{% set class = 'VariantModel' %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>

class {{class}} : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    {{class}}(QObject *parent = nullptr);
    Q_INVOKABLE QVariant get(int index);
    int count() const;
Q_SIGNALS:
   void countChanged(int count);
};
