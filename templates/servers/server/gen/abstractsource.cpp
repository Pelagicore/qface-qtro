{% set class = 'Abstract{0}Source'.format(interface) %}

#include "abstract{{interface|lower}}source.h"


{{class}}::{{class}}(QObject *parent)
    : {{interface}}Source(parent)
{
}

