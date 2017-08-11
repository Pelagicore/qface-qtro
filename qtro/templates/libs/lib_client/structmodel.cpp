{% set class = '{0}Model'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{module|using_ns}}

{{class}}::{{class}}(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

int {{class}}::count() const
{
    return rowCount(QModelIndex());
}

{{struct}} {{class}}::get(int row)
{
    {{struct}} {{struct|lower}};

    const QModelIndex& index = createIndex(row, 0);

{% for field in struct.fields %}
    {{struct|lower}}.set{{field|upperfirst}}(index.data({{struct}}::{{field|upperfirst}}Role).value<{{field|returnType}}>());
{% endfor %}

    return {{struct|lower}};
}

