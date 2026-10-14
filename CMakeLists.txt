cmake_minimum_required(VERSION 3.5)

project(raw_sniffer CXX)

add_executable(raw_sniffer src/sniffer.cpp)
set_target_properties(raw_sniffer PROPERTIES
    LINK_FLAGS_RELEASE "-O2"
)

