# Raw-packet-sniffer

The raw-packet-sniffer is written in C++ 
using raw sockets 
and sockaddr_ll to avoid segmentation faults in the logging system implemented with fstream.

## Build & usage
    git clone https://github.com/rafael-hacker/raw-packet-sniffer.git
    cd raw-packet-sniffer
    make
## 📁 Project structure
```text
├── LICENSE
├── Makefile
├── README.md
├── bin
│   └── net
├── libs
│   └── defines.h
└── src
    └── sniffer.cpp

```

📜 MIT License
Free to break, modify and burn however you wish.
