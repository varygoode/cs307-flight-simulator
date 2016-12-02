//========================================================
// FlightDataParser.cpp
// Implementation file for the flight data parser class.
//
// Author: Dr. Rick Coleman
// Date: August 2011
//========================================================
#pragma warning(disable : 4996)

#include "stdafx.h"
#include "FlightDataParser.h"
#include "string.h"
#include "stdlib.h"
#include <iostream>

using namespace std;

//------------------------------------------
// Default constructor
//------------------------------------------
FlightDataParser::FlightDataParser()
{
	m_iStartHour = 0;
	m_iStartMin = 0;
	m_iPJetCount = 0;
	m_iBJetCount = 0;
	m_iSEngineCount = 0;
	m_iFlightCount = 0;
	m_bDataFileOK = false;
}

//------------------------------------------
// Destructor
//------------------------------------------
FlightDataParser::~FlightDataParser()
{
}

//---------------------------------------
// Create the singleton instance of
//	this class.
//---------------------------------------
FlightDataParser *FlightDataParser::getInstance()
{
	static FlightDataParser *instance = NULL;
	if(instance == NULL)
	{
		instance = new FlightDataParser();
	}
	return instance;
}

//------------------------------------------
// Init the flight data
//------------------------------------------
void FlightDataParser::InitFlightData(char *dataFile)
{
	// Save the name of the data file
	strcpy(m_sFlightDataFile, dataFile);
	// Try to open the file
	inFile = new fstream();
	inFile->open(m_sFlightDataFile, fstream::in); // Open the data file
	if(!inFile->is_open())
	{
		cout << "Failed to open the Flight Data file.\nProgram terminating...\n";
		exit(0);
	}
	m_bDataFileOK = true; // flag the data file is good
	// Read and count the number of planes types, flights, and get
	//		the start hour and minute.
	char line[128];
	while(getNextLine(line, 127))
	{
		if(strcmp(line, "<STARTTIME>") == 0)
		{
			bool done = false;
			while(!done)
			{
				getNextLine(line, 127); // Read the next line
				if(strcmp(line, "<HOUR>") == 0)
				{
					getNextLine(line, 127); // Get hours
					m_iStartHour = atoi(line); // Convert string to int
				}
				else if(strcmp(line, "<MINUTE>") == 0)
				{
					getNextLine(line, 127); // Get MINUTES
					m_iStartMin = atoi(line); // Convert string to int
					done = true; // Flag we are done getting time
				}
			}
		}
		else if(strcmp(line, "<TYPE>") == 0)	// Count plane types
		{
			getNextLine(line, 127); // Get TYPE
			if(strcmp(line, "PASSENGERJET") == 0)
					m_iPJetCount++;
			else if(strcmp(line, "BUSINESSJET") == 0)
					m_iBJetCount++;
			else if(strcmp(line, "SINGLEENGINE") == 0)
					m_iSEngineCount++;
		}
		else if(strcmp(line, "<FLIGHT>") == 0)
		{
			m_iFlightCount++;	// Count all FLIGHTS
		}
	}
	inFile->close();
	delete inFile;
}

//------------------------------------------
// Get the scenario start hour and minute
// Args: hr - Pointer to an int to hold the
//				scenario start hour.
//		 min - Pointer to an int to hold the
//				scenario start minute.
//------------------------------------------
void FlightDataParser::getStartTime(int *hr, int *min)
{
	*hr = m_iStartHour;
	*min = m_iStartMin;
}

//------------------------------------------
// Get the number of aircraft types
//------------------------------------------
int FlightDataParser::getAircraftCount(AircraftType t)
{
	switch(t)
	{
		case PASSENGERJET :	
			return m_iPJetCount;
		case BUSINESSJET :	
			return m_iBJetCount;
		case SINGLEENGINE :	
			return m_iSEngineCount;
		default :
			return 0;
	}
}

//------------------------------------------
// Get the number of flights
//------------------------------------------
int FlightDataParser::getFlightCount()
{
	return m_iFlightCount;
}

