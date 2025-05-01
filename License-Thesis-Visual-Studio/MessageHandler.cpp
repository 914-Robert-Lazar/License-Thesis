#include "MessageHandler.h"
#include <string>
#include "Security.h"

//bool MessageHandler::HandleSystemEventMessage(std::vector<char>& message) 
//{
//	char eventCode = message[11];
//	switch (eventCode)
//	{
//	case 'O':
//		bookBuilder.dayStarted = true;
//		break;
//	case 'S':
//		bookBuilder.systemHoursStarted = true;
//		break;
//	case 'Q':
//		bookBuilder.marketHoursStarted = true;
//		break;
//	case 'C':
//		bookBuilder.dayStarted = false;
//		break;
//	case 'E':
//		bookBuilder.systemHoursStarted = false;
//		break;
//	case 'M':
//		bookBuilder.marketHoursStarted = false;
//		break;
//	default:
//		break;
//	}
//
//	return true;
//}
//
//bool MessageHandler::HandleStockDirectoryMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	std::string stockName(message.begin() + 11, message.begin() + 19);
//	Security security = Security(stockName, message[19], message[20], get4byteIntFromChars(message[21], message[22], message[23], message[24]),
//		message[25] == 'Y' ? true : false, message[26], std::string(message.begin() + 27, message.begin() + 29), message[29] == 'P' ? true : false,
//		message[30], message[31], message[32], message[33], get4byteIntFromChars(message[34], message[35], message[36], message[37]), message[38] == 'Y' ? true : false);
//
//	bookBuilder.addSecurity(stockLocate, security);
//	return true;
//}
//
//bool MessageHandler::HandleStockTradingActionMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	bookBuilder.setTradingState(stockLocate, message[19]);
//	return true;
//}
//
//bool MessageHandler::HandleRegSHORestrictionMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	bookBuilder.setRegSHOState(stockLocate, message[19]);
//	return true;
//
//}
//
//bool MessageHandler::HandleMarketParticipantPositionMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	MarketParticipant participant = MarketParticipant(std::string(message.begin() + 11, message.begin() + 15), message[23] == 'Y' ? true : false, message[24], message[25]);
//	bookBuilder.setMarketParticipant(stockLocate, participant);
//	return true;
//}
//
//bool MessageHandler::HandleMWCBDeclineLevelMessage(std::vector<char>& message)
//{
//	bookBuilder.MWCBLevel1 = double (get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]) / 100000000);
//	bookBuilder.MWCBLevel2 = double (get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]) / 100000000);
//	bookBuilder.MWCBLevel3 = double (get8byteIntFromChars(message[27], message[28], message[29], message[30], message[31], message[32], message[33], message[34]) / 100000000);
//	return true;
//}
//
//bool MessageHandler::HandleMWCBStatusMessage(std::vector<char>& message)
//{
//	bookBuilder.MWCBlevelBreached = message[11];
//	return true;
//}
//
//bool MessageHandler::HandleQuotingPeriodUpdateMessage(std::vector<char>& message)
//{
//	return false;
//}
//
//bool MessageHandler::HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message)
//{
//	std::string stockName(message.begin() + 11, message.begin() + 19);
//	float referencePrice = float (get4byteIntFromChars(message[19], message[20], message[21], message[22]) / 10000);
//	float upperPrice = get4byteIntFromChars(message[23], message[24], message[25], message[26]);
//	uint32_t lowerPrice = get4byteIntFromChars(message[27], message[28], message[29], message[30]);
//	uint32_t extension = get4byteIntFromChars(message[31], message[32], message[33], message[34]);
//	return true;
//}
//
//bool MessageHandler::HandleOperationalHaltMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	char marketCode = message[19];
//	char action = message[20];
//	bookBuilder.updateHalt(stockLocate, marketCode, action == 'H' ? true : false);
//	return true;
//}
//
//bool MessageHandler::HandleAddOrderMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	std::string stockName(message.begin() + 24, message.begin() + 33);
//	std::string marketParticipant = "NSDQ";
//	Order order = Order(message[19], get4byteIntFromChars(message[20], message[21], message[22], message[23]), stockName,
//		convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35])), marketParticipant);
//	bookBuilder.addOrder(stockLocate, orderReferenceNumber, order);
//	return true;
//}
//
//bool MessageHandler::HandleAddOrderWithMPIDMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	std::string stockName(message.begin() + 24, message.begin() + 33);
//	std::string marketParticipant(message.begin() + 36, message.end());
//	Order order = Order(message[19], get4byteIntFromChars(message[20], message[21], message[22], message[23]), stockName,
//		convertToPriceWith4Decimals(get4byteIntFromChars(message[32], message[33], message[34], message[35])), marketParticipant);
//	bookBuilder.addOrder(stockLocate, orderReferenceNumber, order);
//	return true;
//}
//
//bool MessageHandler::HandleAddOrderExecutedMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	bookBuilder.executeOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
//	return true;
//}
//
//bool MessageHandler::HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	bookBuilder.executeOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
//	return true;
//}
//
//bool MessageHandler::HandleOrderCancelMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	bookBuilder.cancelOrder(stockLocate, orderReferenceNumber, get4byteIntFromChars(message[19], message[20], message[21], message[22]));
//	return true;
//}
//
//bool MessageHandler::HandleOrderDeleteMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t orderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	bookBuilder.deleteOrder(stockLocate, orderReferenceNumber);
//	return true;
//}
//
//bool MessageHandler::HandleOrderReplaceMessage(std::vector<char>& message)
//{
//	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
//	uint64_t oldOrderReferenceNumber = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
//	uint64_t newOrderReferenceNumber = get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]);
//	Order oldOrder = bookBuilder.getOrder(oldOrderReferenceNumber);
//	bookBuilder.deleteOrder(stockLocate, oldOrderReferenceNumber);
//	Order newOrder = Order(oldOrder.buySellIndicator, get4byteIntFromChars(message[27], message[28], message[29], message[30]), oldOrder.stockName,
//		convertToPriceWith4Decimals(get4byteIntFromChars(message[31], message[32], message[33], message[34])), oldOrder.attribution);
//	bookBuilder.addOrder(stockLocate, newOrderReferenceNumber, newOrder);
//	return false;
//}
//
////ignored for order book
//bool MessageHandler::HandleTradeMessage(std::vector<char>& message)
//{
//	return false;
//}
//
////ignored for order book
//bool MessageHandler::HandleCrossTradeMessage(std::vector<char>& message)
//{
//	return false;
//}
//
////ignored for order book
//bool MessageHandler::HandleBrokenTradeMessage(std::vector<char>& message)
//{
//	return false;
//}
//
////ignored for order book
//bool MessageHandler::HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message)
//{
//	return false;
//}
//
//bool MessageHandler::HandleRetailInterestMessage(std::vector<char>& message)
//{
//	return false;
//}
//
//bool MessageHandler::HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message)
//{
//	return false;
//}

