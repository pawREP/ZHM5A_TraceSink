cmake_minimum_required(VERSION 3.5)

project(ZHM5A_TraceSink LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
   src/main.cpp
   src/Connection.h
   src/Connection.cpp
   src/FileLogger.h
   src/FileLogger.cpp
   src/Message.h
   src/Message.cpp
)

add_executable(
	TraceSink
	${SOURCES}
)
