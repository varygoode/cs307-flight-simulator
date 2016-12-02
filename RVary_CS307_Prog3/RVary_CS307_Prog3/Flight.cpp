/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Flight.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "Flight.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

Flight::Flight()
{
	m_airline = nullptr;
	m_aircraft = new Aircraft();
	m_flightNum = 0;
	m_depCity = new City();
	m_destCity = new City();
	m_depTimeHr = 0;
	m_depTimeMin = 0;
	m_curLat = 0;
	m_curLong = 0;
	curX = 0;
	curY = 0;
	m_curAlt = 0;
	m_curSpeed = 0;
	distBetw = 0;
	m_enRoute = false;
	m_landed = false;
	curTimeHr = 0;
	curTimeMin = 0;
	m_justArrived = false;
	m_justDeparted = false;
}

Flight::~Flight()
{
	m_aircraft->~Aircraft();
	m_depCity->~City();
	m_destCity->~City();
	delete m_aircraft;
	delete[] m_airline;
	delete m_depCity;
	delete m_destCity;
}

void Flight::setFlightInfo(char *airline, Aircraft *aircraft, double flightNum, City *depCity,
	City *destCity, double depTimeHr, double depTimeMin, double distance)
{
	m_airline = new char[strlen(airline) + 1];
	strcpy(m_airline, airline);

	m_aircraft->setPlaneInfo(aircraft->m_make, aircraft->m_model, aircraft->m_cruiseSpeed,
		aircraft->m_cruiseAltitude, aircraft->m_rateOfClimb,
		aircraft->m_wingspan, aircraft->m_fuselageLength);

	m_flightNum = flightNum;

	m_depCity->setCityInfo(depCity->m_name, depCity->m_state, depCity->m_lat, depCity->m_long, depCity->m_symbol, depCity->xPosition, depCity->yPosition);

	m_destCity->setCityInfo(destCity->m_name, destCity->m_state, destCity->m_lat, destCity->m_long, destCity->m_symbol, destCity->xPosition, destCity->yPosition);

	m_depTimeHr = depTimeHr;
	m_depTimeMin = depTimeMin;

	distBetw = distance;
}

void Flight::printFlightInfo(int option)
{
	double tripTime = distBetw / (m_aircraft->m_cruiseSpeed);
	double elapsedTime = (curTimeHr + (curTimeMin / 60)) - (m_depTimeHr + (m_depTimeMin / 60));

	if (elapsedTime < 0)
	{
		elapsedTime = 0;
	}

	double distFromStart = (elapsedTime / tripTime) * distBetw;
	double distToEnd = distBetw - distFromStart;

	double arrivalTimeHr = floor((m_depTimeHr + (m_depTimeMin / 60)) + tripTime);

	double arrivalTimeMin = (((m_depTimeHr + (m_depTimeMin / 60)) + tripTime) - arrivalTimeHr) * 60;
	arrivalTimeMin = ceil(arrivalTimeMin);

	switch (option)
	{
	case 1:
		cout << "Now departing: " << m_airline << " flight " << m_flightNum << ", ";
		m_aircraft->printPlaneInfo();
		cout << endl;
		cout << "\t\tFrom ";
		m_depCity->printCityInfo();
		cout << endl;
		cout << "\t\t\tenroute to ";
		m_destCity->printCityInfo();
		cout << endl;
		break;

	case 2:
		cout << "Now arriving: " << m_airline << " flight " << m_flightNum << ", ";
		m_aircraft->printPlaneInfo();
		cout << endl;
		cout << "\t\t\tAt ";
		m_destCity->printCityInfo();
		cout << endl;
		cout << "\t\t\tfrom ";
		m_depCity->printCityInfo();
		cout << endl;
		break;

	case 3:
		cout << m_airline << " flight " << m_flightNum << " - ";
		m_aircraft->printPlaneInfo();
		cout << endl;
		cout << "\t\tDeparts: " << m_depCity->m_symbol << " (" << m_depCity->m_lat << ", " << m_depCity->m_long << ") at " << m_depTimeHr << ":" << setw(2) << setfill('0') << m_depTimeMin << endl;
		cout << "\t\tArrives: " << m_destCity->m_symbol << " (" << m_destCity->m_lat << ", " << m_destCity->m_long << ") at " << arrivalTimeHr << ":" << setw(2) << setfill('0') << arrivalTimeMin << endl;
		cout << "\t\tCurrent location: (" << m_curLat << ", " << m_curLong << ")" << endl;
		cout << "\t\t\t" << (int) distFromStart << " miles from " << m_depCity->m_symbol << ", " << (int) distToEnd << " miles to " << m_destCity->m_symbol << endl;
		cout << "\t\tCurrent speed: " << m_curSpeed << " MPH" << endl;
		cout << "\t\tCurrent altitude: " << m_curAlt << " feet" << endl;
		break;
	}
}

