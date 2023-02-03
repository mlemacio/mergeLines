#ifndef TAKE_HOME_TEST_SERIALIZE_H
#define TAKE_HOME_TEST_SERIALIZE_H

// STL
#include <string>

#include "rapidjson/rapidjson.h"
#include "take_home_test/helpers.h"

/**
 * @brief Given a vector of lines, serialize them to a file
 * 
 * @param lines 
 * @param file_name What files to serialize lines, in a pre-defined JSON format
 * 
 *  NOTE: Most of this is hard-coded to a specific format. RapidJSON doesn't have the best documentation
 *        to figure out how to *serialize* things. I'm pretty sure the ID tag isn't important so it's just
 *        monotonically increasing
 */
void serialize_to_file(const std::vector<mac::lineSegment_t> &lines, const std::string &file_name);

#endif // TAKE_HOME_TEST_SERIALIZE_H