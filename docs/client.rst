******
Client
******

The client is created based on the module information from the QFace document.

Lets review the following example.

.. code-block:: js

    module org.example.fs 1.0

    interface FileSystem {
        Entry current
        model<Entry> entries;
        Filter filter;
        Sort sort;
        void cd(string path);
        void cdUp();
        Entry entry(string path);
    };

    struct Entry {
        string name;
        string path;
        bool isDir;
        bool isFile;
        string created;
        string modified;
    };

    flag Filter {
        Dirs,
        Files,
        Special,
    };

    enum Sort {
        Name,
        Created
    };


A module like ``module org.example.fs 1.0`` will result into a CPP library called ``client_org_example_fs`` and the client will have the ``org::example::fs`` namespace.

An interface inside the module will be exposed as a QML plugin and can be used from any QML file.

.. code-block:: qml

    // Main.qml
    import QtQuick 2.8
    import QtQuick.Controls 2.1
    import QtQuick.Layouts 1.3
    import org.example.fs 1.0

    ApplicationWindow {
        id: root
        width: 400
        height: 800
        visible: true

        FileSystem {
            id: fs
        }

        ColumnLayout {
            anchors.fill: parent
            Button {
                Layout.fillWidth: true
                text: 'Up'
                onClicked: fs.cdUp();
            }

            ListView {
                id: view
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: fs.entries
                delegate: ItemDelegate {
                    width: view.width
                    text: model.name
                    onClicked: {
                        if(model.isDir) {
                            fs.cd(model.path)
                        }
                    }
                }
            }
        }
    }

You can clearly see that the module URi is used to define the CPP namespace and the object type is based on the interface name.
The properties and methods work as expected. For the model property an own client side model is generated which understand the roles and templated type, in this case the ``Entry`` struct.


Using from C++
==============

To make the types available you first need to include the use library project include file called ``include( $$SOURCE_DIR/libs/lib_client_org_example_fs/use_lib_client_org_example_fs.pri )``. This include will setup the correct linking command and the incldue paths.

To use the client now from the application you need to register the QML types in your main cpp file.

.. code-block:: cpp

    #include <QtGui>
    #include <QtQml>


    #include "filesystem.h"

    int main(int argc, char** argv)
    {
        QGuiApplication app(argc, argv);

        org::example::fs::FileSystem::registerQmlType();

        QQmlApplicationEngine engine;
        engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
        if (engine.rootObjects().isEmpty()) {
            return -1;
        }
        return app.exec();
    }

.. note::

    When you launch the application you need to ensure the service is already running.


