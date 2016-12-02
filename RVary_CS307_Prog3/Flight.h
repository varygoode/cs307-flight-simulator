/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Flight.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "Aircraft.h"
#include "City.h"

class Flight
{
private:
	double distBetw;
public:
	double curTimeHr, curTimeMin;
	char *m_airline;
	Aircraft *m_aircraft;
	double m_flightNum;
	City *m_depCity;
	City *m_destCity;
	double m_depTimeHr;
	double m_depTimeMin;
	double m_curLat;
	double m_curLong;
	double m_curAlt;
	double m_curSpeed;
	int curX;
	int curY;
	bool m_enRoute;
	bool m_landed;
	bool m_justDeparted;
	bool m_justArrived;
	Flight();
	~Flight();
	void setFlightInfo(char *airline, Aircraft *aircraft, double flightNum, City *depCity,
		City *destCity, double depTimeHr, double depTimeMin, double distance);
	void printFlightInfo(int option);
	string getFlightInfo(int option);
	void update(double timeHr, double timeMin);
};