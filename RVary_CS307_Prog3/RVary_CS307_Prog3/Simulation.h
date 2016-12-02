/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Simulation.h
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include "FlightDataParser.h"
#include "Flight.h"
#include <vector>

class Simulation
{
private:
	vector<Flight*> flights;
	char *df;

public:
	Simulation();
	~Simulation();
	FlightDataParser *fdp;
	bool initialize(char *datafile);
	void update(int timeHr, int timeMin);
	bool simDone();
	void drawCities(CDC *dc, int xPos, int yPos);
	void getMapImageSize(int *width, int *height);
	void drawReport(CDC *dc, int xPos, int yPos, int right, int bot);
	void drawArrDep(CDC *dc, int xPos, int yPos, int right, int bot);
	void drawClock(CDC *dc, int xPos, int yPos, int right, int bot);
	void drawRoutesAndPlanes(CDC *dc, int xPos, int yPos);
};