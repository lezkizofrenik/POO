# Carmensita

CXX = clang++
CPPFLAGS = -DP0 -I../Test-auto -I.
CXXFLAGS = -std=c++11 -Wall -g
VPATH = ../Test-auto:.

all: test-P0-auto tet-P0-consola

test-P0-auto: test-caso0-fecha-auto.o \
	test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-P0-consola.o: fecha.hpp cadena.hpp

fecha.o:
cadena.o:

clean : $(RM) *.o test-P0-consola test-P0-auto