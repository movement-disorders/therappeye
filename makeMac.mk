#
# Makefile for MacOS platforms using the SFML Frameworks
#
# Created By: David J Tinley
# For: movement-disorders/therappeye application by https://github.com/luisgizirian
#
# Last Updated: 08/09/2023
#

# Variables
CXX = clang++
CXX_FLAGS = -g -Wall -std=c++17
FRAMEWORK = -F /Library/Frameworks
FRAMEWORK_OPTS = -framework sfml-window -framework sfml-graphics -framework sfml-system

# Message ##############################################################################
msg:
	@echo 'Makefile for MacOS using SFML frameworks.'
	@echo 'Use command "make therappeye -f makeMac.mk" to compile therappeye for MacOS.'
#########################################################################################

# Compile therappeye ####################################################################
therappeye: presentation.o main.o
	${CXX} ${CXX_FLAGS} presentation.o main.o -o therappeye ${FRAMEWORK} ${FRAMEWORK_OPTS}

presentation.o:
	${CXX} ${CXX_FLAGS} -c src/presentation.cpp

main.o:
	${CXX} ${CXX_FLAGS} -c src/main.cpp
#########################################################################################

# clean folder ##########################################################################
clean:
	rm -f *.o
	rm -rf *.dSYM/
	rm -f therappeye
#########################################################################################