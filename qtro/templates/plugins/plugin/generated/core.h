/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtRemoteObjects>

{{module|open_ns}}

class Core : public QObject
{
    Q_OBJECT
private:
    Core(QObject *parent=nullptr);
public:
    static Core* instance();
    static void registerTypes(const char *uri);
    QRemoteObjectNode* node() const;
private:
    void reportError(QRemoteObjectNode::ErrorCode code);
private:
    static Core* s_instance;
    QRemoteObjectNode* m_node;
};

{{module|close_ns}}
