cmake_minimum_required (VERSION 2.8)
project(crc)

add_definitions(-DCRC_TABLE=0)

add_library(crc ${PROJECT_SOURCE_DIR}/sf_crc.c)

# This is necessary for making the inclusion of this module via
# add_subdirectory() work.
target_include_directories(crc PUBLIC ${PROJECT_SOURCE_DIR})

