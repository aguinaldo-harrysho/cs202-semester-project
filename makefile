all: wavprocessor
wavprocessor: driver.cpp reader.o
		g++ -o wavprocessor driver.cpp reader.o
reader.o: reader.cpp reader.h
		g++ -c reader.cpp
clean:
		rm wavprocessor *.o 