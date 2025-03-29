#include <unordered_map>
#include <functional>
#include "BookBuilder.h"

using func = std::function<bool(std::vector<char>&)>;

class MessageHandler {
private:
	std::unordered_map<char, func> handlerChooser;
	BookBuilder& bookBuilder;

	bool HandleSystemEventMessage(std::vector<char>& message);
	bool HandleStockDirectoryMessage(std::vector<char>& message);
	bool HandleStockTradingActionMessage(std::vector<char>& message);
	bool HandleRegSHORestrictionMessage(std::vector<char>& message);
	bool HandleMarketParticipantPositionMessage(std::vector<char>& message);
	bool HandleMWCBDeclineLevelMessage(std::vector<char>& message);
	bool HandleMWCBStatusMessage(std::vector<char>& message);
	bool HandleQuotingPeriodUpdateMessage(std::vector<char>& message);
	bool HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message);
	bool HandleOperationalHaltMessage(std::vector<char>& message);
	bool HandleAddOrderMessage(std::vector<char>& message);
	bool HandleAddOrderWithMPIDMessage(std::vector<char>& message);
	bool HandleAddOrderExecutedMessage(std::vector<char>& message);
	bool HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message);
	bool HandleOrderCancelMessage(std::vector<char>& message);
	bool HandleOrderDeleteMessage(std::vector<char>& message);
	bool HandleOrderReplaceMessage(std::vector<char>& message);
	bool HandleTradeMessage(std::vector<char>& message);
	bool HandleCrossTradeMessage(std::vector<char>& message);
	bool HandleBrokenTradeMessage(std::vector<char>& message);
	bool HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message);
	bool HandleRetailInterestMessage(std::vector<char>& message);
	bool HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message);

	uint16_t get2byteIntFromChars(unsigned char b1, unsigned char b0);
	uint32_t get4byteIntFromChars(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	uint64_t get6byteIntFromChars(unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	uint64_t get8byteIntFromChars(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);

public:
	MessageHandler(BookBuilder& bookBuilder) : bookBuilder(bookBuilder){
		handlerChooser['S'] = [this](std::vector<char>& message) {
			return this->HandleSystemEventMessage(message);
			};
		handlerChooser['R'] = [this](std::vector<char>& message) {
			return HandleStockDirectoryMessage(message);
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

	void HandleMessage(std::vector<char>& message);
};