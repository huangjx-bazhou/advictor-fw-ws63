#===============================================================================
# @brief    cmake file
# Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2023-2023. All rights reserved.
#===============================================================================
set(COMPONENT_NAME "advictor")

if(CONFIG_ENABLE_WIFI_STA)
    add_subdirectory_if_exist(wifi_sta)
endif()

set(WHOLE_LINK
    true
)

set(MAIN_COMPONENT
    false
)

if(CONFIG_ENABLE_WIFI_STA)
    install_sdk("${CMAKE_CURRENT_SOURCE_DIR}/wifi_sta" "*")
endif()

build_component()
