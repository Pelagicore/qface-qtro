=======================
QFace Service Generator
=======================

The ``QFace`` based service generator allows you to generator from a QFace IDL document a complete service abstraction with inter process communication using ``QtRemoteObjects``.

The generated code is divided into a client and service part. For each QFace module a static client library and a static service library is generated.

On the client side there are additional QML plugins created. On the server side a simple sample server exectuble is generated.

The IPC is based on the QtRemoteObjects module which was added in the Qt 5.9 release.

.. toctree::
   :maxdepth: 1

   motivation
   usage
   client
   service
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


Development
===========

To install the development version you need to install the package form the git repository.

.. code-block:: sh

    git clone git@github.com:Pelagicore/qface-qtro.git
    cd qface-qtro
    pip3 install --editable .

Be aware the development version is always cutting edge and often requires also the development version of qface.

