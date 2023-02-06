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
set(A_LIBRARY_SOURCES source/take_home_test/helpers.cpp)
set(A_LIBRARY_HEADERS include/take_home_test/helpers.h)

add_library(helpers_library ${A_LIBRARY_SOURCES} ${A_LIBRARY_HEADERS})

set(B_LIBRARY_SOURCES source/take_home_test/deser.cpp)
set(B_LIBRARY_HEADERS include/take_home_test/deser.h)

add_library(deser_library ${B_LIBRARY_SOURCES} ${B_LIBRARY_HEADERS})

set(C_LIBRARY_SOURCES source/take_home_test/line_merger.cpp)
set(C_LIBRARY_HEADERS include/take_home_test/line_merger.h)

add_library(line_merger_library ${C_LIBRARY_SOURCES} ${C_LIBRARY_HEADERS})

# exec sources go here
set(EXEC_SOURCES source/main.cpp)

add_executable(take_home_test ${EXEC_SOURCES})
target_link_libraries(take_home_test helpers_library deser_library line_merger_library)

# Tests
enable_testing()

# Your tests
set(TEST_SOURCES test/tests.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests helpers_library deser_library)

add_test(unit_tests unit_tests)
