cmake_minimum_required(VERSION 3.0)

project(CMPlatform)

include(path_config.cmake)
CMPlatformSetup(${CMAKE_CURRENT_SOURCE_DIR})

OPTION(BUILD_QT5_SUPPORT_LIB	OFF)

IF(BUILD_QT5_SUPPORT_LIB)

    add_definitions("-DHGL_QT5")

    set(QT_MIN_VERSION "5.14.0")
    find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core)

    include_directories(${Qt5Core_INCLUDES})
    add_definitions(${Qt5Core_DEFINITIONS})

	IF(WIN32)
		SET(HGL_QT_MAIN_SOURCE ${CMPLATFORM_ROOT_SOURCE_PATH}/src/QT/QT5WinUCS2.cpp)
	ELSE()
		SET(HGL_QT_MAIN_SOURCE ${CMPLATFORM_ROOT_SOURCE_PATH}/src/QT/QT5UnixUTF8.cpp)
	ENDIF()

	SET(HGL_QT_LIB CM.QT5Support)
ENDIF()

add_subdirectory(${CMPLATFORM_ROOT_SOURCE_PATH})
