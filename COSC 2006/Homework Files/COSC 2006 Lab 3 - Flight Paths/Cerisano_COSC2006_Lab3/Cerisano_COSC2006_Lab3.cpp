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
#include <fstream> //to read input files
#include <string> //used for city names
#include <vector> //used to store Flight and City data
#include <stack> //used for implementation
#include "LinkedStack.h"
#include "LinkedBag.h"
using namespace std;

struct Flight; //Declare Flight before City so vector<Flight> can be used
struct City //City struct, used in class FlightMap
{
    string name; //store the name of the city
    vector<Flight> flights; //store a list of flights to and from the City
    bool visited; //store if the city is visited or not
    vector<Flight>::iterator tryNext; //iterator to go through list of cities
};
struct Flight
{
    //store origin and the destination cities
    City* from;
    City* to;
};

class FlightMap //FLIGHTMAP CLASS
{
private:
    vector<City> cities;
    static stack<Flight*> convertPathToFlights(stack<City*>& cityPath); //Converts a stack of cities into a stack of flights
    City* getNextCity(City* from); //chooses an unvisited city adjacent to the origin city
    void unvisitAll(); //set all cities in the map to unvisited

public:
    stack<Flight*> getPath(City* from, City* to); //modified version of isPath
    City* addCity(const string& name); //function to add a city to the flight map
    City* getCity(const string& name); //get a city from the flight map
};

stack<Flight*> FlightMap::convertPathToFlights(stack<City*>& cityPath)
{
    stack<Flight*> flightPath; //the return value of the function
    City* from, * to; //origin and destination cities

    while (cityPath.size() > 1) //Make sure that a path exists
    {
        to = cityPath.top(); //the top element of the stack is the destination city
        cityPath.pop(); //remove it
        from = cityPath.top(); //new origin city

        //Search for a flight that flies from the origin city to the destination city
        for (Flight& flight : from->flights)
        {
            if (flight.to == to) //If the destination city is found
            {
                flightPath.push(&flight); //Add the flight to the flight path
                break; //stop searching
            }
        }
    }
    return flightPath; //return our flight plan
}

void FlightMap::unvisitAll()
{
    for (City& city : cities) //For every city in our vector list of cities
    {
        city.visited = false; //mark it as NOT visited
        city.tryNext = city.flights.begin(); //iterate at the beginning of the list
    }
}

City* FlightMap::getNextCity(City* from) //Choose an adjacent city to our origin city
{
    for (vector<Flight>::iterator flight = from->tryNext; flight < from->flights.end(); flight++)
    {
        if (!flight->to->visited) //if the destination city is visited
        {
            from->tryNext = flight + 1;
            return flight->to; //pointer to the next city
        }
    }
    return nullptr; //null pointer if there are no adjacent unvisited cities
}

City* FlightMap::addCity(const string& name) //Adds a new city to the flight map
{
    City temp; //create a temp city
    temp.name = name;
    cities.push_back(temp); //add the city to our cities vector
    return &cities.back(); //return the added city
}

City* FlightMap::getCity(const string& name) //Get a city from the map with an existing name
{
    for (City& city : cities) //for every city in our vector list of cities
    {
        if (city.name == name) return &city; //if a name is found, return it.
    }
    return nullptr; //otherwise, return null
}

stack<Flight*> FlightMap::getPath(City* from, City* to)
{
    stack<City*> cityStack; //list of cities in reverse order.
    unvisitAll(); //Set all cities to unvisited to start up a new search

    //Start with the origin city. Mark it as visited.
    cityStack.push(from);
    from->visited = true;

    //Make sure the stack isn't empty and the top isn't the destination city
    while (!cityStack.empty() && (cityStack.top() != to))
    {
        //Get an unvisited city adjacent to the city at the top of the stack
        City* nextCity = getNextCity(cityStack.top());

        //If there are no unvisited cities, it is a dead end, go back.
        if (nextCity == nullptr)
        {
            cityStack.pop();
        }
        else //If there are unvisited cities, evaluate the next city
        {
            cityStack.push(nextCity);
            nextCity->visited = true;
        }
    }
    //Convert the reversed list of cities into a list of flights
    return convertPathToFlights(cityStack);
}

