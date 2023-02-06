#include "helpers.h"

namespace lines
{
    uint64_t createHashKey(int32_t left, int32_t right)
    {
        return ((static_cast<uint64_t>(left) << 32) | right);
    }

    namespace math
    {
        std::vector<double> calculateSlopes(const std::vector<lineSegment_t> &line_vec)
        {
            size_t num_lines = line_vec.size();

            std::vector<double> y_delta_vec;
            std::vector<double> x_delta_vec;
            std::vector<double> slope_vec;

            y_delta_vec.reserve(num_lines);
            x_delta_vec.reserve(num_lines);
            slope_vec.reserve(num_lines);

            // Subtraction step
            for (const auto &line : line_vec)
            {
                y_delta_vec.emplace_back((line.right.y - line.left.y));
                x_delta_vec.emplace_back((line.right.x - line.left.x));
            }

            // Divide step
            for (auto i = 0; i < num_lines; ++i)
            {
                slope_vec.emplace_back((y_delta_vec[i] / x_delta_vec[i]));
            }

            return slope_vec;
        }

        std::vector<double> calculateYInts(const std::vector<lineSegment_t> &line_vec, const std::vector<double> &slope_vec)
        {
            size_t num_lines = line_vec.size();

            std::vector<double> yInt_vec;
            std::vector<double> temp_vec;

            yInt_vec.reserve(num_lines);
            temp_vec.reserve(num_lines);

            // mx step
            for (int i = 0; i < num_lines; ++i)
            {
                temp_vec.emplace_back(slope_vec[i] * line_vec[i].left.x);
            }

            // b step
            for (int i = 0; i < num_lines; ++i)
            {
                const auto &[x0, y0] = line_vec[i].left;
                yInt_vec.emplace_back((y0 - temp_vec[i]));
            }

            return yInt_vec;
        }

        std::vector<uint64_t> calculateHashes(const std::vector<double> &slope_vec, const std::vector<double> &yInt_vec)
        {
            size_t num_lines = slope_vec.size();

            std::vector<uint64_t> hashes_vec;
            std::vector<std::pair<double, double>> temp_vec;

            hashes_vec.reserve(num_lines);
            temp_vec.reserve(num_lines);

            for (int i = 0; i < num_lines; ++i)
            {
                // We put in a fudge factor here, so that minute differences don't prevent similar slopes and intercepts
                // from being grouped together. We'd rather have too little groups than too many
                auto fudgeSlope = slope_vec[i] * 1'000;
                auto fudgeYInt = yInt_vec[i] * 1'000;

                temp_vec.emplace_back(std::pair<double, double>{fudgeSlope, fudgeYInt});
            }

            for (int i = 0; i < num_lines; ++i)
            {
                hashes_vec.emplace_back(createHashKey(temp_vec[i].first, temp_vec[i].second));
            }

            return hashes_vec;
        }

        std::vector<modifiedSlopeGroup_t> consumeLines(slopeGroups_t &sg,
                                                       const std::vector<uint64_t> &hash_vec,
                                                       std::vector<lineSegment_t> &&line_vec)
        {
            size_t num_lines = hash_vec.size();
            std::vector<modifiedSlopeGroup_t> usg;

            usg.reserve(num_lines);
            sg.reserve(sg.size() + num_lines);

            for (auto i = 0; i < num_lines; ++i)
            {
                // Put all line segments with the same slope in the same group
                auto &slopeGroup = sg[hash_vec[i]];
                slopeGroup.lines_to_be_added.emplace_back(std::move(line_vec[i]));
                usg.emplace_back(slopeGroup);
            }

            // The map now "owns" the line segment
            line_vec.clear();

            return usg;
        }
    }

} // lines