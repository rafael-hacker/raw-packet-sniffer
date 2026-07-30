# Raw-packet-sniffer

The raw-packet-sniffer is written in C++ 
using raw sockets 
and sockaddr_ll to avoid segmentation faults in the logging system implemented with fstream.

## Build & usage
    git clone https://github.com/rafael-hacker/raw-packet-sniffer.git
    cd raw-packet-sniffer
    make
## 📁 Project structure
    raw-packet-sniffer/
        *Makefile*
        src/
            *sniffer.cpp*
        libs/
            *defines.h*
        bin/
            *net*

## license 
    Distributed under MIT license. Read LICENSE for details
