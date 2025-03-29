#include "BookBuilder.h"

bool BookBuilder::addSecurity(uint16_t stockLocate, Security& security)
{
    if (securityDetails.find(stockLocate) != securityDetails.end())
    {
        return false;
    }
    securityDetails[stockLocate] = security;
    return true;
}

bool BookBuilder::setTradingState(uint16_t stockLocate, char state)
{
    if (securityDetails.find(stockLocate) == securityDetails.end())
    {
        return false;
    }
    securityDetails[stockLocate].setTradingState(state);
    return true;
}

bool BookBuilder::setRegSHOState(uint16_t stockLocate, char state)
{
    if (securityDetails.find(stockLocate) == securityDetails.end())
    {
        return false;
    }
    securityDetails[stockLocate].setRegSHOState(state);
    return true;
}

bool BookBuilder::setMarketParticipant(uint16_t stockLocate, MarketParticipant& marketParticipant)
{
    if (securityDetails.find(stockLocate) == securityDetails.end())
    {
        return false;
    }
    securityDetails[stockLocate].setMarketParticipant(marketParticipant);
    return true;
}
