cmake_minimum_required(VERSION 3.9)
project(WordParser CXX)

add_executable(${PROJECT_NAME} Sources/driver.cpp Sources/Dictionary.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
