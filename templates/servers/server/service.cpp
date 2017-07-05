{% set class = '{0}Service'.format(interface) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#include "{{class|lower}}.h"


{{class}}::{{class}}(QObject *parent)
    : {{interface}}AbstractSource(parent)
{
}