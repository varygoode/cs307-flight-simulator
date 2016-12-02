/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: AircraftFactory.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "Aircraft.h"
#include "AircraftTypes.h"
#include "stdafx.h"

class AircraftFactory
{
	public:
		AircraftFactory();
		~AircraftFactory();
		virtual Aircraft *getAircraft(char *name);
};