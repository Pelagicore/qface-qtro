{% set class = '{0}ProxyModel'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

int {{class}}::count() const
{
    return rowCount(QModelIndex());
}

{{struct}} {{class}}::get(int index)
{
    {{struct}} {{struct|lower}};

    const QModelIndex& modelIndex = createIndex(index, 0);

{% for field in struct.fields %}
    QVariant {{field}}Value = data(modelIndex, {{field|upperfirst}}Role);
    {{struct|lower}}.set{{field|upperfirst}}({{field}}Value.value<{{field|returnType}}>());

{% endfor %}
    return {{struct|lower}};
}

