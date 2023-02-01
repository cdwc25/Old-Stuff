#include "FlightMap.h"
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stack>

using namespace std;

vector<string> FlightMap :: split( const string& s , char delimiter )
{
  vector<string> tokens;          // vector of tokens
  string token;                   // a single token
  istringstream tokenStream(s);   // an input string stream
        // Tokenize s by grabbing individual tokens
  while( getline( tokenStream , token , delimiter ) )
    tokens.push_back(token);    // add found token

  return tokens;
}

string FlightMap :: removeSpecials( string str )
{
   	    int i=0,len=str.length();
   	    while(i<len) // Check every character
   	    {
            char c=str[i];
            if( !(((c>='0')&&(c<='9')) || ((c>='A')&&(c<='Z')) || ((c>='a')&&(c<='z')) || (c==' ') || (c=='-')) ) 
            {
                str.erase(i,1); // Delete "bad" character
                --len;          // and adjust length
            }
            i++;
        }
        return str;
}


/** Reads flight information into the flight map. 
        @param cityFileName The filename of the file containing
            cities served.
        @param flightFileName The filename of the file containing
            origin and detination city pairs for each flight.
        Assume the filenames exist and are of the right format. */

void FlightMap :: read( string cityFileName , string flightFileName )
{
  
  ifstream cityFile, flightFile;
  string input;                 // input string to hold 1 line from cin
  char   delimiter = ',';       // what separates tokens in the input string
  vector<string> listOfTokens,cityNames;  // store tokens of input here
  vector<string> origin, destination;
  vector<bool> marking;
  
  

  cityFile.open(cityFileName);
  
  if(cityFile.is_open())
  {
      while(getline(cityFile,input))
      {
          if(cityNames.size()>19)
          break;
          
          cityNames.push_back(removeSpecials(input));
      }
      cityFile.close();
  }
  else
    cout<<"Error opening File"<<endl;
  
  flightFile.open(flightFileName);
    
    if(flightFile.is_open())
  {
      while(getline(flightFile, input))
      {
        listOfTokens = split( input , delimiter );
        
        for(unsigned j=0;j<listOfTokens.size();j++)
         { 
           if(j%2==0)
           {origin.push_back(removeSpecials(listOfTokens[j]));}
           else
           {destination.push_back(removeSpecials(listOfTokens[j]));}
         }
      }
      
      flightFile.close();
  }
  else
    {
      cout<<"Error opening File"<<endl;
    }
    
    for(unsigned k=0;k<cityNames.size();k++)
    {
        mapCity newTuple;
        unsigned a;
       //storing cityname in vector along with the list of destination cities
        get<0>(newTuple) = cityNames[k];
        vector<string> vs;
        for(a=0; a<origin.size(); a++)
        {
            if(get<0>(newTuple) == origin[a])
            {
                vs.push_back(destination[a]);
            }
        }
        
        get<1>(newTuple) = false;
        get<2>(newTuple) = vs;
        
        if(mapDetails.empty()==true)
        {
          mapDetails.push_front(newTuple);
        }
        else
        {
          mapDetails.push_back(newTuple);
        }
    }
   
    
}


 /** Determines if a city is served.
        @param aCity Name of a city.
        @return true if aCity is served; false, otherwise. */

bool FlightMap :: cityServed( string aCity ) const
{

    list<mapCity> :: const_iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
    {  
      if(get<0>((*itr)) == aCity)
        return true;
    
    }
    return false;
}


/** Displays flight map information. */

void FlightMap :: display() const
{
      list<mapCity> :: const_iterator itr = mapDetails.begin();
      for( ; itr != mapDetails.end(); ++itr)
      {
        cout<<  get<0>((*itr)) <<": ";
        if( get<2>((*itr)).size() == 0 )
        cout<<"No adjecent cities";
        else
        {
          for(unsigned i=0; i < get<2>((*itr)).size(); i++)
          cout<< get<2>((*itr))[i]<<" ";
        
        }
        cout<<endl;
      }
}


/** Displays the names of all the cities served. */

void FlightMap :: displayAllCities() const
{
    list<mapCity> :: const_iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
    cout<<get<0>((*itr))<<endl;
}



