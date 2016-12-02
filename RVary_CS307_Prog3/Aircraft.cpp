/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Aircraft.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "Aircraft.h"
#include <iostream>

using namespace std;

Aircraft::Aircraft()
{
	m_make = nullptr;
	m_model = nullptr;
	m_cruiseSpeed = 0;
	m_cruiseAltitude = 0;
	m_rateOfClimb = 0;
	m_wingspan = 0;
	m_fuselageLength = 0;
}

Aircraft::~Aircraft()
{
	delete[] m_make;
	delete[] m_model;
}

void Aircraft::setPlaneInfo(char *make, char *model, double speed, double alt,
	double roc, double wingspan, double length)
{
	m_make = new char[strlen(make) + 1];
	strcpy(m_make, make);

	m_model = new char[strlen(model) + 1];
	strcpy(m_model, model);

	m_cruiseSpeed = speed;
	m_cruiseAltitude = alt;
	m_rateOfClimb = roc;
	m_wingspan = wingspan;
	m_fuselageLength = length;
}

void Aircraft::printPlaneInfo()
{
	cout << m_make;
}