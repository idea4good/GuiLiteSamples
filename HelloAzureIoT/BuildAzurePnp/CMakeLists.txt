cmake_minimum_required(VERSION 3.10)

include_directories(include)
include_directories(include/iothub_client)
include_directories(pnp)
include_directories(pnp/common)

link_directories(libs)

set(source_files
    main.c
    func.cpp
    pnp/common/pnp_dps_ll.c
)

add_definitions(-DUSE_PROV_MODULE_FULL)

add_executable(pnpGuiLite ${source_files})

# prov_auth_client depends on prov_mqtt_transport
target_link_libraries(pnpGuiLite prov_auth_client prov_mqtt_transport)

target_link_libraries(pnpGuiLite iothub_client prov_device_ll_client iothub_client_mqtt_transport aziotsharedutil hsm_security_client parson prov_auth_client umqtt)

target_link_libraries(pnpGuiLite crypto pthread ssl curl m)

add_custom_command(TARGET pnpGuiLite 
    POST_BUILD
    COMMAND ../.sync_build.sh HelloAzureIoT)
