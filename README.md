# QFace QtRemoteObjects Generator

**Work In Progress**

This generator tries to generate a complete micro service solution. It does so by
reading the QFace IDL file and generating a client side plugin and a service
for each interface. Each module will be bundled into one server with an own
service registry where all interfaces from the module will be available.

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

## Install

To install the qface-qtro generator you need to have python3 and pip installed.

```sh
pip3 install qface-qtro
```

## Install Development Version

The development version of qface-qtro requires also the development version of qface. See the qface repository documentation how to install a development version.

### Prerequisites

To install the development version you need to clone the repository and ensure you have checkout the develop branch.

```sh
git clone git@github.com:Pelagicore/qface-qtro.git
cd qface-qtro
git checkout develop
```

The installation requires the python package manager called (pip) using the python 3 version. You can try:

```sh
python3 --version
pip3 --version
```

### Installation

Use the editable option of pip to install an editable version.

```sh
cd qface-qtro
pip3 install --editable .
```

This reads the `setup.py` document and installs the package as reference to this repository. So all changes will be immediatly reflected in the installation.

To update the installation just simple pull from the git repository.
