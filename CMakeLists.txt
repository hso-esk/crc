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
## @author     Lars Moellendorf
## @author     Adrian Antonana
## @author     Johannes Bruder
## @brief      Cyclic Redundancy Check (CRC) error-detecting code.
##
## This file is part of the STACKFORCE Cyclic Redundancy Check Library
## (below "libsfcrc").
##
## libsfcrc is free software: you can redistribute it and/or modify
## it under the terms of the GNU Affero General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## libsfcrc is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Affero General Public License for more details.
##
## You should have received a copy of the GNU Affero General Public License
## along with libsfcrc.  If not, see <http://www.gnu.org/licenses/>.
##

cmake_minimum_required (VERSION 3.6)
project(sfcrc)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# Product and version
#---------------------------------------------------------------------------------------
set(${PROJECT_NAME}_VERSION_MAJOR   0)
set(${PROJECT_NAME}_VERSION_MINOR   1)
set(${PROJECT_NAME}_VERSION_PATCH   2)
set(${PROJECT_NAME}_PRODUCT_COMPANY "STACKFORCE" CACHE STRING "company")
set(${PROJECT_NAME}_PRODUCT_NAME    "Cyclic Redundancy Check" CACHE STRING "product")
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH} )

#---------------------------------------------------------------------------------------
# TARGET
#---------------------------------------------------------------------------------------
# Use CRC calculation as default
option(CRC_TABLE "Set to ON to use a look up table for crc calculation" OFF)

if(CRC_TABLE)
     add_definitions(-DCRC_TABLE=1)
else()
     add_definitions(-DCRC_TABLE=0)
endif()

