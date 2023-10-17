
make: main.o input.o teste.o hash.o
	g++ input.o hash.o -o input.exe
	g++ main.o hash.o -o main.exe
	g++ teste.o hash.o -o teste.exe
	
teste.o: teste.cpp
	g++ -c teste.cpp

main.o: main.cpp
	g++ -c main.cpp

hash.o: hash.cpp hash.hpp
	g++ -c hash.cpp

input.o: input.cpp
	g++ -c input.cpp

clean:
	rm *.o teste.exe input.exe main.exe