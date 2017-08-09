{% set class = '{0}Service'.format(interface) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#ifndef {{interface|upper}}_SERVICE_H
#define {{interface|upper}}_SERVICE_H

#include <QtCore>

#include "{{interface|lower}}servicebase.h"

{{module|open_ns}}

class {{class}} : public {{interface}}ServiceBase
{
    Q_OBJECT
public:
    explicit {{class}}(QObject *parent=nullptr);
private:
};

{{module|close_ns}}

#endif // {{interface|upper}}_SERVICE_H