//---------------------------------------------------
// Get all data on an aircraft
// Args: make - Pointer to a character array to hold
//					the name of the plane make, 
//					example: Boeing.
//		 desc - Pointer to a character array to hold
//					the description of the aircraft
//		 roc - Pointer to a double to hold the rate
//					of climb in feet per minute.
//		 wngs - Pointer to a double to hold the wing
//					span in feet.
//		 len - Pointer to a double to hold the 
//					fuselage length in feet.
//		 cs - Pointer to a double to hold the cruise
//					speed in flight.
//		 ca - Pointer to a double to hold the cruise
//					altitude.
//---------------------------------------------------
bool FlightDataParser::getAircraftData(AircraftType t, char *make, char *desc,
	double *roc, double *wngs, double *len,
	double *cs, double *ca)
{
	static int nextPJPlaneIdx = 0; // Index of the next passenger jet to read
	static int nextBJPlaneIdx = 0; // Index of the next business jet to read
	static int nextSEPlaneIdx = 0; // Index of the next single engine plane to read
	int planePJIdx = 0;	// current count of passenger jets
	int planeBJIdx = 0;	// current count of business jets
	int planeSEIdx = 0;	// current count of single engine planes
	// temporary data holders
	char sMake[32]; // Plane make
	char sDesc[32]; // Plane description
	double dROC;	// Rate of climb
	double dWngSp;	// Wing span
	double dLen;	// Fuselage length
	double dCS;		// Cruise Speed
	double dCA;		// Cruise Altitude

	bool typeOK = false;
//	bool dataOK = false;

	// Have we already read all plane data?
	switch(t)
	{
		case PASSENGERJET :	
			if(nextPJPlaneIdx >= m_iPJetCount)
				return false;
			break;
		case BUSINESSJET :	
			if(nextBJPlaneIdx >= m_iBJetCount)
				return false;
			break;
		case SINGLEENGINE :	
			if(nextSEPlaneIdx >= m_iSEngineCount)
				return false;
			break;
	}

	// Try to open the file
	inFile = new fstream();
	inFile->open(m_sFlightDataFile, fstream::in); // Open the data file
	if(!inFile->is_open())
	{
		cout << "Failed to open the Flight Data file.\nProgram terminating...\n";
		exit(0);
	}
	char line[128];
	// Find the next plane
	while(getNextLine(line, 127))
	{
		if(strcmp(line, "<PLANE>") == 0)
		{
			// Found a plane check the index and type
			//if(((planePJIdx == nextPJPlaneIdx) && (t == PASSENGERJET)) ||
			//	((planeBJIdx == nextBJPlaneIdx) && (t == BUSINESSJET)) ||
			//	((planeSEIdx == nextSEPlaneIdx) && (t == SINGLEENGINE)))
			//{
//				dataOK;	// OK to save this data

			// Read all the data on this plane
			bool done = false;
			while(!done)
			{
				getNextLine(line, 127); // Read the next line
				if(strcmp(line, "<MAKE>") == 0)
				{
					getNextLine(line, 127);
					strcpy(sMake, line); // Save the aircraft make
				}
				else if(strcmp(line, "<TYPE>") == 0)
				{
					getNextLine(line, 127);
					if((strcmp(line, "PASSENGERJET") == 0) && (t == PASSENGERJET))
					{
						if(planePJIdx == nextPJPlaneIdx)
							typeOK = true;
						else
							planePJIdx++;
					}
					else if((strcmp(line, "BUSINESSJET") == 0) && (t == BUSINESSJET))
					{
						if(planeBJIdx == nextBJPlaneIdx)
							typeOK = true;
						else
							planeBJIdx++;
					}
					else if((strcmp(line, "SINGLEENGINE") == 0) && (t == SINGLEENGINE))
					{
						if(planeSEIdx == nextSEPlaneIdx)
							typeOK = true;
						else
							planeSEIdx++;
					}
				}
				else if(strcmp(line, "<DESCRIPTION>") == 0)
				{
					getNextLine(line, 127);	// get the type string
					strcpy(sDesc, line); // Save the aircraft description
				}
				else if(strcmp(line, "<RATEOFCLIMB>") == 0)
				{
					getNextLine(line, 127);
					dROC = atof(line); // Save rate of climb
				}
				else if(strcmp(line, "<WINGSPAN>") == 0)
				{
					getNextLine(line, 127);
					dWngSp = atof(line); // Save wing span in feet
				}
				else if(strcmp(line, "<LENGTH>") == 0)
				{
					getNextLine(line, 127);
					dLen = atof(line); // Save fuselage length in feet
				}
				else if(strcmp(line, "<CRUISESPEED>") == 0)
				{
					getNextLine(line, 127);
					dCS = atof(line); // Save cruise speed in Miles Per Hour
				}
				else if(strcmp(line, "<CRUISEALTITUDE>") == 0)
				{
					getNextLine(line, 127);
					dCA = atof(line); // Save cruise altitude in feet
				}
				else if(strcmp(line, "</PLANE>") == 0)
				{
					if(typeOK) // Got the one we want
					{
						done = true; // Flag done reading data for this plane
						switch(t)
						{
							case PASSENGERJET :	
								nextPJPlaneIdx++;
								break;
							case BUSINESSJET :	
								nextBJPlaneIdx++;
								break;
							case SINGLEENGINE :	
								nextSEPlaneIdx++;
								break;
						}
						// Copy the data
						strcpy(make, sMake);
						strcpy(desc, sDesc);
						*roc = dROC;
						*wngs = dWngSp;
						*len = dLen;
						*cs = dCS;
						*ca = dCA;
						inFile->close();
						delete inFile;
						return true;
					} // end if type OK
				} // end else if </PLANE>
			} // end while not done
			//} // end if this is the index we want
			//else
			//{
			//	// Read to TYPE tag and update counters
			//	getNextLine(line, 127);
			//	while(strcmp(line, "<TYPE>") != 0)
			//		getNextLine(line, 127);
			//	// Now read the type string
			//	getNextLine(line, 127);
			//	if(strcmp(line, "PASSENGERJET") == 0)
			//			planePJIdx++;
			//	else if(strcmp(line, "BUSINESSJET") == 0)
			//			planeBJIdx++;
			//	else if(strcmp(line, "SINGLEENGINE") == 0)
			//			planeSEIdx++;
			//} // end else update the counter
		} // end if this is a PLANE tag
	} // end while
	return false;
}

