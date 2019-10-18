cmake_minimum_required(VERSION 3.15)
project(graphs_luisparaada)

set(CMAKE_CXX_STANDARD 17)
find_package(RapidJSON)

add_executable(graphs_luisparaada main.cpp CGraph.h ENode.h Json.h)