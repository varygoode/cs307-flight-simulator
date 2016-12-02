//========================================================
// FlightDataParser.h
// Interface file for the flight data parser class.
//
// Author: Dr. Rick Coleman
//========================================================
#ifndef FLIGHTDATAPARSER_H
#define FLIGHTDATAPARSER_H

#include "fstream"
#include "AircraftTypes.h"

using namespace std;

class FlightDataParser
{
	private:
		char m_sFlightDataFile[32];				// Name of the flight data file
		int  m_iStartHour;						// Hour the scenario starts (24 hr clock)
		int  m_iStartMin;						// Minute the scenario starts
		int  m_iPJetCount;						// Number of passenger jet types
		int  m_iBJetCount;						// Number of business jet types
		int  m_iSEngineCount;					// Number of single engine plane types
		int  m_iFlightCount;					// Number of flights 
		bool m_bDataFileOK;						// Flag we have a good data file
		fstream	*inFile;
		FlightDataParser();						// Default constructor

	public:
		~FlightDataParser();					// Destructor
		static FlightDataParser *getInstance();	// Get the singleton instance
		void InitFlightData(char *dataFile);	// Init the flight data
		void getStartTime(int *hr, int *min);	// Get the scenario start hour and minute
		int getAircraftCount(AircraftType t);	// Get the number of aircraft types
		int getFlightCount();					// Get the number of flights
		bool getAircraftData(AircraftType t, 
			char *make, char *desc,
			double *roc, double *wngs, double *len,
			double *cs, double *ca);			// Get all data on an aircraft
		bool getFlightData(char *airline, char *plane,
			int *flNum, char *departCity, int *depHr,
			int *depMin, char *destCity);		// Get all data on a flight
		bool getNextLine(char *buffer, int n);
};

#endif
