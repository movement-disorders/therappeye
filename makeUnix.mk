#
# Makefile for Unix/Linux platforms using the SFML Libraries
#
# Created By: David J Tinley
# For: movement-disorders/therappeye application by https://github.com/luisgizirian
#
# Last Updated: 08/09/2023
#

# Variables
CXX = g++
CXX_FLAGS = -g -Wall -std=c++17
LIBRARIES = -lsfml-window -lsfml-graphics -lsfml-system

# Message
msg:
	@echo 'Makefile for Unix based platforms using SFML libraries.'
	@echo 'Use command "make therappeye -f makeUnix.mk" to compile therappeye for a Unix based platform.'
	@echo 'Use command "make clean -f makeUnix.mk" to clean the project folder.'

# Compile therappeye
therappeye: presentation.o main.o
	${CXX} ${CXX_FLAGS} presentation.o main.o -o therappeye ${LIBRARIES}

presentation.o:
	${CXX} ${CXX_FLAGS} -c src/presentation.cpp

main.o:
	${CXX} ${CXX_FLAGS} -c src/main.cpp

clean:
	rm -f *.o
	rm -rf *.dSYM/
	rm -f therappeye