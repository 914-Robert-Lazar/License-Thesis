#include <iostream>
#include <zlib.h>
#include <unordered_set>
#include <fstream>
#include "MessageHandler.h"

const std::unordered_set<char> VALID_ITCH_MSG_TYPES = { 'S', 'R', 'H', 'Y', 'L', 'V', 'W', 'K', 'J', 'h', 'A', 'F', 'E', 'C', 'X', 'D', 'U', 'P', 'Q', 'B', 'I', 'O' };

uint16_t readBigEndianUint16(gzFile file) {
    /*uint8_t buffer[2];
    if (gzread(file, buffer, 2) != 2) return 0;
    return (buffer[0] << 8) | buffer[1];*/
    uint16_t length;
    if (gzread(file, &length, sizeof(length)) <= 0) return 0;
    return _byteswap_ushort(length);
}

bool validateITCHFile(const std::string& filename) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Error opening file" << filename << std::endl;
    }

    int totalMessages = 0, validMessages = 0;
    std::unordered_map<char, uint64_t> messageTypes;

    BookBuilder bookBuilder = BookBuilder();
    MessageHandler messageHandler = MessageHandler(bookBuilder);

    while (true) {
        uint16_t messageLength = readBigEndianUint16(file);
        if (messageLength == 0) {
            std::cout << "End of session marker found." << std::endl;
            break;
        }

        std::vector<char> message(messageLength);
        if (gzread(file, message.data(), messageLength) != messageLength) break;

        totalMessages++;

        if (VALID_ITCH_MSG_TYPES.count(message[0])) {
            validMessages++;
            messageTypes[message[0]]++;
        }
        messageHandler.HandleMessage(message);
    }

    gzclose(file);

    if (validMessages > 0) {
        std::cout << "Valid ITCH BinaryFILE: " << validMessages << "/" << totalMessages << " messages recognized." << std::endl;
        std::ofstream out("messageTypes.txt");
        for (auto& messageType : messageTypes) {
            out << messageType.first << ": " << messageType.second << std::endl;
        }
        out.close();
        return true;
    }
    else {
        std::cout << "No valid ITCH messages found." << std::endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage " << argv[0] << " <binary_itch_file.gz>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    return validateITCHFile(filename) ? 0 : 1;
}