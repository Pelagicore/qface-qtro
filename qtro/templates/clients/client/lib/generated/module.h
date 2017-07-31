{% set class= '{0}Module'.format(module.module_name|upperfirst) %}
#pragma once

#include <QtCore>

{% for enum in module.enums %}
#include "{{enum|lower}}enum.h"
{% endfor %}

{% for struct in module.structs %}
#include "{{struct|lower}}.h"
#include "{{struct|lower}}proxymodel.h"
{% endfor %}


{{module|open_ns}}

class {{class}}
{
    Q_GADGET
private:
    {{class}}();
public:
    static void registerTypes(const char *uri);
    static QRemoteObjectNode* node();
private:
    static void init();
    static void reportError(QRemoteObjectNode::ErrorCode code);
private:
    static QRemoteObjectNode* m_node;
};

{{module|close_ns}}
