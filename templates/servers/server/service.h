{% set class = '{0}Service'.format(interface) %}

#ifndef {{interface|upper}}_SERVICE_H
#define {{interface|upper}}_SERVICE_H

#include <QtCore>

#include "generated/{{interface|lower}}abstractsource.h"


class {{class}} : public {{interface}}AbstractSource
{
    Q_OBJECT
public:
    explicit {{class}}(QObject *parent=nullptr);
};

#endif // {{interface|upper}}_SERVICE_H
