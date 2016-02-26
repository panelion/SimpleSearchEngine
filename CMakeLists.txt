cmake_minimum_required(VERSION 3.3)
project(SimpleSearchEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp Indexer.cpp Indexer.h Document.cpp Document.h Term.cpp Term.h SearchEngine.cpp SearchEngine.h IStore.h MapStore.cpp TermInfo.cpp TermInfo.h)
set(SOURCE_FILES main.cpp Document.cpp Document.h Term.cpp Term.h SearchEngine.cpp SearchEngine.h Indexer.cpp Indexer.h QueryParser.cpp QueryParser.h Utils.cpp Utils.h)

add_executable(SimpleSearchEngine ${SOURCE_FILES})