/** Displays all cities that are adjacent to a given city.
        @param aCity Name of a city served. */

void FlightMap :: displayAdjacentCities( string aCity ) const
{
    list<mapCity> :: const_iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
      {
        if( get<0>((*itr)) == aCity)
        {
            unsigned length = get<2>((*itr)).size();
            for(unsigned j=0;j<length;j++)
            cout<< get<2>((*itr))[j] << endl;
        
        }
      }
    
}
    


  /** Marks a city as visited.
        @param aCity Name of a city served. */
    
void FlightMap :: markVisited( string aCity )
{    
    list<mapCity> :: iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
    {
        if( get<0>((*itr)) == aCity)
          get<1>((*itr)) = true;
    }

}


   /** Clears marks on all cities. */
    
void FlightMap :: unvisitAll()
{
    
    list<mapCity> :: iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
    {
          get<1>((*itr)) = false;
    }

}



/** Sees whether a city was visited.
        @param aCity Name of a city served.
        @return true if aCity is marked as visited; false, otherwise. */
    
bool FlightMap :: isVisited( string aCity ) const
{

    list<mapCity> :: const_iterator itr = mapDetails.begin();
    for( ; itr != mapDetails.end(); ++itr)
      {
        if( get<0>((*itr)) == aCity && get<1>((*itr)) == true)
          return true;
      }
          
  return false;

}



/** Inserts a city adjacent to another city in a flight map.
        @param aCity Name of a city served; origin city.
        @param adjCity Name of a city served; destination city.
        @return true if adjCity successfully added as adjacent to aCity;
            false, otherwise. */    

bool FlightMap :: insertAdjacent( string aCity , string adjCity )
{
  
     list<mapCity> :: iterator itr = mapDetails.begin();
     for( ; itr != mapDetails.end(); ++itr)
     {
         if( get<0>((*itr)) == aCity )
         {
           get<2>((*itr)).push_back(adjCity);
         }    
     
     
     } 
    return true;
}
    
    

/** Returns the next unvisited city, if any, that is adjacent to a given city.
        Returns a sentinel value if no unvisited adjacent city was found.
        @param fromCity Name of a city served; origin city.
        @return Name of next unvisited city adjacent to fromCity; 
            otherwise, returns the empty string "". */    
    
string FlightMap :: getNextCity( string fromCity ) const
{
    
      list<mapCity> :: const_iterator itr = mapDetails.begin();
      for( ; itr != mapDetails.end(); ++itr)
      {
        if( get<0>((*itr)) == fromCity )
        {
            
            for(unsigned k = 0; k < get<2>((*itr)).size(); k++)
            {
                list<mapCity> :: const_iterator it = mapDetails.begin();
                
                for( ; it!=mapDetails.end(); ++it)
                {
                    if( get<2>((*itr))[k] == get<0>((*it)) && get<1>((*it)) == false)
                      return  get<0>((*it));
                }
            }
        }
      }


    return NO_CITY;

}



 /** Tests whether a sequence of flights exists between two cities.
        @param originCity Name of a city served; origin city.
        @param destinationCity Name of a city served; destination city.
        @return true if there exists a sequence of flights between
            originCity and destinationCity; false, otherwise. */
            
    bool FlightMap :: isPath( string originCity , string destinationCity )
    {
          stack<string> cityStack;
          unvisitAll(); // Clear marks on all cities
          cityStack.push( originCity ); // Push origin city onto cityStack and mark it as visited
          markVisited( originCity );
          string topCity=cityStack.top();
          while( !cityStack.empty() && (topCity!=destinationCity) )
          {
            // The stack contains a directed path from the origin city at
            // the bottom of the stack to the city at the top of the stack
            // Find an unvisited city adjacent to city on top of the stack
            string nextCity=getNextCity(topCity);
            if( nextCity==NO_CITY )
            cityStack.pop(); // No city found; backtrack
            else // Visit city
            {
              cityStack.push( nextCity );
              markVisited( nextCity );
            } // end if
            if( !cityStack.empty() )
            topCity=cityStack.top();
          } // end while
          
          
          return !cityStack.empty(); // Path found if stack is non-empty
          
    
    }