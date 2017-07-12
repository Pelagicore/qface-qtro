{% set class = '{0}Model'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>

#include "rep_{{module}}_source.h"

class {{class}} : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles {
{% for field in struct.fields %}
        {{field|upperfirst}}Role = Qt::UserRole + {{loop.index}},
{% endfor %}
    };
    {{class}}(QObject *parent = nullptr);
    Q_INVOKABLE {{struct}} get(int index);
    int count() const;
    void insert(int row, const {{struct}} &{{struct|lower}});
    void append(const {{struct}} &{{struct|lower}});
    void update(int row, const {{struct}} &{{struct|lower}});
    void remove(int row);
    void reset(const QList<{{struct}}> data);
    void clear();
public: // from QAbstractListModel
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
Q_SIGNALS:
   void countChanged(int count);
private:
    QList<{{struct}}> m_data;
    QHash<int, QByteArray> m_roleNames;
};


