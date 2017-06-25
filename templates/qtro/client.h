{% set class = '{0}Client'.format(interface) %}

#ifndef {{interface|upper}}_CLIENT_H
#define {{interface|upper}}_CLIENT_H

#include <QtCore>

class {{class}} : public QObject {
    Q_OBJECT    
};

#endif // {{interface|upper}}_CLIENT_H
