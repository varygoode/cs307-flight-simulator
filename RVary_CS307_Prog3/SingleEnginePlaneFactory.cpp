/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: SingleEnginePlaneFactory.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "SingleEnginePlaneFactory.h"

SingleEnginePlaneFactory::SingleEnginePlaneFactory()
{

}

SingleEnginePlaneFactory::~SingleEnginePlaneFactory()
{

}

SingleEnginePlaneFactory *SingleEnginePlaneFactory::getInstance()
{
	static SingleEnginePlaneFactory *theInstance = nullptr;
	if (theInstance == nullptr)
	{
		theInstance = new SingleEnginePlaneFactory();
	}

	return theInstance;
}

Aircraft *SingleEnginePlaneFactory::getAircraft(char *name)
{
	for (int i = 0; i < singEngs.size(); i++)
	{
		if (strcmp(singEngs[i]->m_make, name) == 0)
		{
			return singEngs[i];
		}
	}

	SingleEnginePlane *singEng = new SingleEnginePlane();

	singEngs.push_back(singEng);

	return singEng;
}