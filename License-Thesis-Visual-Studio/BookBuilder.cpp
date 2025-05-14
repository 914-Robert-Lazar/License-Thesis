#include "BookBuilder.h"
#include <iostream>

bool BookBuilder::addSecurity(uint16_t stockLocate, Security& security)
{
    if (securityDetails.find(stockLocate) != securityDetails.end())
    {
        return false;
    }
    securityDetails[stockLocate] = security;
    return true;
}

bool BookBuilder::addOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, Order& order)
{
    if (securityDetails.find(stockLocate) == securityDetails.end())
    {
        return false;
    }
    orders[orderReferenceNumber] = order;
    orderBooks[stockLocate].addOrder(order);
    return true;
}

bool BookBuilder::executeOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t executedShares)
{
    if (orders.find(orderReferenceNumber) == orders.end())
    {
        return false;
    }

    orderBooks[stockLocate].executeOrder(orders[orderReferenceNumber].buySellIndicator,
        orders[orderReferenceNumber].price, executedShares);

    if (orders[orderReferenceNumber].numberOfShares <= executedShares)
    {
        orders.erase(orderReferenceNumber);
    }
    else 
    {
        orders[orderReferenceNumber].numberOfShares -= executedShares;
    }
    return true;
}

bool BookBuilder::cancelOrder(uint16_t stockLocate, uint64_t orderReferenceNumber, uint32_t cancelledShares)
{
    if (orders.find(orderReferenceNumber) == orders.end())
    {
        return false;
    }

    orderBooks[stockLocate].cancelOrder(orders[orderReferenceNumber].buySellIndicator, orders[orderReferenceNumber].price, cancelledShares);
    orders[orderReferenceNumber].numberOfShares -= cancelledShares;
    return true;
}

bool BookBuilder::deleteOrder(uint16_t stockLocate, uint64_t orderReferenceNumber)
{
    if (orders.find(orderReferenceNumber) == orders.end())
    {
        return false;
    }

    orderBooks[stockLocate].deleteOrder(orders[orderReferenceNumber].buySellIndicator, orders[orderReferenceNumber].price);
    orders.erase(orderReferenceNumber);
    return true;
}

Order BookBuilder::getOrder(uint64_t orderReferenceNumber)
{
    return orders[orderReferenceNumber];
}

std::ostream& BookBuilder::printOrderBook(std::ostream& output)
{
    for (auto& security : securityDetails)
    {
        output << security.second.name << ":\n";
        auto buyIterator = orderBooks[security.first].buyBook.begin();
        auto sellIterator = orderBooks[security.first].sellBook.begin();
        while (buyIterator != orderBooks[security.first].buyBook.end() && sellIterator != orderBooks[security.first].sellBook.end())
        {
            output << buyIterator->first << ": " << buyIterator->second << "\t" << sellIterator->first << ": " << sellIterator->second << "\n";
            buyIterator++;
            sellIterator++;
        }
        while (buyIterator != orderBooks[security.first].buyBook.end())
        {
            output << buyIterator->first << ": " << buyIterator->second << "\n";
            buyIterator++;
        }
        while (sellIterator != orderBooks[security.first].sellBook.end())
        {
            output << "\t\t\t" << sellIterator->first << ": " << sellIterator->second << "\n";
            sellIterator++;
        }
    }

    return output;
}
