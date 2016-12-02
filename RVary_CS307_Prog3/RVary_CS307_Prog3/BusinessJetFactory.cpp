/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: BusinessJetFactory.cpp
*   Author: Robert G. Vary
*   Desc: A simulation of airport flights using Design Patterns.
*   Date: 17 October 2015
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "stdafx.h"
#include "BusinessJetFactory.h"
#include "BusinessJet.h"

BusinessJetFactory::BusinessJetFactory()
{

}

BusinessJetFactory::~BusinessJetFactory()
{

}

BusinessJetFactory *BusinessJetFactory::getInstance()
{
	static BusinessJetFactory *theInstance = nullptr;
	if (theInstance == nullptr)
	{
		theInstance = new BusinessJetFactory();
	}

	return theInstance;
}

Aircraft *BusinessJetFactory::getAircraft(char *name)
{
	for (int i=0; i < bizJets.size(); i++)
	{
		if (strcmp(bizJets[i]->m_make, name) == 0)
		{
			return bizJets[i];
		}
	}

	BusinessJet *bizJet = new BusinessJet();

	bizJets.push_back(bizJet);
	
	return bizJet;
}