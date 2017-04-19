# README                                                             {#mainpage}
    @code

     ___ _____ _   ___ _  _____ ___  ___  ___ ___
    / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
    \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
    |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
    embedded.connectivity.solutions.==============

    @endcode

# Introduction                                                   {#introduction}

## Purpose                                                            {#purpose}

The STACKFORCE Cyclic Redundancy Check (CRC) error-detecting code.

Intended to detect unintentional changes to raw data during transmissions.

## Features                                                           {#feature}

The STACKFORCE CRC is written originally for constrained embedded systems but 
is usable within operating systems as well.

It provides an interface to calculate the checksum for a data block at 
once or successively chunk-wise with a finalization step.

## Build instructions                                                   {#build}

The STACKFORCE CRC uses CMake as build system. However it can be 
integrated as sources or as library into your own project. How to build:
Go to root, create build directory:

    cd crc
    mkdir build

and run:

    cmake ..
    make
    sudo make install
    
or to define a custom install directory e.g. devroot:

    cmake .. -DCMAKE_INSTALL_PREFIX=devroot
    make
    make install
    
To generate the doxygen documentation run:

    make doc
