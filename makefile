all: driver
driver: driver.cpp
		g++ -o driver driver.cpp
clean:
		rm driver *.o 