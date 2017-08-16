=====
Usage
=====

After you have installed qface-qtro you need to create an interface file in the QFace format.

For example this:

.. code-block:: js

    // counter.qface
    module counter 1.0

    interface Counter {
        int sum;
        void increment();
        void decrement();
        Status status;
    }

    enum Status {
        Null,
        Ready
    }

Create a folder called ``counter`` and an ``interface`` and ``counter`` sub-folder.

.. code-block:: sh

    mkdir counter
    cd counter
    mkdir interfaces
    mkdir counter
    touch interface/counter.qface

Now copy the qface example into the counter.qface document and call

.. code-block:: sh

    qface-qtro interfaces counter

The generator will read all qface files from the interface folder and use the target folder name to generate a new Qt project.

You can now open the Qt project using QtCrator. The project is at ``counter/counter.pro``.

The generator crates a ``lib_client_counter`` and a ``lib_service_counter``. Additional a QML plugin called ``plugin_counter`` and a ``server_counter`` executable.

Implement the Service
=====================

To make the server usable you need to implement the ``CounterService`` on the server side.

.. code-block:: cpp

    void CounterService::increment()
    {
        setSum(sum() + 1);
        return ;
    }

    void CounterService::decrement()
    {
        setSum(sum() - 1);
        return ;
    }

The increment and decrement methods are called from the client and the service sum is updated. The changes are then propagated back to the clients sum property automatically.

.. note::

    The service document ``counterservice.cpp`` is marked as preserved and any changes to it will stay intact in the next generator run. Which means also if you change the API of the service it is your duty to update the implementation document.


Launch the Server
=================

You need to launch the server from the build folders bin directory.

.. code-block:: sh

    ./build/bin/counter_server

This will start the server and listens for client connections. If you rebuild the service code, please ensure you also restart the server.

Using the QML Client
====================

You can use the client API in a pure QML fashion by this

.. code-block:: qml

    import QtQuick.Controls 2.1

    import counter 1.0

    ApplicationWindow {
        id: root
        width: 480
        height: 320

        Counter {
            id: counter
        }

        Button {
            anchors.centerIn: parent
            text: counter.sum
            onClicked: counter.increment()
        }
    }

You need to launch the QML document with the imports path from the build folder.

.. code-block:: sh

    qmlscene -I build/imports  Main.qml

Using the CPP Client
====================

You can also use the counter client using the static CPP client library.

For this you need to add the ``use_lib_client_counter.pri`` project file to your application pro file and register the module types.

.. code-block:: sh

    include( $$SOURCE_DIR/libs/lib_client_counter/use_lib_client_counter.pri )

In your ``main.cpp`` you need to call the interface registry.

.. code-block:: cpp

    #include <QtGui>
    #include <QtQml>


    #include "counter.h"

    int main(int argc, char** argv)
    {
        QGuiApplication app(argc, argv);

        counter::Counter::registerQmlType();

        QQmlApplicationEngine engine;
        engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
        if (engine.rootObjects().isEmpty()) {
            return -1;
        }
        return app.exec();
    }


Configuration
=============

The client and server are linked through a shared ``server.conf`` configuration file in the ``lib_shared`` static library.

There inside is the service registry URL listed for each module.

.. code-block:: ini

    [counter]
    Registry=local:counter

In this case it means we would use a local socket named counter (the module name) to expose the ``Counter`` service.

