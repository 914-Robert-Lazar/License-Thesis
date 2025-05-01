#pragma once
#include <unordered_map>
#include "Security.h"
#include "OrderBook.h"

class BookBuilder
{
	std::unordered_map<uint16_t, Security> securityDetails;
	std::map<uint16_t, OrderBook> orderBooks;
	std::map<uint64_t, Order> orders;
public:
	//bool dayStarted = false;
	//bool systemHoursStarted = false;
	//bool marketHoursStarted = false;
	//double MWCBLevel1;
	//double MWCBLevel2;
	//double MWCBLevel3;
	//char MWCBlevelBreached = '0';

	bool addSecurity(uint16_t stockLocate, Security& security);
	bool addOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, Order& order);
	bool executeOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t executedShares);
	bool cancelOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t cancelledShares);
	bool deleteOrder(uint16_t stockLocate, uint64_t orderReferenceNumber);
	Order getOrder(uint64_t orderReferenceNumber);
	std::ostream& printOrderBook(std::ostream& output);
};

