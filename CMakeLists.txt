cmake_minimum_required(VERSION 3.5)
project(TEPsem3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(zad1
        lista1/zad1/zad1.cpp
        lista1/zad1/zad1.h
        lista2/Tester.cpp
        lista2/Tester.h)

add_executable(zad2-3
        lista1/zad2-3/zad2.cpp
        lista1/zad2-3/zad2.h)

add_executable(zad4
        lista1/zad4/zad4.cpp
        lista1/zad4/zad4.h
        lista1/zad4/CTable.cpp
        lista1/zad4/CTable.h)

add_executable(lista2
        lista2/Number.cpp
        lista2/Number.cpp
        lista2/Tester.cpp
        lista2/Tester.h
)
add_executable(lista3
        lista3/Tree/Tree.cpp
        lista3/Tree/Tree.h
        lista3/Tree/Node.cpp
        lista3/Tree/Node.h
        lista3/Tester.cpp
        lista3/Interface.cpp
        lista3/Interface.h)

add_executable(lista4 lista4/Error.h
        lista4/Result.h
        lista4/Tester.cpp
        lista4/Tester.h
        lista4/TreeAdapter.cpp
        lista4/TreeAdapter.h
        lista4/FileSaver.h
        lista3/Tree/Tree.cpp
        lista3/Tree/Tree.h
        lista3/Tree/Node.cpp
        lista3/Tree/Node.h
        lista3/Interface.cpp
        lista3/Interface.h)
add_executable(lista5
        lista5/Tester.cpp
        lista5/SmartPointer.h
        lista5/SmartPointerFixed.h
        lista4 lista4/Error.h
        lista4/Result.h
        lista4/TreeAdapter.cpp
        lista4/TreeAdapter.h
        lista3/Tree/Tree.cpp
        lista3/Tree/Tree.h
        lista3/Tree/Node.cpp
        lista3/Tree/Node.h)
