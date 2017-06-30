/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtRemoteObjects>


class Core : public QObject
{
    Q_OBJECT
private:
    Core(QObject *parent=nullptr);
public:
    static Core* instance();
    QRemoteObjectNode* node() const;
private:
    static Core* s_instance;
    QRemoteObjectNode* m_node;
};
