*******
Service
*******

The service consist of s service library and some server code to initialize the service module.

For a simple counter server the code will look like this

.. code-block:: cpp


    int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);

        // Get the server wide remote registry host
        // the registry is reachable normally at
        // Registry=local:counter
        QRemoteObjectRegistryHost* host = Core::instance()->host();

        // create Counter service
        QScopedPointer<CounterService> counterService(new CounterService);
        // publish the service as 'counter.Counter'
        host->enableRemoting(counterService.data(), "counter.Counter");
        qDebug() << "register service at: counter.Counter";

        return a.exec();
    }

Additional contains the server a scaffolded service implementation to satisfy the compiler. It it the task of the developer to modify the implementation to its own needs. This service implementation will not be changed by the generator. You would need to delete it first so that the compiler does generate a new document.
