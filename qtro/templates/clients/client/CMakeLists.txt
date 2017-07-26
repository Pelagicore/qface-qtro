set(PLUGIN_PATH ${PLUGINS_INSTALL_PATH}/{{module|path}})
set(PLUGIN_NAME {{module|identifier}}_plugin)

find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5RemoteObjects REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set (SOURCES
    plugin.cpp
{% for interface in module.interfaces %}
    {{interface|lower}}.cpp
    generated/abstract{{interface|lower}}.cpp
{% endfor %}
    generated/core.cpp
    ${CMAKE_SOURCE_DIR}/shared/project.qrc
)

set (HEADERS
    plugin.h
{% for interface in module.interfaces %}
    {{interface|lower}}.cpp
    generated/abstract{{interface|lower}}.cpp
{% endfor %}
    generated/core.cpp
    )

qt5_generate_repc(SOURCES ${CMAKE_SOURCE_DIR}/shared/{{module}}.rep REPLICA)

add_library(${PLUGIN_NAME} SHARED ${SOURCES})


set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_PATH}
)

target_link_libraries(${PLUGIN_NAME} PUBLIC Qt5::Core Qt5::Qml Qt5::RemoteObjects)
configure_file(qmldir ${PLUGIN_PATH}/qmldir COPYONLY)
