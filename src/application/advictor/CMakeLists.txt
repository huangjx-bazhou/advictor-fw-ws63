#===============================================================================
# @brief    cmake file
# Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2023-2023. All rights reserved.
#===============================================================================
set(COMPONENT_NAME "advictor")

if(CONFIG_ENABLE_GATEWAY)
    add_subdirectory_if_exist(gateway)
endif()

set(WHOLE_LINK
    true
)

set(MAIN_COMPONENT
    false
)

if(CONFIG_ENABLE_GATEWAY)
    install_sdk("${CMAKE_CURRENT_SOURCE_DIR}/gateway" "*")
endif()

build_component()
