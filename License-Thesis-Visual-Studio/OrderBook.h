#include "Order.h"
#include <map>

class OrderBook {

public:
	std::map<double, int64_t, std::greater<double>> buyBook;
	std::map<double, int64_t> sellBook;
	void addOrder(Order& order);
	void executeOrder(char buyOrSell, double priceLevel, uint32_t sharesExecuted);
	void cancelOrder(char buyOrSell, double priceLevel, uint32_t sharesCancelled);
	void deleteOrder(char buyOrSell, double priceLevel);
};