{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H


#include <QtCore>

{{module|open_ns}}

class {{class}}
{
    Q_GADGET
{% for field in struct.fields %}
    Q_PROPERTY({{field|ns}}{{field|returnType}} {{field}} MEMBER {{field}})
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
public: // data
{% for field in struct.fields %}
    {{field|returnType}} {{field}};
{% endfor %}
};


{{module|close_ns}}

QDataStream &operator<<(QDataStream &stream, const {{module|ns}}{{class}} &obj);
QDataStream &operator>>(QDataStream &stream, {{module|ns}}{{class}} &obj);

Q_DECLARE_METATYPE({{module|ns}}{{class}})

#endif // {{class|upper}}_H
