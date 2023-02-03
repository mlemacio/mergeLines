#include "serialize.h"

#include <iostream>
#include <fstream>
#include <limits>

// RapidJSON
#include "document.h"
#include "rapidjson.h"

#include <document.h>

using namespace rapidjson;
using namespace mac;

void serialize_to_file(const std::vector<mac::lineSegment_t> &merged_lines, const std::string &file_name)
{
    std::ofstream myfile;
    myfile.open(file_name);

    // This 16 is purely because the reference solution has it at 16
    myfile.precision(16);

    myfile << "{\"lines\":[";

    // Due to formatting, it's just easier to check 0 here
    if (merged_lines.size() > 0)
    {
        for (auto i = 0; i < merged_lines.size() - 1; ++i)
        {
            auto &line = merged_lines[i];

            myfile << "{\"id\":\"";
            myfile << i;
            myfile << "\",\"start\":[";

            myfile << line.left.x << ',';
            myfile << line.left.y << "],";

            myfile << "\"end\":[";
            myfile << line.right.x << ',';
            myfile << line.right.y << "]},";
        }

        auto &lastLine = merged_lines.back();
        myfile << "{\"id\":\"";
        myfile << merged_lines.size() - 1;
        myfile << "\",\"start\":[";

        myfile << lastLine.left.x << ',';
        myfile << lastLine.left.y << "],";

        myfile << "\"end\":[";
        myfile << lastLine.right.x << ',';
        myfile << lastLine.right.y << "]}";
    }

    myfile << "]}";
}