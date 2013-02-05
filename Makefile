jupiter: bin/main.o bin/libjupiter.o
	g++ -o bin/jupiter bin/main.o bin/libjupiter.o

bin/main.o: src/main.cpp src/lib/libjupiter.hpp
	g++ -Wall -W -pedantic -std=c++11 -c src/main.cpp -o bin/main.o

bin/libjupiter.o: src/lib/libjupiter.cpp src/lib/libjupiter.hpp
	g++ -Wall -W -pedantic -std=c++11 -c src/lib/libjupiter.cpp -o bin/libjupiter.o

#.PHONY clean
clean:
	rm ./bin/*
