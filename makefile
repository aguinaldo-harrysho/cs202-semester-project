wavprocessor: driver.o
	g++ -o wavprocessor driver.o

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o