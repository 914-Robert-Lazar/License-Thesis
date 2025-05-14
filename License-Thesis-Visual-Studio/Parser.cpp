#include "Parser.h"

void Parser::HandleSystemEventMessage(std::vector<char>& message)
{
	char eventCode = message[11];
}

void Parser::HandleStockDirectoryMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char marketCategory = message[19];
	char financialStatusIndicator = message[20];
	uint32_t roundLotSize = get4byteIntFromChars(message[21], message[22], message[23], message[24]);
	char roundLotsOnly = message[25];
	char issueClassification = message[26];
	std::string issueSubType(message.begin() + 27, message.begin() + 29);
	char authenticity = message[29];
	char shorSaleThresholdIndicator = message[30];
	char IPOFlag = message[31];
	char LULDReferencePriceTier = message[32];
	char ETPFlag = message[33];
	uint32_t ETPLeverageFactor = get4byteIntFromChars(message[34], message[35], message[36], message[37]);
	char inverseIndicator = message[38];
}

void Parser::HandleStockTradingActionMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char tradingState = message[19];
	char reserved = message[20];
	std::string reason(message.begin() + 21, message.end());
}

void Parser::HandleRegSHORestrictionMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char regSHOAction = message[19];
}

void Parser::HandleMarketParticipantPositionMessage(std::vector<char>& message)
{
	std::string MPID(message.begin() + 11, message.begin() + 15);
	std::string stockName(message.begin() + 15, message.begin() + 23);
	char primaryMarketMaker = message[23];
	char marketMakerMode = message[24];
	char marketMakerState = message[25];
}

void Parser::HandleMWCBDeclineLevelMessage(std::vector<char>& message)
{
	double level1 = convertToPriceWith8Decimals(get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]));
	double level2 = convertToPriceWith8Decimals(get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]));
	double level3 = convertToPriceWith8Decimals(get8byteIntFromChars(message[27], message[28], message[29], message[30], message[31], message[32], message[33], message[34]));
}

void Parser::HandleMWCBStatusMessage(std::vector<char>& message)
{
	char breachedLevele = message[11];
}

void Parser::HandleQuotingPeriodUpdateMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	uint32_t IPOQuotationReleaseTime = get4byteIntFromChars(message[19], message[20], message[21], message[22]);
	char IPOQuotationReleaseQualifier = message[23];
	double IPOPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[24], message[25], message[26], message[27]));
}

void Parser::HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	double auctionCollarReferencePrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[19], message[20], message[21], message[22]));
	double upperAuctionCollarPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[23], message[24], message[25], message[26]));
	double lowerAuctionCollarPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[27], message[28], message[29], message[30]));
	uint32_t auctionCollarExtension = get4byteIntFromChars(message[31], message[32], message[33], message[34]);
}

void Parser::HandleOperationalHaltMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char marketCode = message[19];
	char operationalHaltAction = message[20];
}

void Parser::HandleAddOrderMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	char buySellIndicator = message[19];
	uint32_t shares = get4byteIntFromChars(message[20], message[21], message[22], message[23]);
	std::string stockName(message.begin() + 24, message.begin() + 32);
	double price = convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35]));
}

void Parser::HandleAddOrderWithMPIDMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	char buySellIndicator = message[19];
	uint32_t shares = get4byteIntFromChars(message[20], message[21], message[22], message[23]);
	std::string stockName(message.begin() + 24, message.begin() + 32);
	double price = convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35]));
	std::string marketParticipant(message.begin() + 36, message.end());
}

void Parser::HandleOrderExecutedMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint32_t executedShares = get4byteIntFromChars(message[19], message[20], message[21], message[22]);
	uint64_t matchNumber = get8byteIntFromChars(message[23], message[24], message[25], message[26], message[27], message[28], message[29], message[30]);
}

void Parser::HandleOrderExecutedWithPriceMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint32_t executedShares = get4byteIntFromChars(message[19], message[20], message[21], message[22]);
	uint64_t matchNumber = get8byteIntFromChars(message[23], message[24], message[25], message[26], message[27], message[28], message[29], message[30]);
	char printable = message[31];
	double executionPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35]));
}

void Parser::HandleOrderCancelMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint32_t canceledShares = get4byteIntFromChars(message[19], message[20], message[21], message[22]);
}

void Parser::HandleOrderDeleteMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
}

void Parser::HandleOrderReplaceMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint64_t originalOrderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint64_t newOrderReferenceNumber = get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]);
	uint32_t shares = get4byteIntFromChars(message[27], message[28], message[29], message[30]);
	double price = convertToPriceWith4Decimals(get4byteIntFromChars(message[31], message[32], message[33], message[34]));
}

