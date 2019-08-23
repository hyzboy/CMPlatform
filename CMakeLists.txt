cmake_minimum_required(VERSION 3.0)

project(CMPlatform)

include(path_config.cmake)
CMPlatformSetup(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMPLATFORM_ROOT_SOURCE_PATH})