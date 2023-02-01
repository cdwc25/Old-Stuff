/** ADT Map
    Developed by Ben Juliano @ Chico State
    based on the ADT flight map description provided in
    Carrano & Henry 7e (2017), p. 176.
    @file MapInterface.h */

#ifndef MAP_INTERFACE_
#define MAP_INTERFACE_

#include <string>

using namespace std;

class MapInterface
{
    public:
    
    /** Reads flight information into the flight map. 
        @param cityFileName The filename of the file containing
            cities served.
        @param flightFileName The filename of the file containing
            origin and detination city pairs for each flight.
        Assume the filenames exist and are of the right format. */
        virtual void read( string cityFileName , string flightFileName ) = 0;

    /** Determines if a city is served.
        @param aCity Name of a city.
        @return true if aCity is served; false, otherwise. */
        virtual bool cityServed( string aCity ) const = 0;
        
    /** Displays flight map information. */
        virtual void display() const = 0;
        
    /** Displays the names of all the cities served. */
        virtual void displayAllCities() const = 0;

    /** Displays all cities that are adjacent to a given city.
        @param aCity Name of a city served. */
        virtual void displayAdjacentCities( string aCity ) const = 0;

    /** Marks a city as visited.
        @param aCity Name of a city served. */
        virtual void markVisited( string aCity ) = 0;

    /** Clears marks on all cities. */
        virtual void unvisitAll() = 0;

    /** Sees whether a city was visited.
        @param aCity Name of a city served.
        @return true if aCity is marked as visited; false, otherwise. */
        virtual bool isVisited( string aCity ) const = 0;

    /** Inserts a city adjacent to another city in a flight map.
        @param aCity Name of a city served; origin city.
        @param adjCity Name of a city served; destination city.
        @return true if adjCity successfully added as adjacent to aCity;
            false, otherwise. */
        virtual bool insertAdjacent( string aCity , string adjCity ) = 0;

    /** Returns the next unvisited city, if any, that is adjacent to a given city.
        Returns a sentinel value if no unvisited adjacent city was found.
        @param fromCity Name of a city served; origin city.
        @return Name of next unvisited city adjacent to fromCity; 
            otherwise, returns the empty string "". */
        virtual string getNextCity( string fromCity ) const = 0;

    /** Tests whether a sequence of flights exists between two cities.
        @param originCity Name of a city served; origin city.
        @param destinationCity Name of a city served; destination city.
        @return true if there exists a sequence of flights between
            originCity and destinationCity; false, otherwise. */
        virtual bool isPath( string originCity , string destinationCity ) = 0;

}; // end MapInterface

#endif