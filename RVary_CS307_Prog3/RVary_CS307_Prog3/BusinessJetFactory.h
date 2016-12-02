/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: BusinessJetFactory.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "AircraftFactory.h"
#include "Aircraft.h"
#include "BusinessJet.h"
#include "AircraftTypes.h"
#include <vector>
#include "stdafx.h"

using namespace std;

class BusinessJetFactory : public AircraftFactory
{
	private:
		BusinessJetFactory();
		~BusinessJetFactory();
		vector<BusinessJet*> bizJets;

	public:
		static BusinessJetFactory *getInstance();
		Aircraft *getAircraft(char *name);
};