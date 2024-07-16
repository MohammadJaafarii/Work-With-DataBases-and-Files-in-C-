#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <regex>
#include <cstdint>

class Validation
{
public:
    Validation();
    static bool isValidIP(const uint32_t& ip);
};

#endif // VALIDATION_H
