#ifndef FLIGHTMAP_H_INCLUDED
#define FLIGHTMAP_H_INCLUDED
#include<vector>
#include<iterator>
#include<list>
#include<tuple>
#include "MapInterface.h"

using namespace std;

typedef tuple <string,bool,vector<string> > mapCity; 

class FlightMap:public MapInterface
{
private:
    const string NO_CITY = "NO_CITY";
    list<mapCity> mapDetails;


public:
    void read( string cityFileName , string flightFileName );
    bool cityServed( string aCity ) const;
    void display() const;
    
    vector<string> split( const string& s , char delimiter );
    
    void displayAllCities() const;
    void displayAdjacentCities( string aCity ) const;
    void markVisited( string aCity );
    void unvisitAll();
    string removeSpecials( string str );
    bool isVisited( string aCity ) const;
    bool insertAdjacent( string aCity , string adjCity );
    string getNextCity( string fromCity ) const;
    bool isPath( string originCity , string destinationCity );
};

#include "FlightMap.cpp"

#endif // end
