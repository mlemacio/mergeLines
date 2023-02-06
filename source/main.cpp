#include <iostream>
#include "take_home_test/deser.h"

const std::string INPUT_FILE = "/Users/maciejmleczko/projects/cpp/mergeLines/test/assets/1-split.json";
const std::string OUTPUT_FILE = "/Users/maciejmleczko/projects/cpp/mergeLines/test/assets/1-output.json";

auto main() -> int
{
    // Deserialize in from file
    std::vector<lineSegment_t> lines = deserialize_from_file(INPUT_FILE);
    serialize_to_file(lines, OUTPUT_FILE);

    return 0;
}