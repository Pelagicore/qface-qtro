cmake_minimum_required(VERSION 3.1)

project({{project}})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(INSTALL_PATH "${CMAKE_BINARY_DIR}/imports" CACHE STRING "Path where the plugins are deployed")


{% for module in system.modules %}
add_subdirectory(plugins/{{module|identifier}})
add_subdirectory(servers/{{module|identifier}})
{% endfor %}
