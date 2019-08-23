macro(CMPlatformSetup source_path)

    message("CMPLATFORM_ROOT_PATH: " ${source_path})

    set(CMPLATFORM_ROOT_INCLUDE_PATH    ${source_path}/inc)
    set(CMPLATFORM_ROOT_SOURCE_PATH     ${source_path}/src)

    include_directories(${CMPLATFORM_ROOT_INCLUDE_PATH})
endmacro()