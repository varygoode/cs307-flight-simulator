/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: City.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "stdafx.h"

class City
{
private:

public:
	char *m_name;
	char *m_state;
	double m_lat;
	double m_long;
	char *m_symbol;
	int xPosition;
	int yPosition;
	City();
	~City();
	void setCityInfo(char *name, char *state, double lat, double lon, char *symbol, int x, int y);
	void printCityInfo();
};