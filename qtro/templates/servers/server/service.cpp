{% import 'qface/qtcpp.j2' as cpp %}
{% set class = '{0}Service'.format(interface) %}

{{ cpp.preserved() }}

#include "{{class|lower}}.h"
#include "engine/{{interface|lower}}engine.h"


{{class}}::{{class}}(QObject *parent)
    : {{interface}}ServiceBase(parent)
{
}
