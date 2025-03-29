#include "Message.h"

Message::Message(char type, uint16_t stockLocate, uint16_t trackingNumber, uint64_t timeStamp)
{
	this->type = type;
	this->stockLocate = stockLocate;
	this->trackingNumber = trackingNumber;
	this->timeStamp = timeStamp;
}