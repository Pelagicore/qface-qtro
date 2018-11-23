# QtRemoteObjects Generator

This project is part of the QFace Generator family.

## Overview

This generator allows you to generator Qt QtRemoteObjects (QtRO) projects from one or more qface API documents. Besides generating the actual QtRO code it also generated the scaffolding for a coplete qmake and cmake based project.


## Installation

You need to have qface installed.

    pip install qface>=2.0

Then clone the repository

    git clone git@github.com:Pelagicore/qface-qtro.git


## Getting Started

Assuming you have a `counter.qface` document you can generate your code

    qface --spec qface-qtro/qtro.yml --out example counter.qface

The code is written in the given output folder.

## Configuration

Please see the help of qface for configuration options.

