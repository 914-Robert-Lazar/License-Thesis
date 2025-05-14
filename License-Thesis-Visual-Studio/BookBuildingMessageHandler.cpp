#include "BookBuildingMessageHandler.h"

void BookBuildingMessageHandler::HandleStockDirectoryMessage(std::vector<char>& message)
{
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	std::string stockName(message.begin() + 11, message.begin() + 19);
	Security security = Security(stockName, message[19], message[20], get4byteIntFromChars(message[21], message[22], message[23], message[24]),
		message[25] == 'Y' ? true : false, message[26], std::string(message.begin() + 27, message.begin() + 29), message[29] == 'P' ? true : false,
		message[30], message[31], message[32], message[33], get4byteIntFromChars(message[34], message[35], message[36], message[37]), message[38] == 'Y' ? true : false);

	bookBuilder.addSecurity(stockLocate, security);
}

void BookBuildingMessageHandler::HandleAddOrderMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	std::string stockName(message.begin() + 24, message.begin() + 32);
	std::string marketParticipant = "NSDQ";
	Order order = Order(message[19], get4byteIntFromChars(message[20], message[21], message[22], message[23]), stockName,
		convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35])), marketParticipant);
	bookBuilder.addOrder(stockLocate, orderReferenceNumber, order);
}

void BookBuildingMessageHandler::HandleAddOrderWithMPIDMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	std::string stockName(message.begin() + 24, message.begin() + 32);
	std::string marketParticipant(message.begin() + 36, message.end());
	Order order = Order(message[19], get4byteIntFromChars(message[20], message[21], message[22], message[23]), stockName,
		convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35])), marketParticipant);
	bookBuilder.addOrder(stockLocate, orderReferenceNumber, order);
}

void BookBuildingMessageHandler::HandleOrderExecutedMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	bookBuilder.executeOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
}

void BookBuildingMessageHandler::HandleOrderExecutedWithPriceMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	bookBuilder.executeOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
}

void BookBuildingMessageHandler::HandleOrderCancelMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	bookBuilder.cancelOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
}

void BookBuildingMessageHandler::HandleOrderDeleteMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	bookBuilder.deleteOrder(stockLocate, orderReferenceNumber);
}

void BookBuildingMessageHandler::HandleOrderReplaceMessage(std::vector<char>& message)
{
	this->orderRelatedMessageCounter++;
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	uint64_t oldOrderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	uint64_t newOrderReferenceNumber = get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]);
	Order oldOrder = bookBuilder.getOrder(oldOrderReferenceNumber);
	bookBuilder.deleteOrder(stockLocate, oldOrderReferenceNumber);
	Order newOrder = Order(oldOrder.buySellIndicator, get4byteIntFromChars(message[27], message[28], message[29], message[30]), oldOrder.stockName,
		convertToPriceWith4Decimals(get4byteIntFromChars(message[31], message[32], message[33], message[34])), oldOrder.attribution);
	bookBuilder.addOrder(stockLocate, newOrderReferenceNumber, newOrder);
}