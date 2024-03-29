﻿SET(CPU_INFO_HEADER ${CMPLATFORM_ROOT_INCLUDE_PATH}/hgl/platform/CpuInfo.h)

IF(UNIX)
    SET(PLATFORM_FILE_SOURCE            UNIX/File.cpp
                                        UNIX/FileAccess.cpp
                                        UNIX/EnumFile.cpp)

    SET(PLATFORM_SYSTEM_INFO_SOURCE     UNIX/SystemInfo.cpp)

    SET(PLATFORM_MULTI_THREAD_SOURCE    UNIX/CondVar.cpp
                                        UNIX/RWLock.cpp
                                        UNIX/Thread.cpp
                                        UNIX/ThreadMutex.cpp)

    IF(ANDROID)
        SET(PLATFORM_LOG_SOURCE             Android/LogConsole.cpp)

        SET(PLATFORM_APPLICATION_SOURCE     ${PLATFORM_APPLICATION_SOURCE}
                                            Android/JNISupport.cpp
                                            Android/NativeActivitySupport.cpp)

        SET(PLATFORM_FILE_SOURCE            ${PLATFORM_FILE_SOURCE}
                                            Android/ProgramPath.cpp
                                            Android/AssetManage.cpp)

        SET(PLATFORM_MULTI_THREAD_SOURCE    ${PLATFORM_MULTI_THREAD_SOURCE}
                                            UNIX/Semaphore.cpp)
    ELSE()
        SET(PLATFORM_CODEPAGE_SOURCE        UNIX/CodePage.cpp)
        SET(PLATFORM_LOG_SOURCE             UNIX/LogConsole.cpp)

        IF(APPLE)
            SET(PLATFORM_MULTI_THREAD_SOURCE    ${PLATFORM_MULTI_THREAD_SOURCE}
                                                Apple/Semaphore.cpp)

            SET(PLATFORM_FILE_SOURCE            ${PLATFORM_FILE_SOURCE}
                                                Apple/ProgramPath.mm)
        ELSE()
            SET(PLATFORM_MULTI_THREAD_SOURCE    ${PLATFORM_MULTI_THREAD_SOURCE}
                                                UNIX/Semaphore.cpp)

            SET(PLATFORM_FILE_SOURCE            ${PLATFORM_FILE_SOURCE}
                                                UNIX/ProgramPath.cpp)

            SET(PLATFORM_WINDOW_SOURCE          UNIX/XCBWindow.cpp)
        ENDIF()
    ENDIF()

    SET(PLATFORM_MULTI_PROCESS_SOURCE   UNIX/ProcMutex.cpp
                                        UNIX/Process.cpp
                                        UNIX/Pipe.cpp
                                        UNIX/Fifo.cpp)

    SET(PLATFORM_TIME_SOURCE            UNIX/Time.cpp
                                        UNIX/Exit.cpp
                                        UNIX/DateTime.cpp)

    SET(PLATFORM_EXTERNAL_MODULE_SOURCE UNIX/ExternalModule.cpp)

ENDIF()

IF(WIN32)
    set(CPU_INFO_SOURCE                 Win/CpuInfo.cpp)

    SET(PLATFORM_FILE_SOURCE            Win/File.cpp
                                        Win/FileAccess.cpp
                                        Win/EnumFile.cpp
                                        Win/EnumVolume.cpp
                                        Win/ProgramPath.cpp)

    SET(PLATFORM_CODEPAGE_SOURCE        Win/CodePage.cpp
                                        Win/vsprintf.cpp)

    SET(PLATFORM_SYSTEM_INFO_SOURCE     Win/SystemInfo.cpp)

    SET(PLATFORM_LOG_SOURCE             Win/LogConsole.cpp
                                        Win/LogDialog.cpp)

    SET(PLATFORM_MULTI_THREAD_SOURCE
                                        Win/CondVar.cpp
                                        Win/RWLock.cpp
                                        Win/Semaphore.cpp
                                        Win/Thread.cpp
                                        Win/ThreadMutex.cpp)

    SET(PLATFORM_MULTI_PROCESS_SOURCE   Win/ProcMutex.cpp
                                        Win/Pipe.cpp
                                        Win/Fifo.cpp)

    SET(PLATFORM_TIME_SOURCE            Win/Time.cpp
                                        Win/DateTime.cpp)

    SET(PLATFORM_EXTERNAL_MODULE_SOURCE Win/ExternalModule.cpp)

    SET(PLATFORM_DESKTOP_SOURCE         Win/Desktop.cpp)

    SET(PLATFORM_WINDOW_SOURCE          Win/WinWindow.cpp
                                        Win/WinMessage.cpp
                                        Win/EnumWinFonts.cpp)
