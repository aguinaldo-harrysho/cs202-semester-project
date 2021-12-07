all: wavprocessor
wavprocessor: driver.cpp reader.o wav.o echo.o gain.o normalizer.o
		g++ -o wavprocessor driver.cpp reader.o wav.o echo.o
reader.o: reader.cpp reader.h
		g++ -c reader.cpp
echo.o: echo.cpp echo.h
		g++ -c echo.cpp
gain.o: gain.cpp gain.h
		g++ -c gain.cpp
normalizer.o: normalizer.cpp normalizer.h
		g++ -c normalizer.cpp
wav.o: wav.cpp wav.h
		g++ -c wav.cpp
clean:
		rm wavprocessor *.o 
