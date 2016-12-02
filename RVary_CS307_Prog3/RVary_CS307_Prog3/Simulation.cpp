/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Simulation.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "Simulation.h"
#include "PassengerJetFactory.h"
#include "BusinessJetFactory.h"
#include "SingleEnginePlaneFactory.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "City.h"
#include "CityMap.h"
#include <sstream>

using namespace std;

Simulation::Simulation()
{
	fdp = FlightDataParser::getInstance();
	df = nullptr;
}

Simulation::~Simulation()
{

}

bool Simulation::initialize(char *datafile)
{
	char *cityXML = new char[50];
	char *flightXML = new char[50];
	df = datafile;
	
	ifstream inFile;
	inFile.open(datafile);
	if (!inFile.is_open())
		return false;

	inFile >> cityXML;
	inFile >> flightXML;

	inFile.close();

	CityMap *map = CityMap::getInstance(cityXML);

	fdp->InitFlightData(flightXML);

	AircraftFactory *pjf = PassengerJetFactory::getInstance();
	AircraftFactory *bjf = BusinessJetFactory::getInstance();
	AircraftFactory *ppf = SingleEnginePlaneFactory::getInstance();

	vector<Aircraft*> planes;

	for (AircraftType type = PASSENGERJET; type <= SINGLEENGINE; type = AircraftType(type + 1))
	{
		for (int i = 0; i < fdp->getAircraftCount(type); i++)
		{
			Aircraft *plane;
			
			char aMake[32];
			char aType[32];
			double rateOfClimb, wingspan, length, cruiseSpeed, cruiseAlt;

			if (fdp->getAircraftData(type, aMake, aType, &rateOfClimb, &wingspan, &length, &cruiseSpeed, &cruiseAlt))
			{
				if (type == BUSINESSJET)
				{
					plane = bjf->getAircraft(aMake);
				}

				if (type == PASSENGERJET)
				{
					plane = pjf->getAircraft(aMake);
				}

				if (type == SINGLEENGINE)
				{
					plane = ppf->getAircraft(aMake);
				}

				plane->setPlaneInfo(aMake, aType, cruiseSpeed, cruiseAlt, rateOfClimb, wingspan, length);
			}

			planes.push_back(plane);
		}
	}

	for (int i = 0; i<fdp->getFlightCount(); i++)
	{
		Flight *flight = new Flight();

		char airline[32];
		char planeType[32];
		int flightNumber;
		char departCity[4];
		int departHour, departMin;
		char destinationCity[4];

		fdp->getFlightData(airline, planeType, &flightNumber, departCity, &departHour, &departMin, destinationCity);

		int aircraftIdx = 0;

		for (int k = 0; k < planes.size(); k++)
		{
			if (strcmp(planeType, planes[k]->m_make) == 0)
			{
				aircraftIdx = k;
			}
		}

		flight->setFlightInfo(airline, planes[aircraftIdx], flightNumber, map->getCity(departCity), map->getCity(destinationCity), departHour, departMin, map->distBetw(map->getCity(departCity), map->getCity(destinationCity)));
		flights.push_back(flight);
	}

	return true;
}

void Simulation::update(int timeHr, int timeMin)
{
	for (int i = 0; i<flights.size(); i++)
	{
		flights[i]->update((double)timeHr, (double)timeMin);
	}
}

bool Simulation::simDone()
{
	for (int i = 0; i<flights.size(); i++)
	{
		if (!(flights[i]->m_landed))
		{
			return false;
		}
	}

	return true;
}

void Simulation::drawCities(CDC *dc, int xPos, int yPos)
{
	CityMap::getInstance(df)->drawCities(dc, xPos, yPos);
}

void Simulation::getMapImageSize(int *width, int *height)
{
	CityMap::getInstance(df)->cdp->getMapImageSize(width, height);
}

