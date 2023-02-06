#include "deser.h"
#include "line_merger.h"

const std::string INPUT_FILE = "/Users/maciejmleczko/projects/cpp/mergeLines/test/assets/1-split.json";
const std::string OUTPUT_FILE = "/Users/maciejmleczko/projects/cpp/mergeLines/test/assets/1-output.json";

auto main() -> int
{
    // Deserialize in from file
    auto lines = deserialize_from_file(INPUT_FILE);

    // Merge the lines
    lineMerger_t lm;
    lm.addLineSegments(std::move(lines));
    lm.processLines();
    auto merged_lines = lm.getMergedLines();

    // Serialize the merged lines to the output file
    serialize_to_file(std::move(merged_lines), OUTPUT_FILE);

    return 0;
}