uint16_t MessageHandler::get2byteIntFromChars(unsigned char b1, unsigned char b0)
{
	return (static_cast<uint16_t>(b1) << 8) | static_cast<uint16_t>(b0);
}

uint32_t MessageHandler::get4byteIntFromChars(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0)
{
	return  (static_cast<uint64_t>(b3) << 24) |
			(static_cast<uint64_t>(b2) << 16) |
			(static_cast<uint64_t>(b1) << 8) |
			(static_cast<uint64_t>(b0));
}

uint64_t MessageHandler::get6byteIntFromChars(unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0)
{
	return  (static_cast<uint64_t>(b5) << 40) |
			(static_cast<uint64_t>(b4) << 32) |
			(static_cast<uint64_t>(b3) << 24) |
			(static_cast<uint64_t>(b2) << 16) |
			(static_cast<uint64_t>(b1) << 8) |
			(static_cast<uint64_t>(b0));
}

uint64_t MessageHandler::get8byteIntFromChars(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0)
{
	return  (static_cast<uint64_t>(b7) << 56) |
			(static_cast<uint64_t>(b6) << 48) |
			(static_cast<uint64_t>(b5) << 40) |
			(static_cast<uint64_t>(b4) << 32) |
			(static_cast<uint64_t>(b3) << 24) |
			(static_cast<uint64_t>(b2) << 16) |
			(static_cast<uint64_t>(b1) << 8) |
			(static_cast<uint64_t>(b0));
}

double MessageHandler::convertToPriceWith4Decimals(uint64_t number)
{
	return double(number) / 10000;
}

double MessageHandler::convertToPriceWith8Decimals(uint64_t number)
{
	return double(number) / 100000000;
}

void MessageHandler::HandleMessage(std::vector<char>& message)
{
	if (handlerChooser.find(message[0]) != handlerChooser.end())
	{
		handlerChooser[message[0]](message);
	}
}