file(GLOB "${PROJECT_NAME}_SOURCES"
     ${PROJECT_SOURCE_DIR}/*.c)

file(GLOB "${PROJECT_NAME}_HEADERS"
     ${PROJECT_SOURCE_DIR}/*.h)

# intermediate object library to avoid compiling sources twice for shared and static
add_library(sfcrc_o OBJECT ${${PROJECT_NAME}_SOURCES})
set_target_properties(sfcrc_o PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
add_library(sfcrc SHARED $<TARGET_OBJECTS:sfcrc_o>)
add_library(sfcrc-static STATIC $<TARGET_OBJECTS:sfcrc_o>)

# set the output name to have the same libs names files for .so and .a
set_target_properties(sfcrc PROPERTIES OUTPUT_NAME sfcrc)
set_target_properties(sfcrc-static PROPERTIES OUTPUT_NAME sfcrc)

# Set the version
set_target_properties(sfcrc PROPERTIES
    VERSION  ${${PROJECT_NAME}_VERSION}
)

set_target_properties(sfcrc-static PROPERTIES
    VERSION  ${${PROJECT_NAME}_VERSION}
)
# For inclusion via  add_subdirectory() work.
#target_include_directories(sfcrc PRIVATE ${PROJECT_SOURCE_DIR})
#target_include_directories(sfcrc-static PRIVATE ${PROJECT_SOURCE_DIR})

# For inclusing via find_package() from build 
target_include_directories(sfcrc PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfcrc>
)

target_include_directories(sfcrc-static PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfcrc>
)

#---------------------------------------------------------------------------------------
# Install/export targets and files
#---------------------------------------------------------------------------------------
# Set variables
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")

# Generate package version config file
write_basic_package_version_file(
     "${version_config}"
     VERSION ${${PROJECT_NAME}_VERSION}
     COMPATIBILITY AnyNewerVersion
)

# Install targets
install(
    TARGETS sfcrc sfcrc-static
    EXPORT ${targets_export_name}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Exported targets for build directory
export(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}-config.cmake
)

# Exported targets for installation
install(
    EXPORT ${PROJECT_NAME}Targets
    DESTINATION ${config_install_dir}
    FILE ${PROJECT_NAME}-config.cmake
)

# Install headers
install(
    FILES ${${PROJECT_NAME}_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfcrc
)

# Install version config
install(
    FILES "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Add to CMake registry
export(PACKAGE ${PROJECT_NAME})

#---------------------------------------------------------------------------------------
# Doxygen documentation generation
#---------------------------------------------------------------------------------------
#add a target to generate API documentation with Doxygen
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen 1.8.13)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    find_package(Doxygen 1.8.13 REQUIRED)

    # variables for use by generic doxygen configuration file
    set(DOXYGEN_PRODUCT_NAME "${${PROJECT_NAME}_PRODUCT_NAME}")
    set(DOXYGEN_PROJECT_NUMBER "${${PROJECT_NAME}_VERSION}")
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/doc)
    set(DOXYGEN_CUSTOM_RESOURCES_DIR ${PROJECT_BINARY_DIR}/doxygen)

    string(APPEND DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/README.md " ")
    string(APPEND DOXYGEN_INPUT ${PROJECT_SOURCE_DIR} " ")
    string(APPEND DOXYGEN_INPUT ${PROJECT_BINARY_DIR})

    message(STATUS "doxyfile input: ${DOXYGEN_INPUT}")

    set(SF_CORPORATE_DESIGN_URL "INSERT_HERE_THE_URL")
    message(STATUS "Download files for STACKFORCE corporate design:")
#     file(DOWNLOAD
#         "${SF_CORPORATE_DESIGN_URL}/bootstrap.min.css"
#         ${PROJECT_BINARY_DIR}/bootstrap.min.css
#         SHOW_PROGRESS
#         )
#     file(DOWNLOAD
#         "${SF_CORPORATE_DESIGN_URL}/sf_stylesheet.css"
#         ${PROJECT_BINARY_DIR}/sf_stylesheet.css
#         SHOW_PROGRESS
#         )
#     file(DOWNLOAD
#         "${SF_CORPORATE_DESIGN_URL}/sf_footer.html"
#         ${PROJECT_BINARY_DIR}/sf_footer.html
#         SHOW_PROGRESS
#         )
#     file(DOWNLOAD
#         "${SF_CORPORATE_DESIGN_URL}/sf_header.html"
#         ${PROJECT_BINARY_DIR}/sf_header.html
#         SHOW_PROGRESS
#         )
#     file(DOWNLOAD
#         "${SF_CORPORATE_DESIGN_URL}/stackforce_logo.svg"
#         ${PROJECT_BINARY_DIR}/stackforce_logo.svg
#         SHOW_PROGRESS
#         )

    file(COPY "${SF_CORPORATE_DESIGN_URL}/bootstrap.min.css"
        DESTINATION ${DOXYGEN_CUSTOM_RESOURCES_DIR}
    )

    file(COPY "${SF_CORPORATE_DESIGN_URL}/sf_stylesheet.css"
        DESTINATION ${DOXYGEN_CUSTOM_RESOURCES_DIR}
    )

    file(COPY "${SF_CORPORATE_DESIGN_URL}/sf_footer.html"
        DESTINATION ${DOXYGEN_CUSTOM_RESOURCES_DIR}
    )

    file(COPY "${SF_CORPORATE_DESIGN_URL}/sf_header.html"
        DESTINATION ${DOXYGEN_CUSTOM_RESOURCES_DIR}
    )

    file(COPY "${SF_CORPORATE_DESIGN_URL}/stackforce_logo.svg"
        DESTINATION ${DOXYGEN_CUSTOM_RESOURCES_DIR}
    )

    configure_file(${SF_CORPORATE_DESIGN_URL}/Doxyfile.in
        ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(doc ALL
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        SOURCES ${PROJECT_BINARY_DIR}/Doxyfile
    )

    install(DIRECTORY ${PROJECT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/${PROJECT_NAME})
endif()

#---------------------------------------------------------------------------------------
# Create debian package
#---------------------------------------------------------------------------------------
set(CPACK_GENERATOR "DEB")

# check if command dpkg is available
find_program(DPKG_CMD dpkg)
if(DPKG_CMD)
    message(STATUS "DEB Generator: Found dpkg: ${DPKG_CMD}")
else()
    message(FATAL_ERROR "DEB Generator: dpkg not found")
endif()

# set packaging dir
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)
set(CPACK_DEBIAN_PACKAGE_NAME "lib${PROJECT_NAME}")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${${PROJECT_NAME}_PRODUCT_COMPANY} ${${PROJECT_NAME}_PRODUCT_NAME}")
set(CPACK_PACKAGE_VENDOR "${${PROJECT_NAME}_PRODUCT_COMPANY} GmbH")
set(CPACK_PACKAGE_CONTACT "info@stackforce.de")
set(CPACK_DEBIAN_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

include(CPack)
