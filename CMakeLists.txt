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
cmake_minimum_required (VERSION 3.2)
project(crc)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# PRODUCT AND VERSION
#---------------------------------------------------------------------------------------
set("${PROJECT_NAME}_VERSION_MAJOR" 0)
set("${PROJECT_NAME}_VERSION_MINOR" 1)
set("${PROJECT_NAME}_VERSION_PATCH" 2)
set("${PROJECT_NAME}_VERSION" ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH} )

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

file(GLOB "${PROJECT_NAME}_SOURCES"
     ${PROJECT_SOURCE_DIR}/*.c)

file(GLOB "${PROJECT_NAME}_HEADERS"
     ${PROJECT_SOURCE_DIR}/*.h)

# intermediate object library to avoid compiling sources twice for shared and static
add_library(crc_o OBJECT ${${PROJECT_NAME}_SOURCES})
set_target_properties(crc_o PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
add_library(crc SHARED $<TARGET_OBJECTS:crc_o>)
add_library(crc-static STATIC $<TARGET_OBJECTS:crc_o>)

# set the output name to have the same libs names files for .so and .a
set_target_properties(crc PROPERTIES OUTPUT_NAME crc)
set_target_properties(crc-static PROPERTIES OUTPUT_NAME crc)

# For inclusion via  add_subdirectory() work.
#target_include_directories(crc PRIVATE ${PROJECT_SOURCE_DIR})
#target_include_directories(crc-static PRIVATE ${PROJECT_SOURCE_DIR})

# For inclusing via find_package() from build 
target_include_directories(crc PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfcrc>
)

target_include_directories(crc-static PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfcrc>
)

# Set the version
set_target_properties(crc PROPERTIES
     VERSION  ${${PROJECT_NAME}_VERSION}
)

set_target_properties(crc-static PROPERTIES
     VERSION  ${${PROJECT_NAME}_VERSION}
)

#---------------------------------------------------------------------------------------
# INSTALLATION + CREATING PACKAGE
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
     TARGETS crc crc-static
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
# CREATE DEB PACKAGE
#---------------------------------------------------------------------------------------
set(CPACK_GENERATOR "DEB")

# check if command dpkg is available
find_program(DPKG_CMD dpkg)
if(DPKG_CMD)
	message(STATUS "DEB Generator: Found dpkg: ${DPKG_CMD}")
else()
	message(WARNING "DEB Generator: dpkg not found")
endif()

# inform about package naming issues for cmake<3.6
if(CMAKE_VERSION VERSION_LESS 3.6)
	message(WARNING "DEB Generator: CMake/CPack 3.6 or higher is needed to produce correctly named packages.")
endif()

# set packaging dir
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)

# force CPack generated DEBs to use the same path as CMAKE_INSTALL_PREFIX
#set(CPACK_SET_DESTDIR true)

# manually set system arch if dpkg is not found or cmake version<3.6
if(NOT DPKG_CMD OR CMAKE_VERSION VERSION_LESS 3.6)
	if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL x86_64)
		set(CPACK_SYSTEM_NAME amd64)
	else()
		set(CPACK_SYSTEM_NAME i386)
	endif()
endif()

set(CPACK_DEBIAN_PACKAGE_NAME "libsfcrc")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT) # if cmake<3.6 this is not respected
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "STACKFORCE crc module")
set(CPACK_PACKAGE_VENDOR "STACKFORCE GmbH")
set(CPACK_PACKAGE_CONTACT "info@stackforce.de")
set(CPACK_DEBIAN_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_STRIP_FILES TRUE)

# TODO handle license and readme
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.rst")
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")

include(CPack)
