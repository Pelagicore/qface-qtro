{% set class = 'VariantModel' %}
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

QVariant {{class}}::get(int index)
{
    return data(createIndex(index, 0), Qt::UserRole);
}

