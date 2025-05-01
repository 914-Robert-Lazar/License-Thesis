#pragma once
#include "MessageHandler.h"

class BookBuildingMessageHandler : public MessageHandler
{
	BookBuilder& bookBuilder;

	void HandleStockDirectoryMessage(std::vector<char>& message) override;
	void HandleAddOrderMessage(std::vector<char>& message) override;
	void HandleAddOrderWithMPIDMessage(std::vector<char>& message) override;
	void HandleAddOrderExecutedMessage(std::vector<char>& message) override;
	void HandleAddOrderExecutedWithPriceMessage(std::vector<char>& message) override;
	void HandleOrderCancelMessage(std::vector<char>& message) override;
	void HandleOrderDeleteMessage(std::vector<char>& message) override;
	void HandleOrderReplaceMessage(std::vector<char>& message) override;

public:
	BookBuildingMessageHandler(BookBuilder& bookBuilder) : bookBuilder(bookBuilder), MessageHandler() {}
};

