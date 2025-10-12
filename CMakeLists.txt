cmake_minimum_required(VERSION 3.5)
project(TechnikiEfektywnegoProgramowaniaSem3)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(zad1
        lista1/zad1/zad1.cpp
        lista1/zad1/zad1.h)

add_executable(zad2-3
        lista1/zad2-3/zad2.cpp
        lista1/zad2-3/zad2.h)

add_executable(zad4
        lista1/zad4/zad4.cpp
        lista1/zad4/zad4.h
        lista1/zad4/CTable.cpp
        lista1/zad4/CTable.h)