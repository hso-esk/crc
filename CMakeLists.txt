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

add_library(crc ${${PROJECT_NAME}_SOURCES})

# For inclusion via  add_subdirectory() work.
target_include_directories(crc PRIVATE ${PROJECT_SOURCE_DIR})

# For inclusing via find_package() from build 
target_include_directories(crc INTERFACE "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>")

# For inclusing via find_package() from install
target_include_directories(crc INTERFACE "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Set the version
set_target_properties(crc PROPERTIES
     VERSION  ${${PROJECT_NAME}_VERSION}
)

#---------------------------------------------------------------------------------------
# INSTALLATION + CREATING PACKAGE
#---------------------------------------------------------------------------------------

include(GNUInstallDirs)

#  Set variables
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# Configuration
set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")

set(targets_export_name "${PROJECT_NAME}Targets")

# Generate a package version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
     "${version_config}"
     VERSION ${${PROJECT_NAME}_VERSION}
     COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
     "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
     "${project_config}"
     INSTALL_DESTINATION "${config_install_dir}"
)


# Install targets
install(
     TARGETS crc
     EXPORT ${targets_export_name}
     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Exported targets for build directory
export(EXPORT ${PROJECT_NAME}Targets
     FILE ${project_config}
)

# Exported targets for installation
install(EXPORT ${PROJECT_NAME}Targets
     DESTINATION ${config_install_dir}
     FILE ${PROJECT_NAME}-targets.cmake
)

# Install headers
install(
     FILES ${${PROJECT_NAME}_HEADERS}
	 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install config
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# add to CMake registry
export(PACKAGE ${PROJECT_NAME})
