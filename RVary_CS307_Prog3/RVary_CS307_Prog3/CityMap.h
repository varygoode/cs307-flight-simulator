/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: CityMap.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "CityDataParser.h"
#include "City.h"
#include <vector>

using namespace std;

class CityMap
{
	private:
		CityMap(char *xml);
		~CityMap();
		char **symbols;
		double *distances;

	public:
		vector<City*> cities;
		static CityMap *getInstance(char *xml);
		double distBetw(City *A, City *B);
		City *getCity(char *symbol);
		void CityMap::drawCities(CDC *dc, int xPos, int yPos);
		CityDataParser *cdp;
};