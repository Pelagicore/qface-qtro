project({{module|identifier}})

cmake_minimum_required(VERSION 3.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SERVER_INSTALL_PATH})
set(TARGET_NAME {{module|identifier}}_server)

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


add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC Qt5::Core Qt5::Qml Qt5::RemoteObjects)
