#ifndef TAKE_HOME_TEST_LINES_H
#define TAKE_HOME_TEST_LINES_H

#include <functional>
#include <iostream>

#include "helpers/helpers.h"

namespace mac
{
    /**
     * @brief Class revolved around merging 2-D lines that share a slope and common endpoint
     */
    class lineMerger_t
    {
    public:
        lineMerger_t() : m_newLines(),
                         m_slopeGroups() {}

        /**
         * @brief Add new segments to be considered for merging. Supports batching line segments
         *
         * @param lineSegments line segments to be eventually merged or added to underlying list of lines
         */
        void addLineSegments(std::vector<lineSegment_t> &&lineSegments);

        /**
         * @brief Process all the lines we have waiting
         *
         *  NOTE: Most of the operations here could be easily split up into a state machine, no real need for it though
         */
        void processLines();

        /**
         * @brief Returns all lines that were slated to be merged, effectively ruining the container
         *
         *  NOTE: This could be a O(1) instead of O(N) by storing the all the lines in a "global" list
         *        instead of per "slopeGroup" but that gets into ugly code quickly. You could maybe consider
         *        throwing shared ptrs into the mix, but that's pre-optimization
         */
        std::vector<lineSegment_t> getMergedLines();

    private:
        /**
         * @brief Maps every line segment to the line it sits on the place
         *
         * The idea here is that we want to group up all lines that sit on the same 2-D line.
         * To do this, we need a way to map every pair of coordinates to it's respective 2-D line.
         * Using the idea behind y = mx + b, every 2-D line can be identified by it's slope and y-coord
         * So for every line segment we're given, we put it in it's respective (m, b) bucket
         */
        std::pair<std::vector<uint64_t>, std::vector<lineSegment_t>> createMappings(std::vector<lineSegment_t> &&line_vec);

        /**
         * @param slopeGroup_vec Slope groups that have been modified and updated so that the proper lines are merged
         *
         *  NOTE: This can get very costly very quickly
         */
        void updateSlopeGroups(const std::vector<mac::modifiedSlopeGroup_t> &slopeGroup_vec);

        /**
         * @brief Goes in and tries seeing if a line can be merged with any other line in the group
         *
         *        We use a map of coords to line references to quickly check if a line has a match on coords
         *
         * @param slopeGroup
         */
        void updateSlopeGroup(mac::slopeGroup_t &slopeGroup);

        std::vector<lineSegment_t> m_newLines;
        slopeGroups_t m_slopeGroups;
    };
}

#endif // TAKE_HOME_TEST_LINES_H
