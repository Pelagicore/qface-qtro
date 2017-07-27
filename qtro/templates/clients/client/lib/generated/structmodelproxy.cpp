{% set class = '{0}ModelProxy'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    {% for field in struct.fields %}
    m_roleNames.insert(Roles::{{field|upperfirst}}Role, QByteArray("{{field}}"));
    {% endfor %}
}

int {{class}}::count() const
{
    return m_data.count();
}

{{struct}} {{class}}::get(int index)
{
    return {{struct}}();
}

QHash<int, QByteArray> {{class}}::roleNames() const
{
    return m_roleNames;
}

