#pragma once
#include <string>
class MarketParticipant
{
	bool primaryMarketMaker;
	char marketMakerMode;
	char marketParticipantState;
public:
	std::string identifier;
	MarketParticipant(std::string identifier,
		bool primaryMarketMaker,
		char marketMakerMode,
		char marketParticipantState)
	{
		this->identifier = identifier;
		this->primaryMarketMaker = primaryMarketMaker;
		this->marketMakerMode = marketMakerMode;
		this->marketParticipantState = marketParticipantState;
	}

	MarketParticipant() = default;
	MarketParticipant(const MarketParticipant&) = default;
	MarketParticipant& operator=(const MarketParticipant&) = default;
};

