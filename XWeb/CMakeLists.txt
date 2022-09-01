cmake_minimum_required(VERSION 3.5)

PROJECT (XWeb VERSION 1.0.0)

configure_file(Config.h.in Config.h)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
SET(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#设置预处理宏定义开关
add_definitions(-DRAPIDJSON_HAS_STDSTRING=1)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(third)

# -Wold-style-cast
# -Wshadow
# -Werror
# -Wextra -Wconversion -Wno-unused-parameter -Woverloaded-virtual -Wpointer-arith -Wwrite-strings -march=native -rdynamic