ENDIF(WIN32)

SET(PLATFORM_WINDOW_SOURCE ${PLATFORM_WINDOW_SOURCE} Window.cpp )

SOURCE_GROUP("InputDevice"  FILES ${PLATFORM_INPUT_DEVICE_SOURCE})
SOURCE_GROUP("CodePage"     FILES ${PLATFORM_CODEPAGE_SOURCE})
SOURCE_GROUP("File"         FILES ${PLATFORM_FILE_SOURCE})
SOURCE_GROUP("SystemInfo"   FILES ${PLATFORM_SYSTEM_INFO_SOURCE})
SOURCE_GROUP("Application"  FILES ${PLATFORM_APPLICATION_SOURCE})
SOURCE_GROUP("LogInfo"      FILES ${PLATFORM_LOG_SOURCE})
SOURCE_GROUP("MultiThread"  FILES ${PLATFORM_MULTI_THREAD_SOURCE})
SOURCE_GROUP("MultiProcess" FILES ${PLATFORM_MULTI_PROCESS_SOURCE})
SOURCE_GROUP("Time"         FILES ${PLATFORM_TIME_SOURCE})
SOURCE_GROUP("Desktop"      FILES ${PLATFORM_DESKTOP_SOURCE})
SOURCE_GROUP("Window"       FILES ${PLATFORM_WINDOW_SOURCE})

SOURCE_GROUP("Hardware\\Cpuinfo" FILES ${CPU_INFO_HEADER} ${CPU_INFO_SOURCE})

SET(ANDROID_ABOUT_SOURCE    ${CMPLATFORM_ROOT_INCLUDE_PATH}/hgl/platform/Android.h
                            Android/AndroidVersion.cpp)

SOURCE_GROUP("Android\\Version" FILES ${ANDROID_ABOUT_SOURCE})

OPTION(CM_PLATFORM_SOC OFF)

IF(CM_PLATFORM_SOC)

    SET(SOC_SOURCE  ${CMPLATFORM_ROOT_INCLUDE_PATH}/hgl/platform/SOC.h
                    SOC/SOC.cpp
                    SOC/ARMCpuInfo.cpp
    )

    SOURCE_GROUP("SOC" FILES ${SOC_SOURCE})

ENDIF(CM_PLATFORM_SOC)

SET(PLATFORM_SOURCE ${PLATFORM_SOURCE}
                    ${PLATFORM_FILE_SOURCE}
                    ${PLATFORM_CODEPAGE_SOURCE}
                    #${PLATFORM_SYSTEM_INFO_SOURCE}
                    ${PLATFORM_APPLICATION_SOURCE}
                    ${PLATFORM_LOG_SOURCE}
                    ${PLATFORM_MULTI_THREAD_SOURCE}
                    ${PLATFORM_MULTI_PROCESS_SOURCE}
                    ${PLATFORM_TIME_SOURCE}
                    ${PLATFORM_EXTERNAL_MODULE_SOURCE}
                    ${PLATFORM_INPUT_DEVICE_SOURCE}
                    ${PLATFORM_WINDOW_SOURCE}

                    ${CPU_INFO_HEADER}
                    ${CPU_INFO_SOURCE}
                    ${ANDROID_ABOUT_SOURCE}
                    ${SOC_SOURCE}
)

add_cm_library(CMPlatform "CM" ${PLATFORM_SOURCE})
