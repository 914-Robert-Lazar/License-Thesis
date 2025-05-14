#include <iostream>
#include <zlib.h>
#include <unordered_set>
#include <fstream>
#include "BookBuildingMessageHandler.h"
#include "Parser.h"
#include <chrono>

static uint16_t readBigEndianUint16(gzFile file) {
    uint16_t length;
    if (gzread(file, &length, sizeof(length)) <= 0) return 0;
    return _byteswap_ushort(length);
}

static bool decodeTCHFile(const bool toBuildOrderBook, const std::string& filename, const uint32_t numberOfOrderRelatedMessagesToBeExecuted) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Error opening file" << filename << std::endl;
    }

    std::unordered_map<char, uint64_t> messageTypes;
    std::unique_ptr<MessageHandler> messageHandler;
    BookBuilder bookBuilder = BookBuilder();

    if (toBuildOrderBook) {
        messageHandler = std::make_unique<BookBuildingMessageHandler>(bookBuilder);
    }
    else {
        messageHandler = std::make_unique<Parser>();
    }

    const auto start{ std::chrono::steady_clock::now() };
    while (true) {
        uint16_t messageLength = readBigEndianUint16(file);
        if (messageLength == 0 || 
            (numberOfOrderRelatedMessagesToBeExecuted > 0 && messageHandler->orderRelatedMessageCounter >= numberOfOrderRelatedMessagesToBeExecuted)) {
            break;
        }

        std::vector<char> message(messageLength);
        if (gzread(file, message.data(), messageLength) != messageLength) break;
        messageHandler->HandleMessage(message);
    }

    const auto finish{ std::chrono::steady_clock::now() };
    const std::chrono::duration<double> elapsed_seconds{ finish - start };

    gzclose(file);

    std::cout << elapsed_seconds.count();
    if (toBuildOrderBook)
    {
        std::ofstream out("orderBook.txt");
        bookBuilder.printOrderBook(out);

        out.close();
    }
    return true;
}

static bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage " << argv[0] << " <parse or build> <binary_itch_file.gz> [<number of order related messages to be executed>]" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    bool toBuildOrderBook = type == "build" ? true : false;
    std::string filename = argv[2];

    uint32_t numberOfOrderRelatedMessagesToBeExecuted = argc > 3 && isNumber(argv[3]) ? std::stoi(argv[3]) : 0;
    return decodeTCHFile(toBuildOrderBook, filename, numberOfOrderRelatedMessagesToBeExecuted) ? 0 : 1;
}