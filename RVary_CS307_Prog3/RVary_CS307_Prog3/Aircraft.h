/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Aircraft.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once
#include "stdafx.h"
#include <string.h>
#include <string>

using namespace std;

class Aircraft
{
private:

public:
	char *m_make;
	char *m_model;
	double m_cruiseSpeed;
	double m_cruiseAltitude;
	double m_rateOfClimb;
	double m_wingspan;
	double m_fuselageLength;
	Aircraft();
	~Aircraft();
	void setPlaneInfo(char *make, char *model, double speed, double alt,
		double roc, double wingspan, double length);
	void printPlaneInfo();
};