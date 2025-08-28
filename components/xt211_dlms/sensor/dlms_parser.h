#include <string>
#include <vector>

struct DlmsRecord {
    std::string obis;
    std::string value;   // všechno jako text (ANSI)
};

std::vector<DlmsRecord> parseDlmsResponse(const uint8_t* buf, size_t len);
