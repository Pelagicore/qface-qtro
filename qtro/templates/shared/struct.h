{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H


#include <QtCore>


class {{class}}Data;

class {{class}}
{
    Q_GADGET
{% for field in struct.fields %}
    Q_PROPERTY({{field|returnType}} {{field}} READ {{field}} WRITE set{{field|upperfirst}})
{% endfor %}

public:
    {{class}}();
    {{class}}(const {{class}} &other);
    ~{{class}}();

    static void registerTypes();
    Q_INVOKABLE {{class}} clone();

    {{class}} &operator=(const {{class}} &other);

{% for field in struct.fields %}
    void set{{field|upperfirst}}({{field|parameterType}});
    {{field|returnType}} {{field}}() const;

{% endfor %}


private:
    QExplicitlySharedDataPointer <{{class}}Data> d;
};

bool operator==(const {{class}} &left, const {{class}} &right);
bool operator!=(const {{class}} &left, const {{class}} &right);
QDataStream &operator<<(QDataStream &ds, const {{class}} &obj);
QDataStream &operator>>(QDataStream &ds, {{class}} &obj);

Q_DECLARE_METATYPE({{class}})

#endif // {{class|upper}}_H
