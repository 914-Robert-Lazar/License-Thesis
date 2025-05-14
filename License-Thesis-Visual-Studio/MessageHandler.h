#pragma once
#include <unordered_map>
#include <functional>
#include "BookBuilder.h"

using func = std::function<void(std::vector<char>&)>;

class MessageHandler {
private:
	virtual void HandleStockDirectoryMessage(std::vector<char>& message) {}
	virtual void HandleAddOrderMessage(std::vector<char>& message) {}
	virtual void HandleAddOrderWithMPIDMessage(std::vector<char>& message) {}
	virtual void HandleOrderExecutedMessage(std::vector<char>& message) {}
	virtual void HandleOrderExecutedWithPriceMessage(std::vector<char>& message) {}
	virtual void HandleOrderCancelMessage(std::vector<char>& message) {}
	virtual void HandleOrderDeleteMessage(std::vector<char>& message) {}
	virtual void HandleOrderReplaceMessage(std::vector<char>& message) {}
protected:
	std::unordered_map<char, func> handlerChooser;
	uint16_t get2byteIntFromChars(unsigned char b1, unsigned char b0);
	uint32_t get4byteIntFromChars(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	uint64_t get6byteIntFromChars(unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, 
								  unsigned char b1, unsigned char b0);
	uint64_t get8byteIntFromChars(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, 
								  unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
	double convertToPriceWith4Decimals(uint64_t number);
	double convertToPriceWith8Decimals(uint64_t number);
public:
	uint64_t orderRelatedMessageCounter = 0;
	virtual void HandleMessage(std::vector<char>& message);
	MessageHandler() {

		handlerChooser['R'] = [this](std::vector<char>& message) {
			return HandleStockDirectoryMessage(message);
			};
		handlerChooser['A'] = [this](std::vector<char>& message) {
			return HandleAddOrderMessage(message);
			};
		handlerChooser['F'] = [this](std::vector<char>& message) {
			return HandleAddOrderWithMPIDMessage(message);
			};
		handlerChooser['E'] = [this](std::vector<char>& message) {
			return HandleOrderExecutedMessage(message);
			};
		handlerChooser['C'] = [this](std::vector<char>& message) {
			return HandleOrderExecutedWithPriceMessage(message);
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
	}

	virtual ~MessageHandler() {}
};