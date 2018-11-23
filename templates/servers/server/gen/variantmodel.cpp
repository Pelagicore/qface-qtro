{# Copyright (c) Pelagicore AB 2016 #}
{% set class = 'VariantModel' %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames.insert(Roles::ModelData, QByteArray("modelData"));
}

int {{class}}::count() const
{
    return m_data.count();
}

QVariant {{class}}::get(int index)
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
    const QVariant &entry = m_data.at(index.row());
    switch(role) {
    case Roles::ModelData:
        return entry;
    }
    return QVariant();
}

QHash<int, QByteArray> {{class}}::roleNames() const
{
    return m_roleNames;
}


void {{class}}::insert(int row, const QVariant &entry)
{
    if (row < 0)
        row = 0;
    if (row >= m_data.count())
        row = m_data.count();

    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, entry);
    endInsertRows();
    emit countChanged(count());
}

void {{class}}::reset(const QVariantList entries)
{
    beginResetModel();
    m_data = entries;
    endResetModel();
}

void {{class}}::append(const QVariant &entry)
{
    insert(m_data.count(), entry);
}

void {{class}}::update(int row, const QVariant &entry)
{
    if(row < 0 || row >= m_data.count()) {
        return;
    }
    m_data[row] = entry;
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

