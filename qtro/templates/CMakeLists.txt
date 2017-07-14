cmake_minimum_required(VERSION 3.1)

project({{project}})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(INSTALL_PATH "${CMAKE_BINARY_DIR}")
set(PLUGINS_INSTALL_PATH "${INSTALL_PATH}/imports" CACHE STRING "Path where the plugins are deployed")
set(SERVER_INSTALL_PATH "${INSTALL_PATH}/bin" CACHE STRING "Path where the server binaries are deployed")


{% for module in system.modules %}
add_subdirectory(plugins/{{module|identifier}})
add_subdirectory(servers/{{module|identifier}})
{% endfor %}
