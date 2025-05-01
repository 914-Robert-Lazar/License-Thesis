#pragma once
#include <string>
#include "MarketParticipant.h"
#include <unordered_map>
class Security
{
	std::string issueSubType;
	uint32_t roundLotSize;
	uint32_t ETPLeverageFactor;
	bool roundLotOnly;
	bool liveOrTest;
	char shortSaleIndicator;
	char IPOflag;
	char limitUpDownPriceTier;
	char exchangeTradedProductFlag;
	bool ETPInverseFlag;
	char issueClassification;
	char financialStatus;
	char marketCategory;
public:
	std::string name;
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
};