void Flight::update(double timeHr, double timeMin)
{
	curTimeHr = timeHr;
	curTimeMin = timeMin;

	double tripTime = distBetw / (m_aircraft->m_cruiseSpeed);
	double elapsedTime = (curTimeHr + (curTimeMin / 60)) - (m_depTimeHr + (m_depTimeMin / 60));
	double timeLeft = tripTime - elapsedTime;

	if (elapsedTime < 0)
	{
		elapsedTime = 0;
	}

	double distFromStart = (elapsedTime / tripTime) * distBetw;
	double distToEnd = distBetw - distFromStart;

	double speedInMPM = m_aircraft->m_cruiseSpeed / 60.0;
	double speedInFPM = speedInMPM * 5280.0;

	double MACA = m_aircraft->m_cruiseAltitude / m_aircraft->m_rateOfClimb; //mins to cruise alt.
	double DACA = MACA * speedInFPM; //distance to cruise alt. in ft
	DACA = DACA / 5280; //distance to cruise alt. in miles

	if ((timeHr == m_depTimeHr) && (timeMin == m_depTimeMin) && !m_justDeparted)
	{
		m_enRoute = true;
		m_curLat = m_depCity->m_lat;
		m_curLat = m_depCity->m_long;
		curX = m_depCity->xPosition;
		curY = m_depCity->yPosition;
		m_curSpeed = m_aircraft->m_cruiseSpeed;
		m_justDeparted = true;
	}

	else if (distToEnd <= 1 && !m_landed && !m_justArrived)
	{
		m_enRoute = false;
		m_landed = true;
		m_curAlt = 0;
		m_curSpeed = 0;
		distToEnd = -1;
		m_justArrived = true;
	}

	else if (!m_landed && m_enRoute)
	{
		m_curLat = m_depCity->m_lat + (m_destCity->m_lat - m_depCity->m_lat) * (elapsedTime / tripTime);
		m_curLong = m_depCity->m_long + (m_destCity->m_long - m_depCity->m_long) * (elapsedTime / tripTime);
		curX = m_depCity->xPosition + (m_destCity->xPosition - m_depCity->xPosition) * (elapsedTime / tripTime);
		curY = m_depCity->yPosition + (m_destCity->yPosition - m_depCity->yPosition) * (elapsedTime / tripTime);
		double roc = m_aircraft->m_rateOfClimb;
		if (m_curAlt < m_aircraft->m_cruiseAltitude)
		{
			if (distToEnd >(distBetw / 2))
			{
				m_curAlt = (elapsedTime * 60) * roc;
			}
			else if (distFromStart > (distBetw - DACA))
			{
				m_curAlt = (timeLeft * 60) * roc;
			}
		}

		if (distFromStart > (distBetw - DACA))
		{
			m_curAlt = (timeLeft * 60) * roc;
		}
	}
}

string Flight::getFlightInfo(int option)
{
	stringstream theString;
	
	double tripTime = distBetw / (m_aircraft->m_cruiseSpeed);
	double elapsedTime = (curTimeHr + (curTimeMin / 60)) - (m_depTimeHr + (m_depTimeMin / 60));

	if (elapsedTime < 0)
	{
		elapsedTime = 0;
	}

	double distFromStart = (elapsedTime / tripTime) * distBetw;
	double distToEnd = distBetw - distFromStart;

	double arrivalTimeHr = floor((m_depTimeHr + (m_depTimeMin / 60)) + tripTime);

	double arrivalTimeMin = (((m_depTimeHr + (m_depTimeMin / 60)) + tripTime) - arrivalTimeHr) * 60;
	arrivalTimeMin = ceil(arrivalTimeMin);

	switch (option)
	{
	case 1:
		theString << "Now departing: \n";
		theString << "  " << m_airline << " flight #" << m_flightNum << endl;
		theString << "  " << m_aircraft->m_make << " service:\n";
		theString << "   From " << m_depCity->m_symbol << "  (Lat: " << m_depCity->m_lat << ", Lon: " << m_depCity->m_long << ") at " << m_depTimeHr << ":" << setw(2) << setfill('0') << m_depTimeMin << endl;
		theString << "   To " << m_destCity->m_symbol << " (Lat: " << m_destCity->m_lat << ", Lon: " << m_destCity->m_long << ") at " << arrivalTimeHr << ":" << setw(2) << setfill('0') << arrivalTimeMin << endl;
		break;

	case 2:
		theString << "Now arriving: \n";
		theString << "  " << m_airline << " flight #" << m_flightNum << endl;
		theString << "  " << m_aircraft->m_make << " service:\n";
		theString << "   At " << m_destCity->m_symbol << " (Lat: " << m_destCity->m_lat << ", Lon: " << m_destCity->m_long << ") at " << arrivalTimeHr << ":" << setw(2) << setfill('0') << arrivalTimeMin << endl;
		theString << "   From " << m_depCity->m_symbol << "  (Lat: " << m_depCity->m_lat << ", Lon: " << m_depCity->m_long << ") at " << m_depTimeHr << ":" << setw(2) << setfill('0') << m_depTimeMin << endl;
		break;

	case 3:
		theString << m_airline << " #" << m_flightNum << ":";
		theString << " (Lat " << m_curLat << ", Lon " << m_curLong << ")" << endl;
		theString << "\t" << fixed << setprecision(0) << distFromStart << " from " << m_depCity->m_symbol << " " << distToEnd << " to " << m_destCity->m_symbol << ", ";
		theString << "Spd=" << m_curSpeed << ", ";
		theString << "Alt=" << m_curAlt << endl;
		break;
	}

	return theString.str();
}