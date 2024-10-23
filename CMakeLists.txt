cmake_minimum_required(VERSION 3.29)
project(PPD_Lab1_C)

set(CMAKE_CXX_STANDARD 20)

add_executable(PPD_Lab1_C main.cpp
        convolutionsThreadedRows.h
        convolutionsThreadedRows.cpp
        utils.h
        utils.cpp
        ConvolutionsThreadedColumns.h
        ConvolutionsThreadedColumns.cpp)
