all: wavprocessor
wavprocessor: driver.cpp reader.o wav.o echo.o
		g++ -o wavprocessor driver.cpp reader.o wav.o echo.o
reader.o: reader.cpp reader.h
		g++ -c reader.cpp
echo.o: echo.cpp echo.h
		g++ -c echo.cpp
wav.o: wav.cpp wav.h
		g++ -c wav.cpp
clean:
		rm wavprocessor *.o 
