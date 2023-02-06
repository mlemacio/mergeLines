#include "line_merger.h"

namespace lines
{
    void lineMerger_t::addLineSegments(std::vector<lineSegment_t> &&lineSegments)
    {
        // If we have a fresh batch, we can just grab the line segments
        if (m_newLines.size() == 0)
        {
            m_newLines = std::move(lineSegments);
            return;
        }

        // Add new segments to our list (this is our primitive batching)
        m_newLines.reserve(m_newLines.size() + lineSegments.size());
        m_newLines.insert(m_newLines.end(),
                          std::make_move_iterator(lineSegments.begin()),
                          std::make_move_iterator(lineSegments.end()));
    }

    void lineMerger_t::processLines()
    {
        std::vector<lineSegment_t> line_vec = std::move(m_newLines);
        m_newLines.clear();

        // Create a hash (slope / yInt pair) for every line segment
        auto mappings = createMappings(std::move(line_vec));

        // Throw them into the map, and track which groups of lines need to be reconsidered for merging
        auto updatedSlopeGroups_vec = math::consumeLines(m_slopeGroups, std::move(mappings.first), std::move(mappings.second));

        // Merge any new into their respective places
        updateSlopeGroups(std::move(updatedSlopeGroups_vec));
    }

    std::vector<lineSegment_t> lineMerger_t::getMergedLines()
    {
        std::vector<lineSegment_t> mergedLine_vec;
        mergedLine_vec.reserve(m_slopeGroups.size());

        // We really don't care about relative ordering
        for (auto &slopeGroup : m_slopeGroups)
        {
            for (auto &line : slopeGroup.second.stored_lines)
            {
                mergedLine_vec.emplace_back(std::move(line));
            }
            slopeGroup.second.stored_lines.clear();
        }

        m_slopeGroups.clear();
        return mergedLine_vec;
    }

    std::pair<std::vector<uint64_t>, std::vector<lineSegment_t>> lineMerger_t::createMappings(std::vector<lineSegment_t> &&line_vec)
    {
        auto slope_vec = math::calculateSlopes(line_vec);
        auto yInt_vec = math::calculateYInts(line_vec, slope_vec);
        auto hash_vec = math::calculateHashes(std::move(slope_vec), std::move(yInt_vec));

        return {hash_vec, line_vec};
    }

    void lineMerger_t::updateSlopeGroups(const std::vector<modifiedSlopeGroup_t> &slopeGroup_vec)
    {
        for (auto &slopeGroup_ref : slopeGroup_vec)
        {
            updateSlopeGroup(slopeGroup_ref.get());
        }
    }

    void lineMerger_t::updateSlopeGroup(slopeGroup_t &slopeGroup)
    {
        for (auto &line : slopeGroup.lines_to_be_added)
        {
            // See if we have any matches on coords
            // If there is a match, it's guaranteed going to be extracted regardless
            auto leftNH = slopeGroup.coord_to_line.extract(line.left.getHash());
            auto rightNH = slopeGroup.coord_to_line.extract(line.right.getHash());

            bool canMergeWithLeft = !leftNH.empty();
            bool canMergeWithRight = !rightNH.empty();

            // If we get a match, update the line to include coord that DIDN'T match
            // A merged line means we get rid of the coordinate that matched
            if (canMergeWithLeft)
            {
                line.left = (leftNH.mapped()->left == line.left) ? leftNH.mapped()->right : leftNH.mapped()->left;
                slopeGroup.stored_lines.erase(leftNH.mapped());
            }

            if (canMergeWithRight)
            {
                line.right = (rightNH.mapped()->right == line.right) ? rightNH.mapped()->left : rightNH.mapped()->right;
                slopeGroup.stored_lines.erase(rightNH.mapped());
            }

            // At this point, "line" is ready to be added
            slopeGroup.stored_lines.emplace_front(std::move(line));

            auto lineIter = slopeGroup.stored_lines.begin();
            slopeGroup.coord_to_line.emplace(lineIter->left.getHash(), lineIter);
            slopeGroup.coord_to_line.emplace(lineIter->right.getHash(), lineIter);
        }

        // We're done processing all new lines
        slopeGroup.lines_to_be_added.clear();
    }
};