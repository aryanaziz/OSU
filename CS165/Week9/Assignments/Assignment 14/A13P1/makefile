CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
CXXFLAGS += -Wno-char-subscripts
#LDFLAGS = -lboost_date_time
LDFLAGS =

OBJS = MyGame.o main.o

SRCS = MyGame.cpp main.cpp

HEADERS = MyGame.hpp

#target: dependencies
#	rule to build
#

main: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o main

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)