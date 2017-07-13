=======================
QFace Service Generator
=======================

The QFace based service generator allows you to generator from a QFace IDL document a complete service abstraction with inter process communication.

The generated code is divided into a plugin anf server part. For each module a plugin and a server is generated. On the server side the developer is required to implement the service API.

The IPC is based on the QtRemoteObjects module which was added in the Qt 5.9 release.

.. toctree::
   :maxdepth: 1

   motivation
   usage
   plugin
   server
   examples

Installing
===========

QFace-QtRO is a service generator to generate a Qt based client server solution and is packaged using the python package manager (pip).

To install `qface-qtro` you need to have python3 installed and typically also pip3

.. code-block:: sh

    pip3 install qface-qtro

This installs the python qface-qtro executable and all its dependencies.

You can verify that you have qface installed with

.. code-block:: sh

    qface-qtro --help




