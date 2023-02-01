// CLASS IMPLEMENTATION INFORMATION ///////////////////////////////////////////
/**
  * @file FlightMapV1.cpp
  *
  * @brief FlightMap class implementation
  *
  * @version 1.00
  *          Alexander Novotny
  *          First version
  *
  */
#include "FlightMap.h"

/**
  * @brief Converts a backwards stack of cities into a proper stack of flights
  *
  * @param[in] cityPath
  *            A stack of cities with the destination city on top and origin on bottom
  *            which describes a path of flights to reach the destination.
  *            Can be empty, in which case the returned stack will also be empty
  *
  * @par Algorithm
  *      Pops each city off and tries to find a flight from the next city to
  *      that city, then adds that flight to the next stack.
  *
  * @return A stack of flights from the origin city to the destination city
  *
  */
std::stack<Flight*> FlightMap::convertPathToFlights ( std::stack<City*>& cityPath )
{
    std::stack<Flight*> flightPath; //return value
    City* from, *to;

    while ( cityPath.size() > 1)
    {
        //Pop the top item off
        //The thing we just popped off is what we're flying to
        //The thing now on the top is where we're flying from
        to = cityPath.top ();
        cityPath.pop ();
        from = cityPath.top ();

        //Now search for a flight that flies from our from city and to our to city
        //And add it onto our itinerary
        for ( Flight& flight : from->flights )
        {
            if ( flight.to == to )
            {
                flightPath.push ( &flight );
                log ( "Flight from " + flight.from->name 
                      + " to " + flight.to->name );
                break;
            }
        }
    }

    return flightPath;
}

/**
  * @brief Sets all cities in the map to unvisited
  */
void FlightMap::unvisitAll ()
{
    for ( City& city : cities )
    {
        city.visited = false;
    }
}

/**
  * @brief Chooses an unvisited city adjacent to from
  *
  * @param[in] from
  *            Pointer to the city we should check for adjacencies
  *
  * @return Pointer to the next city, or nullptr if no adjacent unvisited cities
  *
  */
City* FlightMap::getNextCity ( City* from )
{
    for ( Flight& flight : from->flights )
    {
        if ( !flight.to->visited )
        {
            return flight.to;
        }
    }
    return nullptr;
}

/**
  * @brief Adds a new city to the map
  *
  * @param[in] name
  *            Name of the new city
  *
  * @return Pointer to the new city
  *
  */
City* FlightMap::addCity ( std::string& name )
{
    City temp;
    temp.name = name;
    cities.push_back ( temp );
    return &cities.back ();
}

/**
  * @brief Gets a city from the map with a specific name
  *
  * @param[in] name
  *            The name of the city to search for
  *
  * @return Pointer to the found city, or nullptr if not found
  *
  */
City* FlightMap::getCity ( std::string& name )
{
    for ( City& city : cities )
    {
        if ( city.name == name )
        {
            return &city;
        }
    }
    return nullptr;
}

/**
  * @brief Finds path of flights to get from one city to another
  *
  * @param[in] from
  *            Pointer to the city to start searching from
  *
  * @param[in] to
  *            Pointer to the city to search for
  *
  * @par Algorithm
  *      Starting with from, searches through each adjacent unvisited city
  *      and then repeats until it either finds to or runs out of adjacent cities
  *
  * @return A stack of flights from the origin city to the destination city
  *         Or an empty stack if no path could be found
  *
  */
std::stack<Flight*> FlightMap::getPath ( City* from, City* to )
{
    //Our return value - a list of cities in reverse order (destination on top)
    //Will be formatted into a correctly ordered list of flights before returning
    std::stack<City*> cityStack;

    //Set all cities to unvisited, as we are beginning a new search
    unvisitAll ();

    log ( "\nAttempting to find path from " + from->name + " to " + to->name );

    //Start with our from city
    cityStack.push ( from );
    from->visited = true;

    while ( !cityStack.empty () && ( cityStack.top () != to ) )
    {
        //Get an unvisited city adjacent to the city we're looking at
        City* nextCity = getNextCity ( cityStack.top() );

        //For formatting the log file to read the stack easily
        for ( unsigned int tabs = 1; tabs < cityStack.size (); tabs++ )
        {
            log ( "\t", false );
        }

        //If there is no unvisited city, we've hit a dead end - go backwards
        //Otherwise look at that next city
        if ( nextCity == nullptr )
        {
            log ( "dead end" );
            cityStack.pop ();
        }
        else
        {
            log ( "Looking at " + nextCity->name );
            cityStack.push ( nextCity );
            nextCity->visited = true;
        }
    }

    if ( cityStack.empty () )
    {
        log ( "Failed to find path" );
    }
    else
    {
        log ( "Found path..." );
    }

    //format our return value from a reverse list of cities to a correct list of flights
    return convertPathToFlights(cityStack);
}


/**
  * @brief Logs information to file defined in LOG_FILE
  *
  * @param[in] text
  *            Text to log
  *
  * @param[in] newLine
  *            Whether std::endl should be printed at the end. Defaults to true
  *
  * @note If LOG_FILE not defined, nothing will happen
  *
  */
void log ( const std::string& text, bool newLine )
{
#ifdef LOG_FILE
    static std::ofstream logFile ( LOG_FILE );
    logFile << text;
    if ( newLine ) logFile << std::endl;
#endif
}