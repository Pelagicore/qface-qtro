{% set class = '{0}Replica'.format(interface) %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
#pragma once

#include <QtCore>
#include <QtRemoteObjects>
#include "core.h"


{{module|open_ns}}

class {{class}} : public QRemoteObjectReplica {
    Q_OBJECT
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "{{interface}}")
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "{{interface.qualified_name|hash}}")

{% for property in properties %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endfor %}

public:
    {{class}}();
private:
    {{class}}(QRemoteObjectNode *node, const QString &name = QString());
public:
    virtual ~{{class}}();

{% for property in properties %}
    {{property|returnType}} {{property}}() const;
    void set{{property|upperfirst}}({{property|parameters}});
{% endfor %}

public Q_SLOTS:
{% for property in properties %}
    void push{{property|upperfirst}}({{property|parameters}});
{% endfor %}

{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}

Q_SIGNALS:
{% for property in properties %}
    void {{property}}Changed({{property|returnType}});
{% endfor %}
{% for signal in interface.signals %}
    void {{signal}}({{signal|parameters}});
{% endfor %}

private:
    void initialize();
private:
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};

{{module|close_ns}}


