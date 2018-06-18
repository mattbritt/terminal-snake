# makefile for Final Project
# 
# Program name:  Console Snake
# Author:  Matt Britt
# Date:  11/30/17
# Description:  Snake in the console.
#

PROGRAM = snake      # this is the compiled program name

CXX = g++
CXXFLAGS = -std=c++0x
#CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

default: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${HEADERS} ${SOURCES} -o ${PROGRAM}

clean:
	rm -f $(OBJECTS) ${PROGRAM}

.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck  --track-origins=yes --leak-check=full --show-leak-kinds=all ${PROGRAM}
