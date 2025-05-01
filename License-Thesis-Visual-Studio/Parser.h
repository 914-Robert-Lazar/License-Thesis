#pragma once
#include "MessageHandler.h"

class Parser : public MessageHandler
{
	void HandleSystemEventMessage(std::vector<char>& message);
	void HandleStockDirectoryMessage(std::vector<char>& message) override;
	void HandleStockTradingActionMessage(std::vector<char>& message);
	void HandleRegSHORestrictionMessage(std::vector<char>& message);
	void HandleMarketParticipantPositionMessage(std::vector<char>& message);
	void HandleMWCBDeclineLevelMessage(std::vector<char>& message);
	void HandleMWCBStatusMessage(std::vector<char>& message);
	void HandleQuotingPeriodUpdateMessage(std::vector<char>& message);
	void HandleLimitUpDownAuctionCollarMessage(std::vector<char>& message);
	void HandleOperationalHaltMessage(std::vector<char>& message);
	void HandleAddOrderMessage(std::vector<char>& message) override;
	void HandleAddOrderWithMPIDMessage(std::vector<char>& message) override;
	void HandleAddOrderExecutedMessage(std::vector<char>& message) override;
	void HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message) override;
	void HandleOrderCancelMessage(std::vector<char>& message) override;
	void HandleOrderDeleteMessage(std::vector<char>& message) override;
	void HandleOrderReplaceMessage(std::vector<char>& message) override;
	void HandleTradeMessage(std::vector<char>& message);
	void HandleCrossTradeMessage(std::vector<char>& message);
	void HandleBrokenTradeMessage(std::vector<char>& message);
	void HandleNetOrderImbalanceIndicatorMessage(std::vector<char>& message);
	void HandleRetailInterestMessage(std::vector<char>& message);
	void HandleDirectListingWithCapitalRaiseMessage(std::vector<char>& message);
};