void Parser::HandleTradeMessage(std::vector<char>& message)
{
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	char buySellIndicator = message[19];
	uint32_t shares = get4byteIntFromChars(message[20], message[21], message[22], message[23]);
	std::string stockName(message.begin() + 24, message.begin() + 32);
	double price = convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35]));
	uint64_t matchNumber = get8byteIntFromChars(message[36], message[37], message[38], message[39], message[40], message[41], message[42], message[43]);
}

void Parser::HandleCrossTradeMessage(std::vector<char>& message)
{
	uint64_t shares = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	std::string stockName(message.begin() + 19, message.begin() + 27);
	double crossPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[27], message[28], message[29], message[30]));
	uint64_t matchNumber = get8byteIntFromChars(message[31], message[32], message[33], message[34], message[35], message[36], message[37], message[38]);
	char crossType = message[39];
}

void Parser::HandleBrokenTradeMessage(std::vector<char>& message)
{
	uint64_t matchNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
}

void Parser::HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message)
{
	uint64_t pairedShares = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint64_t imbalanceShares = get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]);
	char imbalanceDirection = message[27];
	std::string stockName(message.begin() + 28, message.begin() + 36);
	double fairPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[36], message[37], message[38], message[39]));
	double nearPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[40], message[41], message[42], message[43]));
	double currentReferencePrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[44], message[45], message[46], message[47]));
	char crossType = message[48];
	char priceVariationIndicator = message[49];
}

void Parser::HandleRetailInterestMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char interestFlag = message[19];
}

void Parser::HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message)
{
	std::string stockName(message.begin() + 11, message.begin() + 19);
	char openEligibilityStatus = message[19];
	double minimumAllowablePrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[20], message[21], message[22], message[23]));
	double maximumAllowablePrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[24], message[25], message[26], message[27]));
	double nearExecutionPrice = convertToPriceWith4Decimals(get4byteIntFromChars(message[28], message[29], message[30], message[31]));
	uint64_t nearExecutionTime = get8byteIntFromChars(message[32], message[33], message[34], message[35], message[36], message[37], message[38], message[39]);
	double lowerPriceRangeCollar = convertToPriceWith4Decimals(get4byteIntFromChars(message[40], message[41], message[42], message[43]));
	double upperPriceRangeCollar = convertToPriceWith4Decimals(get4byteIntFromChars(message[44], message[45], message[46], message[47]));
}

void Parser::BaseParsing(std::vector<char>& message)
{
	char messageType = message[0];
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint16_t trackingNumber = get2byteIntFromChars(message[3], message[4]);
	uint64_t timeStamp = get6byteIntFromChars(message[5], message[6], message[7], message[8], message[9], message[10]);
}

void Parser::HandleMessage(std::vector<char>& message)
{
	BaseParsing(message);
	MessageHandler::HandleMessage(message);
}

Parser::Parser() : MessageHandler()
{
	
	handlerChooser['S'] = [this](std::vector<char>& message) {
		return this->HandleSystemEventMessage(message);
		};
	handlerChooser['H'] = [this](std::vector<char>& message) {
		return HandleStockTradingActionMessage(message);
		};
	handlerChooser['Y'] = [this](std::vector<char>& message) {
		return HandleRegSHORestrictionMessage(message);
		};
	handlerChooser['L'] = [this](std::vector<char>& message) {
		return HandleMarketParticipantPositionMessage(message);
		};
	handlerChooser['V'] = [this](std::vector<char>& message) {
		return HandleMWCBDeclineLevelMessage(message);
		};
	handlerChooser['W'] = [this](std::vector<char>& message) {
		return HandleMWCBStatusMessage(message);
		};
	handlerChooser['K'] = [this](std::vector<char>& message) {
		return HandleQuotingPeriodUpdateMessage(message);
		};
	handlerChooser['J'] = [this](std::vector<char>& message) {
		return HandleLimitUpDownAuctionCollarMessage(message);
		};
	handlerChooser['h'] = [this](std::vector<char>& message) {
		return HandleOperationalHaltMessage(message);
		};
	handlerChooser['P'] = [this](std::vector<char>& message) {
		return HandleTradeMessage(message);
		};
	handlerChooser['Q'] = [this](std::vector<char>& message) {
		return HandleCrossTradeMessage(message);
		};
	handlerChooser['B'] = [this](std::vector<char>& message) {
		return HandleBrokenTradeMessage(message);
		};
	handlerChooser['I'] = [this](std::vector<char>& message) {
		return HandleNetOrderImbalanceIndicatorMessage(message);
		};
	handlerChooser['N'] = [this](std::vector<char>& message) {
		return HandleRetailInterestMessage(message);
		};
}
