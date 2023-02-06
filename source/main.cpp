#include <iostream>
#include "take_home_test/deser.h"

const std::string INPUT_FILE = "../";

auto main() -> int
{
    // Deserialize in from file
    std::vector<lineSegment_t> lines = deserialize_from_file(INPUT_FILE);
    serialize_to_file(lines);

    return 0;
}