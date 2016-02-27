cmake_minimum_required(VERSION 3.3)

project(SimpleSearchEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/Document.cpp
        src/Document.h
        src/Term.cpp
        src/Term.h
        src/SearchEngine.cpp
        src/SearchEngine.h
        src/Indexer.cpp
        src/Indexer.h
        src/QueryParser.cpp
        src/QueryParser.h
        src/Utils.cpp
        src/Utils.h
        src/DocumentParser.cpp
        src/DocumentParser.h
        src/Hits.cpp
        src/Hits.h)

add_executable(SimpleSearchEngine ${SOURCE_FILES})