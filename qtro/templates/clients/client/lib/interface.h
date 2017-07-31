{% set class = '{0}'.format(interface) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#pragma once

#include <QtCore>

#include "generated/{{interface|lower}}base.h"

{{interface|open_ns}}

class {{class}} : public {{interface}}Base
{
    Q_OBJECT
public:
    {{class}}(QObject *parent = nullptr);
    virtual ~{{class}}();

    static void registerQmlType(const QString& uri="{{module}}", int majorVersion=1, int minorVersion=0);
};


{{interface|close_ns}}
