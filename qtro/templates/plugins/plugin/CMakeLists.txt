project({{module|identifier}})

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

set(INSTALL_PATH "${CMAKE_BINARY_DIR}/imports" CACHE STRING "Path where the plugins are deployed")

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

add_library({{module|identifier}}_plugin SHARED ${SOURCES})

set(OUTPUT_PATH ${INSTALL_PATH}/{{module.name_parts|join('/')}})

set_target_properties({{module|identifier}}_plugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

message(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})

target_link_libraries({{module|identifier}}_plugin PUBLIC Qt5::Core Qt5::Qml Qt5::RemoteObjects)
configure_file(qmldir ${OUTPUT_PATH}/qmldir COPYONLY)
message(SOURCES ${SOURCES})
