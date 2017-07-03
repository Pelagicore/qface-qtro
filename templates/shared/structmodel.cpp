{# Copyright (c) Pelagicore AB 2016 #}
{% set class = '{0}Model'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : QAbstractListModel(parent)
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
    return m_data.value(index);
}

int {{class}}::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant {{class}}::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= count()) {
        return QVariant();
    }
    const {{struct}} &{{struct|lower}} = m_data.at(index.row());
    switch(role) {
    {% for field in struct.fields %}
    case Roles::{{field|upperfirst}}Role:
        return QVariant::fromValue({{struct|lower}}.{{field}}());
    {% endfor %}
    }
    return QVariant();
}

QHash<int, QByteArray> {{class}}::roleNames() const
{
    return m_roleNames;
}


void {{class}}::insert(int row, const {{struct}} &{{struct|lower}})
{
    if (row < 0)
        row = 0;
    if (row >= m_data.count())
        row = m_data.count();

    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, {{struct|lower}});
    endInsertRows();
    emit countChanged(count());
}

void {{class}}::reset(const QList<{{struct}}> data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}

void {{class}}::append(const {{struct}} &{{struct|lower}})
{
    insert(m_data.count(), {{struct|lower}});
}

void {{class}}::update(int row, const {{struct}} &{{struct|lower}})
{
    if(row < 0 || row >= m_data.count()) {
        return;
    }
    m_data[row] = {{struct|lower}};
    const QModelIndex &index = createIndex(row, 0);
    emit dataChanged(index, index);
}

void {{class}}::remove(int row)
{
    if(row < 0 || row >= m_data.count()) {
        return;
    }
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void {{class}}::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

