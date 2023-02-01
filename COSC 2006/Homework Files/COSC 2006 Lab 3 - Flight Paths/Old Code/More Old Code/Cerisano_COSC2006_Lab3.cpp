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
#include <fstream>
#include <string>
#include "Map.h"
using namespace std;

//Function prototypes
void loadCities(FlightMap&, const string&);
void loadFlights(FlightMap&, const string&);
void handleRequests(FlightMap&, const string&);
void printFlightPlan(stack<Flight*>);

//Main program
int main()
{
    FlightMap map;
    loadCities(map, "Cities.txt");
    loadFlights(map, "FlightMap.txt");
    handleRequests(map, "Requests_0.txt");
    return 0;
}

void loadCities(FlightMap & map, const string & fileName)
{
    ifstream inFile(fileName);
    string name;

    while (inFile.peek() != EOF)
    {
        //Every line should just be a city name, so don't worry about parsing
        getline(inFile, name);
        //For whatever god forsaken reason, getLine reads an extra \r at the end
        if (name.at(name.size() - 1) == '\r') name.erase(name.size() - 1);
        map.addCity(name);
    }
}

void loadFlights(FlightMap& map, const string& fileName)
{
    ifstream inFile(fileName);
    string flightLine, fromName, toName; //Used to load one line at a time for parsing
    Flight flight;

    City* from, * to;

    //Read until the end of the file
    while (inFile.peek() != EOF)
    {
        //Read a line and parse it
        getline(inFile, flightLine);

        size_t delim = flightLine.find(' ');
        size_t delim2 = flightLine.find('\t', delim + 1);

        fromName = flightLine.substr(0, delim);
        toName = flightLine.substr(delim + 1, delim2 - delim - 1);

        from = map.getCity(fromName);
        to = map.getCity(toName);

        //Cities could not be found
        if (from == nullptr) continue;
        if (to == nullptr) continue;

        //Add flight to city's flight list
        flight.from = from;
        flight.to = to;

        from->flights.push_back(flight);
    }
}

void handleRequests(FlightMap& map, const string& fileName)
{
    ifstream inFile(fileName);
    string requestLine, fromName, toName; //Used to load one line at a time for parsing
    stack<Flight*> flightPath;
    City* from, * to;

    //Read until the end of the file
    while (inFile.peek() != EOF)
    {
        getline(inFile, requestLine);

        if (requestLine.at(requestLine.size() - 1) == '\r') requestLine.erase(requestLine.size() - 1);

        size_t delim = requestLine.find(' ');

        fromName = requestLine.substr(0, delim);
        toName = requestLine.substr(delim + 1, requestLine.size() - delim - 1);

        cout << "Request is to fly from " << fromName << " to " << toName << endl;

        from = map.getCity(fromName);
        to = map.getCity(toName);

        //Cities could not be found
        if (from == nullptr)
        {
            cout << "HPAir does not service " << fromName << endl;
            continue;
        }
        if (to == nullptr)
        {
            cout << "HPAir does not service " << toName << endl;
            continue;
        }

        //See if we can fly this request
        //Then either notify the client that we can't or print their flight plan
        flightPath = map.getPath(from, to);
        if (flightPath.empty()) cout << "HPAir does not fly from " << from->name << " to " << to->name << endl << endl;
        else printFlightPlan(flightPath);
    }
}

void printFlightPlan(stack<Flight*> flightPlan)
{
    Flight* next;
    while (!flightPlan.empty())
    {
        next = flightPlan.top();
        flightPlan.pop();
        cout << "Fly" << " from " << next->from->name << " to " << next->to->name << endl;
    }
    cout << endl;
}