#pragma once

{% for struct in module.structs %}
#include "{{struct|lower}}.h"
#include "{{struct|lower}}model.h"
{% endfor %}
#include "variantmodel.h"
