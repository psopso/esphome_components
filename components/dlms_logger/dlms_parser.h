#pragma once

#include <string>
#include <vector>
#include <map>

struct DlmsRecord {
    std::string obis;
    std::string value;   // všechno jako text (ANSI)
};

std::map<std::string, std::string> parse_dlms(const uint8_t *buf, size_t len);