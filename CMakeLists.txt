cmake_minimum_required(VERSION 3.14)
project(take_home_test)

set(CMAKE_CXX_STANDARD 17)

# needed by RapidJSON
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DGTEST_HAS_POSIX_RE=0")

if (WIN32)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

include_directories(include)
include_directories(include/rapidjson)
include_directories(include/rapidjson/error)
include_directories(include/rapidjson/internal)
include_directories(include/take_home_test)

# Your library sources go here
set(LIBRARY_SOURCES source/take_home_test/helpers.cpp)
set(LIBRARY_HEADERS include/take_home_test/helpers.h)

add_library(helpers_library ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

set(LIBRARY_SOURCES source/take_home_test/serialize.cpp)
set(LIBRARY_HEADERS include/take_home_test/serialize.h)

add_library(serialize_library ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

set(LIBRARY_SOURCES source/take_home_test/deserialize.cpp)
set(LIBRARY_HEADERS include/take_home_test/deserialize.h)

add_library(deserialize_library ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# exec sources go here
set(EXEC_SOURCES source/main.cpp)

add_executable(take_home_test ${EXEC_SOURCES})
target_link_libraries(take_home_test helpers_library serialize_library deserialize_library)

# Tests
enable_testing()

# Your tests
set(TEST_SOURCES test/tests.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests take_home_test_library)

add_test(unit_tests unit_tests)
