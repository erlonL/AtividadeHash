
teste: main.o input.o hash.o
	g++ main.o hash.o -o teste.exe
	g++ input.o hash.o -o input.exe
	
main.o: main.cpp
	g++ -c main.cpp

hash.o: hash.cpp hash.hpp
	g++ -c hash.cpp

input.o: input.cpp
	g++ -c input.cpp

clean:
	rm *.o teste.exe input.exe
