cmake_minimum_required(VERSION 4.0)
project(TechnikiEfektywnegoProgramowaniaSem3)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(zad1
        lista1/zad1/main.cpp
        lista1/zad1/main.h)

add_executable(zad2-3
        lista1/zad2-3/main.cpp
        lista1/zad2-3/main.h)

add_executable(zad4
        lista1/zad4/main.cpp
        lista1/zad4/main.h
        lista1/zad4/CTable.cpp
        lista1/zad4/CTable.h)