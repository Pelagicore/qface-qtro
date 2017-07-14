project({{module|identifier}})

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

set(INSTALL_PATH "${CMAKE_BINARY_DIR}/bin" CACHE STRING "Path where the executables are deployed")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5RemoteObjects REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set (SOURCES
    main.cpp
{% for interface in module.interfaces %}
    {{interface|lower}}service.cpp
    generated/{{interface|lower}}servicebase.cpp
    engine/{{interface|lower}}engine.cpp
{% endfor %}
{% for struct in module.structs %}
    generated/{{struct|lower}}model.cpp
{% endfor %}
    generated/variantmodel.cpp
    ${CMAKE_SOURCE_DIR}/shared/project.qrc
)

qt5_generate_repc(SOURCES ${CMAKE_SOURCE_DIR}/shared/{{module}}.rep SOURCE)


add_executable({{module|identifier}} ${SOURCES})

target_link_libraries({{module|identifier}} PUBLIC Qt5::Core Qt5::Qml Qt5::RemoteObjects)
