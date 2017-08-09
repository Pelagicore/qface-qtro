{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

#include <QtRemoteObjects>

class {{class}}Data : public QSharedData
{
public:
    {{class}}Data()
        : QSharedData()
    {% for field in struct.fields %}
        , {{field}}({{field|defaultValue}})
    {% endfor %}
    {
    }
    {{class}}Data(const {{class}}Data &other)
        : QSharedData(other)
    {% for field in struct.fields %}
        , {{field}}(other.{{field}})
    {% endfor %}
    {
    }

public:
{% for field in struct.fields %}
    {{field|returnType}} {{field}};
{% endfor %}
};

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
    : d(new {{class}}Data)
{
}

{{class}}::{{class}}(const {{class}} &other)
    : d(other.d)
{
}

{{class}}::~{{class}}()
{
}

void {{class}}::registerTypes(const char* uri)
{
    Q_UNUSED(uri);
    qRegisterMetaType<{{class}}>();
    qRegisterMetaTypeStreamOperators<{{class}}>();
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
void {{class}}::set{{field|upperfirst}}({{field|parameterType}})
{
    d->{{field}} = {{field}};
}
{{field|returnType}} {{class}}::{{field}}() const
{
    return d->{{field}};
}

{% endfor %}



{{class}} {{class}}::clone()
{
    {{class}} other(*this);
    other.d.detach();
    return other;
}

{{class}} &{{class}}::operator=(const {{class}} &other)
{
    d = other.d;
    return *this;
}

QDataStream& {{class}}::toStream(QDataStream& stream) const
{
  {% for field in struct.fields %}
  stream << d->{{field}};
  {% endfor %}
  return stream;
}

QDataStream& {{class}}::fromStream(QDataStream& stream)
{
  {% for field in struct.fields %}
  stream >> d->{{field}};
  {% endfor %}
  return stream;
}


bool operator==(const {{class}} &left, const {{class}} &right)
{
    return (
{% for field in struct.fields %}
        left.{{field}}() == right.{{field}}(){% if not loop.last %} &&
{% endif %}
{% endfor %}

    );
}

bool operator!=(const {{class}} &left, const {{class}} &right) {
    return !(left == right);
}

QDataStream &operator<<(QDataStream &ds, const {{class}} &obj) {
    return obj.toStream(ds);
}

QDataStream &operator>>(QDataStream &ds, {{class}} &obj) {
    return obj.fromStream(ds);
}
