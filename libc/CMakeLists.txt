cmake_minimum_required(VERSION 3.25)

project(library)

set(SOURCE_LIB get_if.c signal_handler.c
    interface_info/get_broadcast_if.c interface_info/get_ip_for_mac_if.c    # Установка переменной со списком исходников 
    interface_info/get_mac_address_if.c interface_info/get_flags_if.c interface_info/get_interface_lists.c interface_info/get_interface_value_if.c
    interface_info/get_mtu_if.c interface_info/get_network_mask_if.c
    analizator_kernel/analizator.c analizator_kernel/get_listen_kernel.c analizator_kernel/io_kernel.c analizator_kernel/transport_processing.c
    analizator_kernel/network_processing.c)

add_library(library STATIC ${SOURCE_LIB}) # Создание статической библиотеки