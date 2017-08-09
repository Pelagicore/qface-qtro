{% import 'qface/qtcpp.j2' as cpp %}
{% set class = '{0}Service'.format(interface) %}

{{ cpp.preserved() }}

#include "{{class|lower}}.h"
#include "{{module.name|lower}}engine.h"

{{module|using_ns}}

{{class}}::{{class}}(QObject *parent)
    : {{interface}}ServiceBase(parent)
{
}
