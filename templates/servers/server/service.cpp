{% set class = '{0}Service'.format(interface) %}

#include "{{class|lower}}.h"


{{class}}::{{class}}(QObject *parent)
    : Abstract{{interface}}Source(parent)
{
}