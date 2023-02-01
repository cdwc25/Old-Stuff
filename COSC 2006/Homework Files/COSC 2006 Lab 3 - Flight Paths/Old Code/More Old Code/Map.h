#include <vector>
#include <stack> //used for implementation
#include "LinkedStack.h"
#include "LinkedBag.h"
using namespace std;

struct Flight;
struct City
{
    string name;
    vector<Flight> flights;
    bool visited;
    vector<Flight>::iterator tryNext;
};
struct Flight
{
    City* from;
    City* to;
};

// CLASS DEFINITION ///////////////////////////////////////////////////////////
class FlightMap
{
private:
    vector<City> cities;
    static stack<Flight*> convertPathToFlights(stack<City*>& cityPath);
    void unvisitAll();
    City* getNextCity(City* from);

public:
    City* addCity(const string& name);
    City* getCity(const string& name);
    stack<Flight*> getPath(City* from, City* to);
};

////////////////////////////////////////////////////////////////////////////
stack<Flight*> FlightMap::convertPathToFlights(stack<City*>& cityPath)
{
    stack<Flight*> flightPath; //return value
    City* from, * to;

    while (cityPath.size() > 1)
    {
        //Pop the top item off
        //The thing we just popped off is what we're flying to
        //The thing now on the top is where we're flying from
        to = cityPath.top();
        cityPath.pop();
        from = cityPath.top();

        //Now search for a flight that flies from our from city and to our to city
        //And add it onto our itinerary
        for (Flight& flight : from->flights)
        {
            if (flight.to == to)
            {
                flightPath.push(&flight);
                break;
            }
        }
    }
    return flightPath;
}

void FlightMap::unvisitAll()
{
    for (City& city : cities)
    {
        city.visited = false;
        //Start from the beginning of the list
        city.tryNext = city.flights.begin();
    }
}

City* FlightMap::getNextCity(City* from)
{
    for (vector<Flight>::iterator flight = from->tryNext; flight < from->flights.end(); flight++)
    {
        if (!flight->to->visited)
        {
            from->tryNext = flight + 1;
            return flight->to;
        }
    }
    return nullptr;
}

City* FlightMap::addCity(const string& name)
{
    City temp;
    temp.name = name;
    cities.push_back(temp);
    return &cities.back();
}

City* FlightMap::getCity(const string& name)
{
    for (City& city : cities)
    {
        if (city.name == name) return &city;
    }
    return nullptr;
}

stack<Flight*> FlightMap::getPath(City* from, City* to)
{
    //Our return value - a list of cities in reverse order (destination on top)
    //Will be formatted into a correctly ordered list of flights before returning
    stack<City*> cityStack;

    //Set all cities to unvisited, as we are beginning a new search
    unvisitAll();

    //Start with our from city
    cityStack.push(from);
    from->visited = true;

    while (!cityStack.empty() && (cityStack.top() != to))
    {
        //Get an unvisited city adjacent to the city we're looking at
        City* nextCity = getNextCity(cityStack.top());

        //If there is no unvisited city, we've hit a dead end - go backwards
        //Otherwise look at that next city
        if (nextCity == nullptr)
        {
            cityStack.pop();
        }
        else
        {
            cityStack.push(nextCity);
            nextCity->visited = true;
        }
    }
    //format our return value from a reverse list of cities to a correct list of flights
    return convertPathToFlights(cityStack);
}