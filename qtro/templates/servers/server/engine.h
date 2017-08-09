{% set class = '{0}Engine'.format(module.name|upperfirst) %}

#pragma once

#include <QtCore>

{{module|open_ns}}

class {{class}} : public QObject
{
    Q_OBJECT
private:
    {{class}}(QObject *parent = nullptr);
public:
    virtual ~{{class}}();
    static {{class}}* instance();
private:
    static {{class}}* s_instance;
};

{{module|close_ns}}
