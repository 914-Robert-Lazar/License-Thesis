#pragma once
#include <unordered_map>
#include "Security.h"
#include "OrderBook.h"

class BookBuilder
{
	std::unordered_map<uint16_t, Security> securityDetails;
	std::unordered_map<uint16_t, OrderBook> orderBooks;
	std::unordered_map<uint64_t, Order> orders;
public:
	bool addSecurity(uint16_t stockLocate, Security& security);
	bool addOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, Order& order);
	bool executeOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t executedShares);
	bool cancelOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t cancelledShares);
	bool deleteOrder(uint16_t stockLocate, uint64_t orderReferenceNumber);
	Order getOrder(uint64_t orderReferenceNumber);
	std::ostream& printOrderBook(std::ostream& output);
};

