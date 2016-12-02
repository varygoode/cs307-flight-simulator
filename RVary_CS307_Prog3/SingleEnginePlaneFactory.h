/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: SingleEnginePlaneFactory.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "AircraftFactory.h"
#include "Aircraft.h"
#include "SingleEnginePlane.h"
#include "AircraftTypes.h"
#include <vector>

using namespace std;

class SingleEnginePlaneFactory : public AircraftFactory
{
	private:
		SingleEnginePlaneFactory();
		~SingleEnginePlaneFactory();
		vector<SingleEnginePlane*> singEngs;

	public:
		static SingleEnginePlaneFactory *getInstance();
		Aircraft *getAircraft(char *name);
};