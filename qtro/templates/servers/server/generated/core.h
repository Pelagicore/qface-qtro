{% set class = "Core" %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>
#include <QtRemoteObjects>

{% for enum in module.enums %}
#include "{{enum|lower}}enum.h"
{% endfor %}

{% for struct in module.structs %}
#include "{{struct|lower}}.h"
#include "{{struct|lower}}model.h"
{% endfor %}


{{module|open_ns}}


class {{class}} : public QObject
{
    Q_OBJECT
private:
    {{class}}(QObject *parent=nullptr);
    virtual ~{{class}}();
public:
    void init();
    static {{class}}* instance();
    QRemoteObjectRegistryHost* host() const;
    static void registerTypes();
{% for struct in module.structs %}
    Q_INVOKABLE {{struct}} create{{struct}}();
{% endfor %}
private:
    void reportError(QRemoteObjectNode::ErrorCode code);
private:
    static {{class}}* s_instance;
    QRemoteObjectRegistryHost* m_host;
};

{{module|close_ns}}

#endif
