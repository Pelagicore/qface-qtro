{% set class = '{0}ServiceBase'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>
#include <QtRemoteObjects>

#include "core.h"


{{module|open_ns}}

class {{class}} : public QObject
{
    Q_OBJECT
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "{{interface}}")
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "{{interface.qualified_name|hash}}")

{% for property in properties %}
    Q_PROPERTY({{property|ns}}{{property|returnType}} {{property}} READ {{property}} NOTIFY {{property}}Changed)
{% endfor %}

public:
    explicit {{class}}(QObject *parent = nullptr);

{% for property in properties %}
    virtual {{property|returnType}} {{property}}() const;
    virtual void set{{property|upperfirst}}({{property|parameterType}});

{% endfor %}

{% for property in models %}
    {{property|returnType}} {{property}}() const;
{% endfor %}

Q_SIGNALS:
{% for property in properties %}
    void {{property}}Changed({{property|parameters}});
{% endfor %}
{% for signal in interface.signals %}
    void {{signal}}({{signal|parameters}});
{% endfor %}


public Q_SLOTS:
{% for property in properties %}
    virtual void push{{property|upperfirst}}({{property|parameters}});
{% endfor %}

{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}

private:
{% for property in properties %}
    {{property|returnType}} m_{{property}};
{% endfor %}
{% for property in models %}
    {{property|returnType}} m_{{property}};
{% endfor %}
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};

{{module|close_ns}}

#endif // {{class|upper}}_H