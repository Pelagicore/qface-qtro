{% set class = '{0}Service'.format(interface) %}

#ifndef {{interface|upper}}_SERVICE_H
#define {{interface|upper}}_SERVICE_H

#include <QtCore>

#include "gen/abstract{{interface|lower}}source.h"


class {{class}} : public Abstract{{interface}}Source
{
    Q_OBJECT
public:
    explicit {{class}}(QObject *parent=nullptr);
};

#endif // {{interface|upper}}_SERVICE_H
