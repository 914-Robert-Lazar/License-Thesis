#include "MessageHandler.h"
#include <string>
#include "Security.h"

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
