#pragma once
#include <string>
#include "MarketParticipant.h"
#include <unordered_map>
class Security
{
	std::string name;
	char marketCategory;
	char financialStatus;
	uint32_t roundLotSize;
	bool roundLotOnly;
	char issueClassification;
	std::string issueSubType;
	bool liveOrTest;
	char shortSaleIndicator;
	char IPOflag;
	char limitUpDownPriceTier;
	char exchangeTradedProductFlag;
	uint32_t ETPLeverageFactor;
	bool ETPInverseFlag;
	char tradingState;
	char RegSHOShortSalePriceTestRestrictionStatus;

	std::unordered_map<std::string, MarketParticipant> marketParticipants;

public:
	Security(std::string name,
		char marketCategory,
		char financialStatus,
		uint32_t roundLotSize,
		bool roundLotOnly,
		char issueClassification,
		std::string issueSubType,
		bool liveOrTest,
		char shortSaleIndicator,
		char IPOflag,
		char limitUpDownPriceTier,
		char exchangeTradedProductFlag,
		uint32_t ETPLeverageFactor,
		bool ETPInverseFlag)
	{
		this->name = name;
		this->marketCategory = marketCategory;
		this->financialStatus = financialStatus;
		this->roundLotSize = roundLotSize;
		this->roundLotOnly = roundLotOnly;
		this->issueClassification = issueClassification;
		this->issueSubType = issueSubType;
		this->liveOrTest = liveOrTest;
		this->shortSaleIndicator = shortSaleIndicator;
		this->IPOflag = IPOflag;
		this->limitUpDownPriceTier = limitUpDownPriceTier;
		this->exchangeTradedProductFlag = exchangeTradedProductFlag;
		this->ETPLeverageFactor = ETPLeverageFactor;
		this->ETPInverseFlag = ETPInverseFlag;
	}

	Security() = default;
	Security(const Security&) = default;
	Security& operator=(const Security&) = default;
	void setTradingState(char state);
	void setRegSHOState(char state);
	void setMarketParticipant(MarketParticipant& participant);
};

