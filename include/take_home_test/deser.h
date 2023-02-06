//
// Created by Nikolay Shulga on 2019-06-18.
//
// Stub code to test the framework. Feel free to ignore or change.
//

#ifndef TAKE_HOME_TEST_DESER_H
#define TAKE_HOME_TEST_DESER_H

#include <string>
#include <vector>

#include "helpers.h"

using namespace lines;

/**
 * @brief
 *
 * @param file_name
 * @return std::vector<lineSegment_t>
 */
std::vector<lineSegment_t> deserialize_from_file(const std::string &file_name);
void serialize_to_file(const std::vector<lineSegment_t> &line_segments, const std::string &file_name);

#endif // TAKE_HOME_TEST_DESER_H
