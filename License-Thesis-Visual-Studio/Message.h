#pragma once
#include <cstdint>
class Message
{
	uint64_t timeStamp;
	uint16_t stockLocate;
	uint16_t trackingNumber;
	char type;
public:
	Message(char type, uint16_t stockLocate, uint16_t trackingNumber, uint64_t timeStamp);
};

