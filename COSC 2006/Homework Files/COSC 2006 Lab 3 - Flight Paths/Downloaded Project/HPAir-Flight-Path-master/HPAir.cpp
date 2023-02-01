/*
	Programming Assignment No. 3
	author: Sujeet Hiremath
	High Planes Airline Company (HPAir)
*/

#include "FlightMap.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main()
{

  string cityFileName, flightFileName, requestFileName,input,inputNames;
  ifstream requestFile;
  char   delimiter = ',';
  vector<string> origin, destination,listOfTokens,listOfFiles;
  string data;

  while(cin>>data)
  {
      listOfFiles.push_back(data);
  }


  cityFileName = listOfFiles[0]; //storing first input line to cityFiles
  flightFileName = listOfFiles[1]; //storing second input line to flightFilename
  requestFileName = listOfFiles[2]; //storing third to requestFilename

  unsigned count = 1;
  FlightMap fM;
  
  fM.read(cityFileName, flightFileName);
  
  requestFile.open(requestFileName);

    if(requestFile.is_open())
  {
      while(getline(requestFile, input))
      {
        listOfTokens = fM.split( input , delimiter );

        for(unsigned j=0;j<listOfTokens.size();j++)
          {
            if(j%2==0)
            origin.push_back(fM.removeSpecials(listOfTokens[j]));
            else
            destination.push_back(fM.removeSpecials(listOfTokens[j]));
          }
      }

      requestFile.close();
  }
  else
    {
      cout<<"Error opening File"<<endl;
    }

    for(unsigned i=0; i<origin.size();i++)
    {
        bool result = fM.isPath(origin[i],destination[i]);  //retuen of isPath function stored in variable result
        bool originServed = fM.cityServed(origin[i]); //return of cityServed stored 
        bool destinationServed = fM.cityServed(destination[i]); //return of cityServed stored in variable

        cout<<"Request "<<"#"<<count<<":"<<" Fly from "<< origin[i]<<" to "<< destination[i]<<"?"<<endl;

        if(originServed == true && destinationServed == true)
        {
          if(result == true)
          cout<<"HPAir flies from "<< origin[i]<<" to "<< destination[i]<<"."<<endl;
          else
          cout<<"Sorry. HPAir does not fly from "<< origin[i]<<" to "<<destination[i]<<"."<<endl;
        }
        else
        {
            if(originServed == false && destinationServed == false)
            {
              cout<<"Sorry. HPAir does not serve "<<origin[i]<<"."<<endl;
              cout<<"Sorry. HPAir does not serve "<<destination[i]<<"."<<endl;
            }
            else if(originServed == false && destinationServed == true)
              cout<<"Sorry. HPAir does not serve "<<origin[i]<<"."<<endl;
            else if(originServed == true && destinationServed == false)
              cout<<"Sorry. HPAir does not serve "<<destination[i]<<"."<<endl;
        }

        cout<<endl;
        count++;
    }


return 0;
}
