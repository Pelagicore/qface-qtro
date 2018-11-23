# qface-qtcpp

The reference QtRemoteObjects generator for qface.

It uses the face executable to run the code geenrator.

## Install

    pip install qface>==2.0
    git clone https://github.com/Pelagicore/qface-qtro

## Run

You run the generator by using the qface executbale and passing in the qface.yml document as specification.

    qface --spec qface-qtqml/qtro.yml --dst output sample.qface

This will generate the C++ project inside the oytput folder.


## Help

For help use th qface executable

    qface --help
