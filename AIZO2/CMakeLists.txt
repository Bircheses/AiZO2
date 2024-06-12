cmake_minimum_required(VERSION 3.27)
project(AIZO2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(AIZO2
        Sources/Counter.cpp
        Sources/Counter.h
        MainMenu.cpp
        Sources/StaticFunctions.cpp
        Sources/Prim.cpp
        Sources/Prim.h
        Sources/Kruskal.cpp
        Sources/Kruskal.h
        Sources/Containers/PriorityQueueEdge.cpp
        Sources/Containers/PriorityQueueEdge.h
        Sources/Containers/Set.cpp
        Sources/Containers/Set.h
        Sources/Containers/Structures.cpp
        Sources/Dijkstra.cpp
        Sources/Dijkstra.h
        Sources/Containers/PriorityQueueVertex.cpp
        Sources/Containers/PriorityQueueVertex.h
        Sources/BellmannFord.cpp
        Sources/BellmannFord.h
)
