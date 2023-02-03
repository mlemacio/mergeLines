#include <iostream>
#include <chrono>
#include <fstream> // std::fstream
#include <vector>
#include <cstddef>

#include "take_home_test/deserialize.h"
#include "take_home_test/serialize.h"
#include "take_home_test/lineMerger.h"

using namespace std::chrono;

const std::string INPUT_FILE = "/Users/maciejmleczko/Downloads/take_home_test-main/test/assets/1-split.json";
const std::string OUTPUT_FILE = "hey.json";


int main()
{
    auto t1 = high_resolution_clock::now();

    auto lineSegments = deserialize_from_file(INPUT_FILE);

    mac::lineMerger_t lm;

    lm.addLineSegments(std::move(lineSegments));
    lm.processLines();

    auto mergedLines = lm.getMergedLines();

    serialize_to_file(std::move(mergedLines), OUTPUT_FILE);

    auto t2 = high_resolution_clock::now();
}