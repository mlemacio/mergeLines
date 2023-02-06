//
// Created by Nikolay Shulga on 2019-06-18.
//

#include "deser.h"

#include <iostream>

// STL
#include <fstream>
#include <string>
#include <vector>

// RapidJSON
#include "document.h"
#include "filereadstream.h"
#include "rapidjson.h"

using namespace rapidjson;

// Input data format/parsing.
// Input is a JSON file. The root object is an array called "lines". These are line segments.
// Each line segment has an id "id" (string), starting point "start and an end point "end".
// Points are represented as an array of two doubles. These correspond to X and Y cartesian coordinates.

std::vector<lineSegment_t> deserialize(Document &doc)
{
    std::vector<lineSegment_t> lineSegments;

    auto const &lines_json = doc["lines"];
    if (lines_json.IsArray())
    {
        auto lines_array = lines_json.GetArray();
        for (auto &line : lines_array)
        {
            auto const &id_json = line["id"];
            auto const &start_json = line["start"];
            auto const &end_json = line["end"];
            if (id_json.IsString() && start_json.IsArray() && end_json.IsArray())
            {
                auto start_x = start_json.GetArray()[0].GetDouble(),
                     start_y = start_json.GetArray()[1].GetDouble(),
                     end_x = end_json.GetArray()[0].GetDouble(),
                     end_y = end_json.GetArray()[1].GetDouble();

                lineSegments.emplace_back(lineSegment_t{coord_t{start_x, start_y}, coord_t{end_x, end_y}});
            }
        }
    }

    return lineSegments;
}

std::vector<lineSegment_t> deserialize_from_file(const std::string &file_name)
{
    FILE *fp = fopen(file_name.c_str(), "r");

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    fclose(fp);

    return deserialize(d);
}

void serialize_to_file(const std::vector<lineSegment_t> &line_segments, const std::string &file_name)
{
    std::ofstream my_file;
    my_file.open(file_name);

    // This 16 is purely because the reference solution has it at 16
    my_file.precision(16);

    my_file << "{\"lines\":[";

    // Due to formatting, it's just easier to check 0 here
    if (line_segments.size() > 0)
    {
        for (auto i = 0; i < line_segments.size() - 1; ++i)
        {
            auto &line = line_segments[i];

            my_file << "{\"id\":\"";
            my_file << i;
            my_file << "\",\"start\":[";

            my_file << line.left.x << ',';
            my_file << line.left.y << "],";

            my_file << "\"end\":[";
            my_file << line.right.x << ',';
            my_file << line.right.y << "]},";
        }

        auto &lastLine = line_segments.back();
        my_file << "{\"id\":\"";
        my_file << line_segments.size() - 1;
        my_file << "\",\"start\":[";

        my_file << lastLine.left.x << ',';
        my_file << lastLine.left.y << "],";

        my_file << "\"end\":[";
        my_file << lastLine.right.x << ',';
        my_file << lastLine.right.y << "]}";
    }

    my_file << "]}";
}