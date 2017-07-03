{% set class = '{0}'.format(enum) %}
#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>
#include <QtQml>

class {{class}}
{
    Q_GADGET
    {{class}}();
public:
    enum E{{enum}} {
{% for member in enum.members %}
        {{member.name}} = {{member.value}},
{% endfor %}
    };
    Q_ENUM(E{{enum}})


    static inline void registerTypes()
    {
        qRegisterMetaType<{{class}}::E{{class}}>();
        qRegisterMetaTypeStreamOperators<{{class}}::E{{class}}>();
    }

    static inline E{{enum}} to{{enum}}(quint8 i, bool *ok = 0)
    {
        if (ok)
            *ok = true;
        switch (i) {
{% for member in enum.members %}
        case {{member.value}} : return {{member}};
{% endfor %}
        default:
            if (ok)
                *ok = false;
            return {{enum.members|first}};
        }
    }
};

inline QDataStream &operator<<(QDataStream &ds, const {{class}}::E{{enum}} &obj)
{
    quint8 val = obj;
    ds << val;
    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, {{class}}::E{{enum}}  &obj) {
    bool ok;
    quint8 val;
    ds >> val;
    obj = {{class}}::to{{enum}}(val, &ok);
    if (!ok)
        qWarning() << "Received an invalid enum value for typeStatus, value =" << val;
    return ds;
}

#endif // {{class|upper}}_H

