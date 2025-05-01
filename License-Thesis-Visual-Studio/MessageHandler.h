#pragma once
#include <unordered_map>
#include <functional>
#include "BookBuilder.h"

using func = std::function<void(std::vector<char>&)>;

class MessageHandler {
private:
	std::unordered_map<char, func> handlerChooser;
	/*BookBuilder& bookBuilder;*/

	/*void HandleSystemEventMessage(std::vector<char>& message);*/
	virtual void HandleStockDirectoryMessage(std::vector<char>& message) {}
	/*void HandleStockTradingActionMessage(std::vector<char>& message);
	void HandleRegSHORestrictionMessage(std::vector<char>& message);
	void HandleMarketParticipantPositionMessage(std::vector<char>& message);
	void HandleMWCBDeclineLevelMessage(std::vector<char>& message);
	void HandleMWCBStatusMessage(std::vector<char>& message);
	void HandleQuotingPeriodUpdateMessage(std::vector<char>& message);
	void HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message);
	void HandleOperationalHaltMessage(std::vector<char>& message);*/
	
	/*void HandleTradeMessage(std::vector<char>& message);
	void HandleCrossTradeMessage(std::vector<char>& message);
	void HandleBrokenTradeMessage(std::vector<char>& message);
	void HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message);
	void HandleRetailInterestMessage(std::vector<char>& message);
	void HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message);*/
protected:
	virtual void HandleAddOrderMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleAddOrderWithMPIDMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleAddOrderExecutedMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleOrderCancelMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleOrderDeleteMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	virtual void HandleOrderReplaceMessage(std::vector<char>& message) { orderRelatedMessageCounter++; }
	uint16_t get2byteIntFromChars(unsigned char b1, unsigned char b0);
	uint32_t get4byteIntFromChars(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	uint64_t get6byteIntFromChars(unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	uint64_t get8byteIntFromChars(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	double convertToPriceWith4Decimals(uint64_t number);
	double convertToPriceWith8Decimals(uint64_t number);
public:
	int orderRelatedMessageCounter = 0;
	MessageHandler() /*: bookBuilder(bookBuilder)*/{
		/*handlerChooser['S'] = [this](std::vector<char>& message) {
			return this->HandleSystemEventMessage(message);
			};*/
		handlerChooser['R'] = [this](std::vector<char>& message) {
			return HandleStockDirectoryMessage(message);
			};
		/*handlerChooser['H'] = [this](std::vector<char>& message) {
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
			};*/
		handlerChooser['A'] = [this](std::vector<char>& message) {
			return HandleAddOrderMessage(message);
			};
		handlerChooser['F'] = [this](std::vector<char>& message) {
			return HandleAddOrderWithMPIDMessage(message);
			};
		handlerChooser['E'] = [this](std::vector<char>& message) {
			return HandleAddOrderExecutedMessage(message);
			};
		handlerChooser['C'] = [this](std::vector<char>& message) {
			return HandleAddOrderExecutedWithPriceMessage(message);
			};
		handlerChooser['X'] = [this](std::vector<char>& message) {
			return HandleOrderCancelMessage(message);
			};
		handlerChooser['D'] = [this](std::vector<char>& message) {
			return HandleOrderDeleteMessage(message);
			};
		handlerChooser['U'] = [this](std::vector<char>& message) {
			return HandleOrderReplaceMessage(message);
			};
		/*handlerChooser['P'] = [this](std::vector<char>& message) {
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
			};*/
	}

	void HandleMessage(std::vector<char>& message);

	virtual ~MessageHandler() {}
};