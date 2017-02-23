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

#---------------------------------------------------------------------------------------
# PRODUCT AND VERSION
#---------------------------------------------------------------------------------------
set(CRC_VERSION_MAJOR 0)
set(CRC_VERSION_MINOR 1)
set(CRC_VERSION_PATCH 2)
set(CRC_VERSION ${CRC_VERSION_MAJOR}.${CRC_VERSION_MINOR}.${CRC_VERSION_PATCH} )

#---------------------------------------------------------------------------------------
# TARGET
#---------------------------------------------------------------------------------------
# Build static libraries only
option(BUILD_SHARED_LIBS "Set to ON to build shared libraries" OFF)

# Use CRC calculation as default
option(CRC_TABLE "Set to ON to use a look up table for crc calculation" OFF)

if(CRC_TABLE)
   add_definitions(-DCRC_TABLE=1)
else()
   add_definitions(-DCRC_TABLE=0)
endif()

set (CRC_SOURCES
     ${PROJECT_SOURCE_DIR}/sf_crc.c
     )

add_library(crc  ${CRC_SOURCES})

# This is necessary for making the inclusion of this module via
# add_subdirectory() work.
target_include_directories(crc PUBLIC ${PROJECT_SOURCE_DIR})
# NOTE target_include_directories(PUBLIC) is not enough to get Kdevelop
# to find the includes, hence the are defined again with INTERFACE_INCLUDE_DIRECTORIES
set_target_properties(crc PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}
    VERSION  ${CRC_VERSION}
)

#---------------------------------------------------------------------------------------
# INSTALLATION
#---------------------------------------------------------------------------------------
install(TARGETS crc DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/sf_crc.h DESTINATION include)