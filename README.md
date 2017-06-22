# QFace QtRemoteObjects Generator

This generator does generate a complete micro service solution. It does so by
reading the QFace IDL file and generating a client side plugin and a service
for each interface. Each module will be bundled into one server with an own
service registry where all interfaces from the module will be available.

interface => service
module => server => plugin

As a user you can simply import the QML generated plugin and ensure the server
side generated stub is being implemented.

The QML plugin will automatically connect to the server, which needs to run
when the plugin is loaded.

Each interface service is accessible using the fully qualified name. Different
than the REPC the models are also integrated into the service interface as
described via the QFace IDL.

Open Issues:
- Ideally the client side has a mean to start the server on demand.
- What happens if the customer would like to have only one service registry for all
modules (e.g. the whole system)?
