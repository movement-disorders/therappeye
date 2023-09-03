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

# Message ##############################################################################
msg:
	@echo 'Makefile for Unix based platforms using SFML libraries.'
	@echo 'Use command "make therappeye -f makeUnix.mk" to compile therappeye for a Unix based platform.'
	@echo 'Use command "make clean -f makeUnix.mk" to clean the project folder.'
#########################################################################################

# Compile therappeye ####################################################################
therappeye: slide.o engine.o main.o
	${CXX} ${CXX_FLAGS} slide.o engine.o main.o -o therappeye ${LIBRARIES}

slide.o:
	${CXX} ${CXX_FLAGS} -c src/slide.cpp

engine.o:
	${CXX} ${CXX_FLAGS} -c src/engine.cpp

main.o:
	${CXX} ${CXX_FLAGS} -c src/main.cpp
#########################################################################################

# clean folder ##########################################################################
clean:
	rm -f *.o
	rm -f therappeye
#########################################################################################