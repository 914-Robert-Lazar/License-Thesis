#include "Security.h"

void Security::setTradingState(char state)
{
	tradingState = state;
}

void Security::setRegSHOState(char state)
{
	RegSHOShortSalePriceTestRestrictionStatus = state;
}

void Security::setMarketParticipant(MarketParticipant& participant)
{
	marketParticipants[participant.identifier] = participant;
}
