// Connor Cerisano
// COSC 2006 FA 2020
// Lab 3 - Adaptation of flight map / flight path problem

/*
Write a C++ program to implement the flight map / flight path problem. Use the stack operation of isPath.

Because getNextCity is the primary operation that the search algorithm performs on the flight map,
you should choose an implementation that will efficiently determine which cities are adjacent to given city.

If there are n cities numbered 1,2,...,n, you can use n chains of linked nodes to represent the flight map.

You place a node in chain i for city j if and only if there is a directed path from city i to city j.

Such a data structure is called an adjacency list.
*/

#include <iostream> //input and output
#include <string> //cities will be strings
#include <fstream> //input from a file
#include <algorithm> //vector operations to find() strings

#include "LinkedStack.h" //used for implementation
#include "LinkedBag.h" //used for adjacency list
#include "Map.h"

//Main program
int main()
{
	Map mymap; //Create a flight map
	string originCityName, destinationCityName;

	mymap.readMap();

	//Enter in a custom origin / destination city
	cout << "Enter an origin city: ";
	cin >> originCityName;
	cout << "Enter a destination city: ";
	cin >> destinationCityName;

	//Finds index value of a requested city.
	City originCity = mymap.getIndex(originCityName);
	City destinationCity = mymap.getIndex(destinationCityName);

	cout << mymap.getIndex(originCityName);
	cout << mymap.getIndex(destinationCityName);

	//Display the path (if available)
	cout << "\nPath from " << originCityName << " to " << destinationCityName << ":\n";
	//If no path exists, display an error
	cout << "This path does not exist.\n";

	return 0;
}