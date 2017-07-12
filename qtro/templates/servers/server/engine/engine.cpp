{% set class = '{0}Engine'.format(interface) %}

#include "{{class|lower}}.h"


{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{
}

{{class}}::~{{class}}()
{
}