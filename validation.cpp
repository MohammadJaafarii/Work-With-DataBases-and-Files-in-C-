#include "validation.h"

Validation::Validation() {}

bool Validation::isValidIP(const uint32_t& ip) {

    if (ip == 0x0A000001 || ip == 0xFFFFFFFF) return false;

    // Convert the uint32_t IP to a string in the form of "xxx.xxx.xxx.xxx"
    std::string ipStr;
    for (int i = 0; i < 4; ++i) {
        if (i > 0) ipStr = "." + ipStr;
        ipStr = std::to_string((ip >> (8 * (3 - i))) & 0xFF) + ipStr;
    }

    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");
    if (std::regex_match(ipStr, ipv4))
        return true;
    if (std::regex_match(ipStr, ipv6))
        return true;
    return false;
}
