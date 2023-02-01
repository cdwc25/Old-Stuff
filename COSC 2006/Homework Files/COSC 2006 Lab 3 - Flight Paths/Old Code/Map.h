#include <string> //cities will be strings
#include <fstream> //input from a file
#include <vector>
#include <algorithm>
#include "Node.h"
#include "LinkedStack.h" //used for implementation
using namespace std;

typedef int City; //a City is just an integer.
const int MAX_CITIES = 40; //The number of cities (lines) in Cities.txt
const City NO_CITY = -1; //If no city exists, assign it -1.

class Map
{
private:
    vector<string> cities;
	string cities[MAX_CITIES]; //String array to store city names
    City cityIndex[MAX_CITIES]; //Int array to store encoded city numbers

	bool visited[MAX_CITIES]; //boolean to check if a city has been visited
	Node<City>* map[MAX_CITIES];
	int numCities;

	void unvisitedAll(); // set all cities as unvisited.
	void markVisited(City); // set cities as visited.
	City getNextCity(City); // find the next unvisited city.
	bool isPath(City, City); // check whether a path exists or not.
	bool isVisited(City); // checks to see if a city has been visited or not.
	void insertAdjacent(City, City);
	void splitCities(string, string&, string&);

public:
	Map();
    City getIndex(string);
	void doRequests();
	void readMap();
};

void Map::unvisitedAll() 
{
    for (int index = 0; index < MAX_CITIES; index++)
    {
        visited[index] = false;
    }
}

void Map::markVisited(City city) 
{
    visited[city] = true;
}

City Map::getNextCity(City origin) 
{
    City dest = NO_CITY;
    Node<City>* cityPtr = map[origin];
    while (cityPtr != nullptr && visited[cityPtr->getItem()])
        cityPtr = cityPtr->getNext();
    if (cityPtr != nullptr)
    {
        dest = cityPtr->getItem();
        markVisited(dest);
    }
    return dest;
}

bool Map::isPath(City originCity, City destinationCity) 
{
    LinkedStack<City> cityStack;

    unvisitedAll();

    cityStack.push(originCity);
    markVisited(originCity);

    City topCity = cityStack.peek();
    while (!cityStack.isEmpty() && (topCity != destinationCity)) 
    {
        City nextCity = getNextCity(topCity);

        if (nextCity == NO_CITY)
            cityStack.pop();
        else {
            cityStack.push(nextCity);
            markVisited(nextCity);
        }

        if (!cityStack.isEmpty())
            topCity = cityStack.peek();
    }
    return !cityStack.isEmpty();
}

bool Map::isVisited(City city) 
{
    return visited[city];
}

City Map::getIndex(string cityName) 
{
    City city = 0;
    while (city < numCities && cities[city] != cityName)
        city++;
    if (city >= numCities)
        city = NO_CITY;
    return city;
}

void Map::insertAdjacent(City origin, City dest) 
{
    Node<City>* cityPtr = new Node<City>(dest, map[origin]);
    map[origin] = cityPtr;
}

Map::Map() : numCities(0) 
{
    for (int index = 0; index < MAX_CITIES; index++)
    {
        cities[index] = "";
        visited[index] = false;
        map[index] = nullptr;
    }
}

void Map::doRequests() 
{
  
}

void Map::readMap() 
{
    ifstream cfile("Cities.txt");
    ifstream mfile("FlightMap.txt");

    string word;
    string originCityName, destinationCityName;
    int index = 0, pos;

    if (cfile.is_open())
    {
        while (getline(cfile, word))
        {
            cities[index] = word; //Assign the city a name
            cityIndex[index] = index; //Assign the city a number
            cout << cities[index] << " indx: " << cityIndex[index] << endl;
            index++;
        }
        cfile.close();
    }
    else cout << "Unable to open cfile.";

    //ADD CITIES TO ADJ LIST
    if (mfile.is_open())
    {
        while (getline(mfile, word))
        {
            pos = word.find_first_of(' ');
            originCityName = word.substr(pos + 1);
            destinationCityName = word.substr(0, pos);

            //Read flights. city1 = origin, city2 = destination
            cout << "\nOrigin city: " << originCityName << endl;
            cout << "Destination city: " << destinationCityName << endl;

            //Add destination city to adjacency list for the origin city
            cout << "Adding city " << destinationCityName << " to the adjacency list for city " << originCityName << endl;
        }
        mfile.close();
    }
    else cout << "Unable to open mfile.";

}