/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: PassengerJetFactory.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "PassengerJetFactory.h"
#include "PassengerJet.h"

PassengerJetFactory::PassengerJetFactory()
{

}

PassengerJetFactory::~PassengerJetFactory()
{

}

PassengerJetFactory *PassengerJetFactory::getInstance()
{
	static PassengerJetFactory *theInstance = nullptr;
	if (theInstance == nullptr)
	{
		theInstance = new PassengerJetFactory();
	}

	return theInstance;
}

Aircraft *PassengerJetFactory::getAircraft(char *name)
{
	for (int i = 0; i < pasJets.size(); i++)
	{
		if (strcmp(pasJets[i]->m_make, name) == 0)
		{
			return pasJets[i];
		}
	}

	PassengerJet *pasJet = new PassengerJet();

	pasJets.push_back(pasJet);

	return pasJet;
}