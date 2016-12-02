/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: CityMap.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "CityMap.h"
#include <iostream>

using namespace std;

CityMap::CityMap(char *xml)
{
	cdp = new CityDataParser();
	cdp->InitCityData(xml);

	for (int i = 0; i<cdp->getCityCount(); i++)
	{
		City *city = new City();

		char cName[32];
		char cState[32];
		char cSymbol[32];
		double lat, lon;
		int x, y;

		if (cdp->getCityData(cName, cState, cSymbol, &lat, &lon, &x, &y))
		{
			city->setCityInfo(cName, cState, lat, lon, cSymbol, x, y);
			cities.push_back(city);
		}
	}

	cdp->getCitySymbolsArray(&symbols);
	cdp->getDistTable(&distances);
}

CityMap::~CityMap()
{
	delete cdp;
	delete[] symbols;
	delete[] distances;
}

CityMap *CityMap::getInstance(char *xml)
{
	static CityMap *theInstance = nullptr;
	if (theInstance == nullptr)
	{
		theInstance = new CityMap(xml);
	}

	return theInstance;
}

double CityMap::distBetw(City *A, City *B)
{	
	int row, col;

	for (int i = 0; i<cdp->getCityCount(); i++)
	{
		if (strcmp(A->m_symbol, symbols[i]) == 0)
			row = i;
		if (strcmp(B->m_symbol, symbols[i]) == 0)
			col = i;
	}

	return distances[row*(cdp->getCityCount()) + col];
}

City *CityMap::getCity(char *symbol)
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (strcmp(cities[i]->m_symbol, symbol) == 0)
		{
			return cities[i];
		}
	}

	return nullptr;
}

void CityMap::drawCities(CDC *dc, int xPos, int yPos)
{
	CRect textRect;
	int X, Y;

	// For all cities
	for (vector<City *>::iterator itr = cities.begin();
		itr != cities.end(); itr++)
	{
		X = (*itr)->xPosition + xPos;
		Y = (*itr)->yPosition + yPos;
		// Draw the city circle 5 pix wide and 5 pix high
		dc->Ellipse(X - 2, Y - 2, X + 3, Y + 3);
		// Add the label
		textRect.left = (int)(X + 6);
		textRect.top = (int)(Y);
		textRect.right = textRect.left + 35;
		textRect.bottom = textRect.top + 18;
		// Standard window background
		dc->SetBkMode(TRANSPARENT);
		// Use OPAQUE for solid background
		// Args: Char array giving city symbol, #chars in the 
		//	array, address of the textRect, default value 0		 
		dc->DrawText((*itr)->m_symbol, 3, &textRect, 0);
	}
}