void Simulation::drawReport(CDC *dc, int xPos, int yPos, int right, int bot)
{
	CRect textRect;
	CRect theRect;
	
	theRect.left = xPos + 10;
	theRect.top = yPos + 15;
	theRect.right = theRect.left + right;
	theRect.bottom = theRect.top + bot;

	textRect.left = theRect.left + 5;
	textRect.top = theRect.top + 5;
	textRect.right = theRect.right -5;
	textRect.bottom = theRect.bottom -5;
	dc->SetBkMode(OPAQUE);
	dc->SetBkColor(RGB(255,255,255));

	dc->Rectangle(theRect);

	HFONT hFont;

	hFont = CreateFont(12, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, 0,
		0, CLEARTYPE_QUALITY, 0, TEXT("Lucida Console"));

	SelectObject(*dc, hFont);

	stringstream title;
	char time[10];
	strcpy(time, "");
	if (flights[0]->curTimeHr <= 9)
	{
		strcat(time, "0");
	}

	ostringstream hour, min;

	hour << flights[0]->curTimeHr;

	min << flights[0]->curTimeMin;

	strcat(time, hour.str().c_str());
	strcat(time, ":");
	if (flights[0]->curTimeMin <= 9)
	{
		strcat(time, "0");
	}
	strcat(time, min.str().c_str());

		title << "================================================\n|  Status Report: Flights Enroute " <<
			"at " << time << "   |\n================================================\n";

	dc->DrawText(title.str().c_str(), -1, &textRect, 0);

	textRect.top += 35;
	textRect.bottom += 35;

	for (int i = 0; i<flights.size(); i++)
	{
		if (flights[i]->m_enRoute && !flights[i]->m_landed)
		{
			dc->DrawText(flights[i]->getFlightInfo(3).c_str(), -1, &textRect, 0);
			textRect.top += 27;
			textRect.bottom += 27;
		}
	}

	DeleteObject(hFont);

	if (simDone())
	{
		dc->Rectangle(theRect);
		textRect.left = theRect.left + 5;
		textRect.top = theRect.top + 5;
		textRect.right = theRect.right - 5;
		textRect.bottom = theRect.bottom - 5;
		dc->DrawText("The simulation has run to completion.", -1, &textRect, 0);
	}
}

void Simulation::drawArrDep(CDC *dc, int xPos, int yPos, int right, int bot)
{
	CRect textRect;
	CRect theRect;

	theRect.left = xPos + 10;
	theRect.top = yPos + 15;
	theRect.right = theRect.left + right;
	theRect.bottom = theRect.top + bot;

	textRect.left = theRect.left + 5;
	textRect.top = theRect.top + 5;
	textRect.right = theRect.right - 5;
	textRect.bottom = theRect.bottom - 5;
	dc->SetBkMode(OPAQUE);
	dc->SetBkColor(RGB(255, 255, 255));


	HFONT hFont;

	hFont = CreateFont(12, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, 0,
		0, CLEARTYPE_QUALITY, 0, TEXT("Lucida Console"));

	SelectObject(*dc, hFont);

	for (int i = 0; i<flights.size(); i++)
	{
		if (flights[i]->m_justDeparted)
		{
			dc->Rectangle(theRect);
			dc->DrawText(flights[i]->getFlightInfo(1).c_str(), -1, &textRect, 0);
			flights[i]->m_justDeparted = false;
		}

		if (flights[i]->m_justArrived)
		{
			dc->Rectangle(theRect);
			dc->DrawText(flights[i]->getFlightInfo(2).c_str(), -1, &textRect, 0);
			flights[i]->m_justArrived = false;
		}
	}

	DeleteObject(hFont);

	if (simDone())
	{
		dc->Rectangle(theRect);
	}
}

void Simulation::drawClock(CDC *dc, int xPos, int yPos, int right, int bot)
{
	CRect textRect;
	CRect theRect;

	theRect.left = xPos + 10;
	theRect.top = yPos + 15;
	theRect.right = theRect.left + right;
	theRect.bottom = theRect.top + bot;

	textRect.left = theRect.left + 2;
	textRect.top = theRect.top + 2;
	textRect.right = theRect.right - 2;
	textRect.bottom = theRect.bottom - 2;
	dc->SetBkMode(OPAQUE);
	dc->SetBkColor(RGB(255, 255, 255));

	dc->Rectangle(theRect);

	char time[10];
	strcpy(time, "");
	if (flights[0]->curTimeHr <= 9)
	{
		strcat(time, "0");
	}

	ostringstream hour, min;

	hour << flights[0]->curTimeHr;

	min << flights[0]->curTimeMin;

	strcat(time, hour.str().c_str());
	strcat(time, ":");
	if (flights[0]->curTimeMin <= 9)
	{
		strcat(time, "0");
	}
	strcat(time, min.str().c_str());

	HFONT hFont;

	hFont = CreateFont(10, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0,
		0, CLEARTYPE_QUALITY, 0, TEXT("Lucida Console"));

	SelectObject(*dc, hFont);

	dc->DrawText(time, 10, &textRect, DT_SINGLELINE | DT_VCENTER);

	DeleteObject(hFont);
}

void Simulation::drawRoutesAndPlanes(CDC *dc, int xPos, int yPos)
{
	for (int i = 0; i < flights.size(); i++)
	{
		if (flights[i]->m_enRoute)
		{
			CPen routePen, planePen;
			routePen.CreatePen(PS_SOLID, 2, RGB(0,0,255));
			planePen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			dc->SelectObject(&routePen);
			dc->MoveTo(xPos + flights[i]->m_depCity->xPosition, yPos + flights[i]->m_depCity->yPosition);
			dc->LineTo(xPos + flights[i]->m_destCity->xPosition, yPos + flights[i]->m_destCity->yPosition);
			dc->SelectObject(&planePen);
			dc->Ellipse(xPos + flights[i]->curX - 3, yPos + flights[i]->curY - 3, xPos + flights[i]->curX + 4, yPos + flights[i]->curY + 4);
		}
	}
}