//Function prototypes for main()
void loadCities(FlightMap&, const string&);
void loadFlights(FlightMap&, const string&);
void handleRequests(FlightMap&, const string&);

//Main program
int main()
{
    FlightMap map; //Create a flight map
    City* from, * to; //Origin and destination cities
    string fromName, toName;
    stack<Flight*> flightPath;
    Flight* next; //To get the next flight in a path

    loadCities(map, "Cities.txt");
    loadFlights(map, "FlightMap.txt");
    handleRequests(map, "Requests_0.txt");

    //Enable the user to test a custom path
    cout << "Enter an origin city: ";
    cin >> fromName;
    cout << "Enter a destination city: ";
    cin >> toName;

    //Note: the same code below exists in handleRequests()
    from = map.getCity(fromName);
    to = map.getCity(toName);
    flightPath = map.getPath(from, to);
    if (flightPath.empty()) cout << "No path exists from " << from->name << " to " << to->name << endl << endl;
    else
    {
        while (!flightPath.empty())
        {
            next = flightPath.top();
            flightPath.pop();
            cout << "Fly" << " from " << next->from->name << " to " << next->to->name << endl;
        }
        cout << endl;
    }
    return 0;
}

void loadCities(FlightMap& map, const string& fileName)
{
    ifstream inFile(fileName);
    string name;

    while (inFile.peek() != EOF) //Until the end of the file is reached
    {
        getline(inFile, name); //Get city names line by line
        map.addCity(name); //Add the city
    }
}

void loadFlights(FlightMap& map, const string& fileName)
{
    ifstream inFile(fileName);
    string flightLine, fromName, toName; //Used to load one line at a time for parsing
    Flight flight; //Placeholder flight
    City* from, * to; //Origin and destination cities

    //Read until the end of the file
    while (inFile.peek() != EOF)
    {
        getline(inFile, flightLine); //Get the list of flights line by line

        //note: find() finds the position value.
        int delim = flightLine.find(' ');
        int delim2 = flightLine.find('\t', delim + 1);

        //Parse our origin and destination city names
        fromName = flightLine.substr(0, delim);
        toName = flightLine.substr(delim + 1, delim2 - delim - 1);

        //Set our local origin/destination cities to the corresponding existing ones
        from = map.getCity(fromName);
        to = map.getCity(toName);

        //Add flight to the origin/destination city's flight list
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
    Flight* next; //To get the next flight in a path
    City* from, * to; //Origin and destination cities

    //Read until the end of the file
    while (inFile.peek() != EOF)
    {
        getline(inFile, requestLine); //read line by line

        //find a space in the request to identify the origin and destination cities
        int delim = requestLine.find(' ');

        //Parse our origin and destination city names
        fromName = requestLine.substr(0, delim);
        toName = requestLine.substr(delim + 1, requestLine.size() - delim - 1);

        //Display our parsed information
        cout << "Request is to fly from " << fromName << " to " << toName << endl;

        //Set our local origin/destination cities to the corresponding existing ones
        from = map.getCity(fromName);
        to = map.getCity(toName);

        flightPath = map.getPath(from, to); //Find the path from the origin city to the destination city

        //If flightPath doesn't contain data, assume no path exists.
        if (flightPath.empty()) cout << "No path exists from " << from->name << " to " << to->name << endl << endl;

        //If flightPath does contain data, print out the results.
        else 
        {
            while (!flightPath.empty())
            {
                next = flightPath.top();
                flightPath.pop();
                cout << "Fly" << " from " << next->from->name << " to " << next->to->name << endl;
            }
            cout << endl;
        }
    }
}