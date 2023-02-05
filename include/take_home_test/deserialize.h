//
// Created by Nikolay Shulga on 2019-06-18.
//
// Stub code to test the framework. Feel free to ignore or change.
//

#ifndef TAKE_HOME_TEST_DESERIALIZE_H
#define TAKE_HOME_TEST_DESERIALIZE_H

// STL
#include <string>

struct coord_t
{
    double x;
    double y;
};

struct lineSegment_t
{
    coord_t left;
    coord_t right;
};

std::vector<lineSegment_t> deserialize_from_file(const std::string &file_name);

#endif // TAKE_HOME_TEST_DESERIALIZE_H
