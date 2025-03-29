#pragma once
#include <unordered_map>
#include "Security.h"

class BookBuilder
{
	std::unordered_map<uint16_t, Security> securityDetails;

public:
	bool dayStarted = false;
	bool systemHoursStarted = false;
	bool marketHoursStarted = false;
	uint64_t MWCBLevel1;
	uint64_t MWCBLevel2;
	uint64_t MWCBLevel3;
	char MWCBlevelBreached = '0';

	bool addSecurity(uint16_t stockLocate, Security& security);
	bool setTradingState(uint16_t stockLocate, char state);
	bool setRegSHOState(uint16_t stockLocate, char state);
	bool setMarketParticipant(uint16_t stockLocate, MarketParticipant& marketParticipant);
};