//---------------------------------------------------
// Get all data on a flight
// Args: airline - Pointer to a character array to
//					hold the name of the airline.
//		 plane - Pointer to a character array to hold
//					the name of the type of aircraft.
//		 flNum - Pointer to an int to hold the flight
//					number.
//		 departCity - Pointer to a character array to
//					hold the 3-letter symbol for the
//					flight departure city.
//		 depHr - Pointer to an int to hold the 
//					departure hour.
//		 depMin - Pointer to an int to hold the 
//					departure minute.
//		 destCity - Pointer to a character array to
//					hold the 3-letter symbol for the
//					flight destination city.
// Returns: True if the data are valid.  False when
//			all flight data has been read.
//---------------------------------------------------
bool FlightDataParser::getFlightData(char *airline, char *plane,
	int *flNum, char *departCity, int *depHr,
	int *depMin, char *destCity)
{
	static int nextFlightIdx = 0;
	int flightIdx = 0;
		
	// Have we already read all plane data?
	if(nextFlightIdx >= m_iFlightCount) return false;


	// Try to open the file
	inFile = new fstream();
	inFile->open(m_sFlightDataFile, fstream::in); // Open the data file
	if(!inFile->is_open())
	{
		cout << "Failed to open the Flight Data file.\nProgram terminating...\n";
		exit(0);
	}
	char line[128];
	// Find the next flight
	while(getNextLine(line, 127))
	{
		if(strcmp(line, "<FLIGHT>") == 0)
		{
			// Found a plane check the index
			if(flightIdx == nextFlightIdx) 
			{
				bool done = false;
				while(!done)
				{
					getNextLine(line, 127); // Read the next line
					if(strcmp(line, "<AIRLINE>") == 0)
					{
						getNextLine(line, 127);
						strcpy(airline, line); // Save the airline name
					}
					else if(strcmp(line, "<PLANEMAKE>") == 0)
					{
						getNextLine(line, 127);
						strcpy(plane, line); // Save the plane type
					}
					else if(strcmp(line, "<FLIGHTNUMBER>") == 0)
					{
						getNextLine(line, 127);
						*flNum = atoi(line); // Save flight number
					}
					else if(strcmp(line, "<DEPARTSFROM>") == 0)
					{
						getNextLine(line, 127);
						strcpy(departCity, line); // Save departure city symbol
					}
					else if(strcmp(line, "<DEPARTURETIME>") == 0)
					{
						bool done2 = false;
						while(!done2)
						{
							getNextLine(line, 127); // Read the next line
							if(strcmp(line, "<HOUR>") == 0)
							{
								getNextLine(line, 127); // Get hour
								*depHr = atoi(line); // Convert string to int
							}
							else if(strcmp(line, "<MINUTE>") == 0)
							{
								getNextLine(line, 127); // Get minute
								*depMin = atoi(line); // Convert string to int
							}
							else if(strcmp(line, "</DEPARTURETIME>") == 0)
							{
								done2 = true; // Flag we are done getting time
							}
						}
					}
					else if(strcmp(line, "<DESTINATION>") == 0)
					{
						getNextLine(line, 127);
						strcpy(destCity, line); // Save destination city symbol
					}
					else if(strcmp(line, "</FLIGHT>") == 0)
					{
						done = true; // Flag done reading data for this FLIGHT
						nextFlightIdx++; // Index for next call
						inFile->close();
						delete inFile;
						return true;
					}
				} // end while not done
			} // end if this is the index we want
			flightIdx++; // increment count of flights
		} // end if this is a FLIGHT tag
	} // end while
	return false;
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
//------------------------------------------------
bool FlightDataParser::getNextLine(char *buffer, int n)
{
    bool    done = false;
	char    tempBuf[128];
	char	*temp;
    while(!done)
    {
        inFile->getline(tempBuf, n); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(strlen(tempBuf) == 0)     // Skip any blank lines
               continue;
		   else if(strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(buffer, "");  // Clear the buffer array
            return false;        // Flag end of file
        }
    } // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while(isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while(isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
    return true;  // Flag a successful read
}
