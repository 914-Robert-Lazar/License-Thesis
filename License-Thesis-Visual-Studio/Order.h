#include <string>

class Order {

public:
	std::string attribution;
	std::string stockName;
	double price;
	uint32_t numberOfShares;
	char buySellIndicator;

	Order(char buySellIndicator, uint32_t numberOfShares, std::string& stockName, double price, std::string& attribution) {
		this->buySellIndicator = buySellIndicator;
		this->numberOfShares = numberOfShares;
		this->stockName = stockName;
		this->price = price;
		this->attribution = attribution;
	}

	Order() = default;
	Order(const Order&) = default;
	Order& operator=(const Order&) = default;
};