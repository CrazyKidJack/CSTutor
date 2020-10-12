cmake_minimum_required(VERSION 3.9)
project(WordParser CXX)

#add_executable(${PROJECT_NAME} Sources/driver.cpp Sources/Dictionary.cpp Sources/DictionaryNode.cpp)
add_executable(test Sources/driver2.cpp Sources/Dictionary.cpp Sources/DictionaryNode.cpp)

#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET test PROPERTY CXX_STANDARD 20)
