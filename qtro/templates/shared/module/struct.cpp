{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"
#include <QtRemoteObjects>

{{module|using_ns}}

// Class

/*!
   \qmltype {{struct}}
   \inqmlmodule {{module}}
{% with doc = struct.comment|parse_doc %}
   \brief {{doc.brief}}

   \note This is a none creatable data object

   Use the module factory method \l {{module.module_name}}Module::create{{struct}} to create
   an instance.

   {{doc.description}}
{% endwith %}
*/

{{class}}::{{class}}()
{% for field in struct.fields %}
{% if loop.first %}    :{% else %}    ,{% endif %} {{field}}({{field|defaultValue}})
{% endfor %}
{
}

void {{class}}::registerTypes(const char* uri)
{
    Q_UNUSED(uri);
    qRegisterMetaType<{{module|ns}}{{class}}>();
    qRegisterMetaTypeStreamOperators<{{module|ns}}{{class}}>();
}

bool {{class}}::operator==(const {{class}} &other) const
{
    return (
{% for field in struct.fields %}
        this->{{field}} == other.{{field}}{% if not loop.last %} &&
{% endif %}
{% endfor %}

    );
}

bool {{class}}::operator!=(const {{class}} &other) const
{
    return !(*this == other);
}

QDataStream &operator<<(QDataStream &stream, const {{class}} &obj) {
    {% for field in struct.fields %}
    stream << obj.{{field}};
    {% endfor %}
    return stream;
}

QDataStream &operator>>(QDataStream &stream, {{class}} &obj) {
    {% for field in struct.fields %}
    stream >> obj.{{field}};
    {% endfor %}
    return stream;
}

{% for field in struct.fields %}
/*!
   \qmlproperty {{field.type}} {{struct}}::{{field}} (field)
{% with doc = field.comment|parse_doc %}
   \brief {{doc.brief}}

   \note A none notifiable property

   {{doc.description}}
{% endwith %}
*/
{% endfor %}
