{% set class = '{0}Engine'.format(interface) %}

#pragma once

#include <QtCore>

class {{class}} : public QObject
{
    Q_OBJECT
public:
    {{class}}(QObject *parent = nullptr);
    virtual ~{{class}}();
};
