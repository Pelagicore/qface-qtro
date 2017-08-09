set(LIBRARY_NAME {{module|identifier}})

find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5RemoteObjects REQUIRED)

set (SOURCES
    generated/core.cpp
    generated/variantmodel.cpp
{% for interface in module.interfaces %}
    generated/{{interface|lower}}base.cpp
    {{interface|lower}}.cpp
{% endfor %}
{% for struct in module.structs %}
    generated/{{struct|lower}}.cpp
    generated/{{struct|lower}}model.cpp
{% endfor %}
)

set (HEADERS
    generated/core.h
{% for interface in module.interfaces %}
    {{interface|lower}}.cpp
    generated/{{interface|lower}}base.h
{% endfor %}
{% for struct in module.structs %}
    generated/{{struct|lower}}.h
    generated/{{struct|lower}}model.h
{% endfor %}
{% for enum in module.enums %}
    generated/{{enum|lower}}enum.h
{% endfor %}
)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})


set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_INSTALL_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_INSTALL_PATH}
)

target_link_libraries(${LIBRARY_NAME} PUBLIC Qt5::Core Qt5::Qml Qt5::RemoteObjects)
