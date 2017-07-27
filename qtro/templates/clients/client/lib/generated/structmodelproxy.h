{% set class = '{0}ModelProxy'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>

#include "{{struct|lower}}.h"

class {{class}} : public QSortFilterProxyModel
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
public: // from QAbstractListModel
    virtual QHash<int, QByteArray> roleNames() const;
Q_SIGNALS:
   void countChanged(int count);
private:
};
