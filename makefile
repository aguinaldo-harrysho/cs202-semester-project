all: wavprocessor
wavprocessor: driver.cpp reader.o wav.o
		g++ -o wavprocessor driver.cpp reader.o wav.o
reader.o: reader.cpp reader.h
		g++ -c reader.cpp
wav.o: wav.cpp wav.h
		g++ -c wav.cpp
clean:
		rm wavprocessor *.o 