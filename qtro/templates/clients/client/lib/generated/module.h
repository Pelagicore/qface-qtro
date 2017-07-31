#pragma once

{% for enum in module.enums %}
#include "{{enum|lower}}enum.h"
{% endfor %}

{% for struct in module.structs %}
#include "{{struct|lower}}.h"
#include "{{struct|lower}}proxymodel.h"
{% endfor %}

{% for interface in module.interfaces %}
// #include "{{interface|lower}}.h"
{% endfor %}

