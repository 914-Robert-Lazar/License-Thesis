#include "OrderBook.h"

void OrderBook ::addOrder(Order& order) 
{
	double priceLevel = order.price;
	uint32_t numberOfShares = order.numberOfShares;
	if (order.buySellIndicator == 'B') 
	{
		buyBook[priceLevel] += numberOfShares;
	}
	else 
	{
		sellBook[priceLevel] += numberOfShares;
	}
}

void OrderBook::executeOrder(char buyOrSell, double priceLevel, uint32_t sharesExecuted)
{
	if (buyOrSell == 'B') 
	{
		if (buyBook[priceLevel] <= sharesExecuted)
		{
			buyBook.erase(priceLevel);
			return;
		}
		buyBook[priceLevel] -= sharesExecuted;
	}
	else
	{
		if (sellBook[priceLevel] <= sharesExecuted)
		{
			sellBook.erase(priceLevel);
			return;
		}
		sellBook[priceLevel] -= sharesExecuted;
	}
}

void OrderBook::cancelOrder(char buyOrSell, double priceLevel, uint32_t sharesCancelled)
{
	if (buyOrSell == 'B')
	{
		buyBook[priceLevel] -= sharesCancelled;
	}
	else
	{
		sellBook[priceLevel] -= sharesCancelled;
	}
}

void OrderBook::deleteOrder(char buyOrSell, double priceLevel)
{
	if (buyOrSell == 'B')
	{
		buyBook.erase(priceLevel);
	}
	else
	{
		sellBook.erase(priceLevel);
	}
}
