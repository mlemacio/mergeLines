#ifndef TAKE_HOME_TEST_HELPERS_H
#define TAKE_HOME_TEST_HELPERS_H

#include <stdlib.h>

#include <list>
#include <unordered_map>
#include <vector>

namespace lines
{
    /**
     * @brief Convert a pair of two int32s into a unique uint64 for the sake of a hash table.
     *
     *  NOTE: Order of inputs does matter i.e. createHashKey(a, b) does NOT always equal
     *        createHashKey(b, a)
     */
    uint64_t createHashKey(int32_t left, int32_t right);

    /**
     * @brief Simple wrapper around two doubles, to represent a coordinate in a 2-D plane
     */
    struct alignas(16) coord_t
    {
        coord_t(double _x, double _y) : x(_x), y(_y) {}

        bool operator==(const coord_t &other) const
        {
            return x == other.x && y == other.y;
        }

        uint64_t getHash() const
        {
            return createHashKey(x, y);
        }

        double x;
        double y;
    };

    /**
     * @brief Represents a line segment, by two coordinates
     */
    struct alignas(32) lineSegment_t
    {
        coord_t left;
        coord_t right;
    };

    /**
     * @brief Represents all seen line segments that match a certain slope / yInt pair
     */
    struct slopeGroup_t
    {
        std::vector<lineSegment_t> lines_to_be_added;
        std::list<lineSegment_t> stored_lines;
        std::unordered_map<uint64_t, decltype(stored_lines)::iterator> coord_to_line;
    };

    using slopeGroups_t = std::unordered_map<uint64_t, slopeGroup_t>;
    using modifiedSlopeGroup_t = std::reference_wrapper<slopeGroup_t>;

    namespace math
    {
        /**
         * @brief Because of the nature of the input, a lot of the operations can be vectorized instead of
         *        considering each line, one by one. Helps a lot of performance things
         */
        std::vector<double> calculateSlopes(const std::vector<lineSegment_t> &line_vec);
        std::vector<double> calculateYInts(const std::vector<lineSegment_t> &line_vec, const std::vector<double> &slope_vec);
        std::vector<uint64_t> calculateHashes(const std::vector<double> &slope_vec, const std::vector<double> &yInt_vec);
        std::vector<modifiedSlopeGroup_t> consumeLines(slopeGroups_t &sg,
                                                       const std::vector<uint64_t> &hash_vec,
                                                       std::vector<lineSegment_t> &&line_vec);
    }

}

#endif // TAKE_HOME_TEST_HELPERS_H