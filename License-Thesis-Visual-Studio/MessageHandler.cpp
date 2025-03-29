#include "MessageHandler.h"
#include "Message.h"
#include <string>
#include "Security.h"

bool MessageHandler::HandleSystemEventMessage(std::vector<char>& message) 
{
	char eventCode = message[11];
	switch (eventCode)
	{
	case 'O':
		bookBuilder.dayStarted = true;
		break;
	case 'S':
		bookBuilder.systemHoursStarted = true;
		break;
	case 'Q':
		bookBuilder.marketHoursStarted = true;
		break;
	case 'C':
		bookBuilder.dayStarted = false;
		break;
	case 'E':
		bookBuilder.systemHoursStarted = false;
		break;
	case 'M':
		bookBuilder.marketHoursStarted = false;
		break;
	default:
		break;
	}

	return true;
}

bool MessageHandler::HandleStockDirectoryMessage(std::vector<char>& message)
{
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	std::string stockName(message.begin() + 11, message.begin() + 19);
	Security security = Security(stockName, message[19], message[20], get4byteIntFromChars(message[21], message[22], message[23], message[24]),
		message[25] == 'Y' ? true : false, message[26], std::string(message.begin() + 27, message.begin() + 29), message[29] == 'P' ? true : false,
		message[30], message[31], message[32], message[33], get4byteIntFromChars(message[34], message[35], message[36], message[37]), message[38] == 'Y' ? true : false);

	bookBuilder.addSecurity(stockLocate, security);
	return true;
}

bool MessageHandler::HandleStockTradingActionMessage(std::vector<char>& message)
{
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	bookBuilder.setTradingState(stockLocate, message[19]);
	return true;
}

bool MessageHandler::HandleRegSHORestrictionMessage(std::vector<char>& message)
{
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	bookBuilder.setRegSHOState(stockLocate, message[19]);
	return true;

}

bool MessageHandler::HandleMarketParticipantPositionMessage(std::vector<char>& message)
{
	uint16_t stockLocate = get2byteIntFromChars(message[1], message[2]);
	MarketParticipant participant = MarketParticipant(std::string(message.begin() + 11, message.begin() + 15), message[23] == 'Y' ? true : false, message[24], message[25]);
	bookBuilder.setMarketParticipant(stockLocate, participant);
	return true;
}

bool MessageHandler::HandleMWCBDeclineLevelMessage(std::vector<char>& message)
{
	bookBuilder.MWCBLevel1 = get8byteIntFromChars(message[11], message[12], message[13], message[14], message[15], message[16], message[17], message[18]);
	bookBuilder.MWCBLevel2 = get8byteIntFromChars(message[19], message[20], message[21], message[22], message[23], message[24], message[25], message[26]);
	bookBuilder.MWCBLevel3 = get8byteIntFromChars(message[27], message[28], message[29], message[30], message[31], message[32], message[33], message[34]);
	return true;
}

bool MessageHandler::HandleMWCBStatusMessage(std::vector<char>& message)
{
	bookBuilder.MWCBlevelBreached = message[11];
}

bool MessageHandler::HandleQuotingPeriodUpdateMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleOperationalHaltMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleAddOrderMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleAddOrderWithMPIDMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleAddOrderExecutedMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleOrderCancelMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleOrderDeleteMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleOrderReplaceMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleTradeMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleCrossTradeMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleBrokenTradeMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleRetailInterestMessage(std::vector<char>& message)
{
	return false;
}

bool MessageHandler::HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message)
{
	return false;
}

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

void MessageHandler::HandleMessage(std::vector<char>& message)
{
	Message structuredMessage = Message(message[0], get2byteIntFromChars(message[1], message[2]), get2byteIntFromChars(message[3], message[4]),
		get6byteIntFromChars(message[5], message[6], message[7], message[8], message[9], message[10]));
	handlerChooser[message[0]](message);
}
