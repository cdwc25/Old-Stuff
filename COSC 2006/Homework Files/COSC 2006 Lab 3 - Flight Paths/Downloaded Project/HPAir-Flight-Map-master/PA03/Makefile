PROGRAM_NAME=HPAirV2
CFLAGS=-c -Wall -std=c++11
RM_TARGET=HPAir.log.txt

# By defult, run unit testing after compiling
all: HPAirV2

# Main program for assignment
HPAirV2: PA03.o FlightMapV2.o
	g++ PA03.o FlightMapV2.o -o $(PROGRAM_NAME)

%.o: %.cpp
	g++ $(CFLAGS) $<

clean:
	rm *.o
	rm $(RM_TARGET)