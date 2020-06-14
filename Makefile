all: output

output:
	g++ -std=c++17 -o proyecto.o main.cpp

clean:
	rm proyecto.o
