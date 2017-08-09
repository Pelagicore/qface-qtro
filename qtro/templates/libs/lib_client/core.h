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

#include "variantmodel.h"


{{module|open_ns}}

Q_DECLARE_LOGGING_CATEGORY(lib_client_{{module|identifier}})


class Core : public QObject
{
    Q_OBJECT
private:
    Core(QObject *parent=nullptr);
public:
    void init();
    static Core* instance();
    QRemoteObjectNode* node() const;
    static void registerTypes(const char* uri="{{module}}");
{% for struct in module.structs %}
    Q_INVOKABLE {{struct}} create{{struct}}();
{% endfor %}
private:
    void reportError(QRemoteObjectNode::ErrorCode code);
private:
    static Core* s_instance;
    QRemoteObjectNode* m_node;
};

{{module|close_ns}}

#endif
