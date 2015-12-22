##
## @code
##  ___ _____ _   ___ _  _____ ___  ___  ___ ___
## / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
## \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
## |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
## embedded.connectivity.solutions.==============
## @endcode
##
## @file
## @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
## @author     STACKFORCE
## @brief      Cyclic Redundancy Check (CRC) error-detecting code.
##
cmake_minimum_required (VERSION 2.8)
project(crc)

add_definitions(-DCRC_TABLE=0)

add_library(crc ${PROJECT_SOURCE_DIR}/sf_crc.c)

# This is necessary for making the inclusion of this module via
# add_subdirectory() work.
target_include_directories(crc PUBLIC ${PROJECT_SOURCE_DIR})

