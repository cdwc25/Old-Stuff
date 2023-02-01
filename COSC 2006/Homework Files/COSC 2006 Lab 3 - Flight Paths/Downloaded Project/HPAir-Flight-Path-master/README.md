# HPAir-Flight-Path
C++ Program that for each line in the file named requestFile, program first determine if HPAir services both the provided origin city and the indicated destination city. If both cities are served, program next determines if HPAir can fly from the provided origin city to the indicated destination city. Each request will be numbered starting with 1. All output sent to standard output.

Input
All input comes from three text files. The program asks for the file
names for each of this file in the order
1. cityFile filename
2. flightFile filename
3. requestFile filename
The user will provide the filenames.


It is assumed that

• The input data from the provided file names is correct.

• HPAir serves at most 20 cities.


Sample Input

• cityFile:

    Albuquerque
    Chicago
    San Diego
  
• flightFile:

    Chicago,San Diego
    Chicago,Albuquerque
    Albuquerque,Chicago
  
  
• requestFile:

    Albuquerque,San Diego
    Albuquerque,Paris
    San Diego,Chicago
  

Sample Output

        Request #1: Fly from Albuquerque to San Diego?
        HPAir flies from Albuquerque to San Diego.
        Request #2: Fly from Albuquerque to Paris?
        Sorry. HPAir does not serve Paris.
        Request #3: Fly from San Diego to Chicago?
        Sorry. HPAir does not fly from San Diego to Chicago.
