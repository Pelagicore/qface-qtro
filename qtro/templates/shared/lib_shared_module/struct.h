{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H

// TODO: Move the role names to the struct
// TODO: Move the conversion of a model index to the struct
// TODO: extract these converstion into a helper class?

#include <QtCore>

{% for enum in module.enums %}
#include "{{enum|lower}}enum.h"
{% endfor %}

{{module|open_ns}}

class {{class}}
{
    Q_GADGET
{% for field in struct.fields %}
    Q_PROPERTY({{field|ns}}{{field|returnType}} {{field}} READ {{field}} WRITE set{{field|upperfirst}})
{% endfor %}
public: // operations
    enum ModelRole {
{% for field in struct.fields %}
        {{field|upperfirst}}Role = Qt::UserRole + {{loop.index}},
{% endfor %}
    };

    {{class}}();
    static void registerTypes(const char* uri="{{module}}");
    bool operator==(const {{class}} &other) const;
    bool operator!=(const {{class}} &other) const;
    QVariant toValue(ModelRole role) const;

{% for field in struct.fields %}
    void set{{field|upperfirst}}({{field|parameterType}});
    {{field|returnType}} {{field}}() const;

{% endfor %}

public: // data
{% for field in struct.fields %}
    {{field|returnType}} m_{{field}};
{% endfor %}
};


{{module|close_ns}}

QDataStream &operator<<(QDataStream &stream, const {{module|ns}}{{class}} &obj);
QDataStream &operator>>(QDataStream &stream, {{module|ns}}{{class}} &obj);

Q_DECLARE_METATYPE({{module|ns}}{{class}})

#endif // {{class|upper}}_H
