{# Copyright (c) Pelagicore AB 2016 #}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtQml>
#include <QtRemoteObjects>

class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    explicit Plugin(QObject* parent=nullptr);
    void initializeEngine(QQmlEngine *engine, const char *uri);
    void registerTypes(const char *uri);
    static Plugin* instance();
private:
    static Plugin* s_instance;
    QRemoteObjectNode *m_node;
};
