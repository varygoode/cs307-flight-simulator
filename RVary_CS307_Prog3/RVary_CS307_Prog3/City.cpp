/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: City.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include <string>
#include "City.h"
#include <iostream>

using namespace std;

City::City()
{
	m_name = NULL;
	m_state = NULL;
	m_lat = 0;
	m_long = 0;
	m_symbol = NULL;
	xPosition = 0;
	yPosition = 0;
}


City::~City()
{
	delete[] m_name;
	delete[] m_state;
	delete[] m_symbol;
}

void City::setCityInfo(char *name, char *state, double lat, double lon, char *symbol, int x, int y)
{
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);

	m_state = new char[strlen(state) + 1];
	strcpy(m_state, state);

	m_lat = lat;
	m_long = lon;

	m_symbol = new char[strlen(symbol) + 1];
	strcpy(m_symbol, symbol);

	xPosition = x;
	yPosition = y;
}

void City::printCityInfo()
{
	cout << m_name << ", " << m_state;
}