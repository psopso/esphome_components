#include <map>
#include <string>
#include <sstream>
#include <iomanip>

/// Pomocná funkce: převede OBIS kód na "A-B:C.D.E.F"
std::string format_obis(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f) {
    std::ostringstream ss;
    ss << (int)a << "-" << (int)b << ":" << (int)c << "." << (int)d << "." << (int)e << "." << (int)f;
    return ss.str();
}

/// Pomocná funkce: převod byte pole na hex string
std::string bytes_to_hex(const uint8_t *data, size_t len) {
    std::ostringstream ss;
    for (size_t i = 0; i < len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}

/// Dekodér DLMS rámce
std::map<std::string, std::string> parse_dlms(const uint8_t *buf, size_t len) {
    std::map<std::string, std::string> result;

    for (size_t i = 0; i + 6 < len; i++) {
        // hledej OBIS (xx xx xx xx xx xx 0xFF)
        if (i + 7 < len && buf[i+6] == 0xFF) {
            std::string obis = format_obis(buf[i], buf[i+1], buf[i+2], buf[i+3], buf[i+4], buf[i+5]);

            size_t p = i + 7;
            if (p + 1 >= len) continue;

            uint8_t dtype = buf[p+1];  // typ dat
            size_t pos = p+2;
            std::string value;

            switch (dtype) {
                case 0x09: { // Octet string (text)
                    if (pos >= len) break;
                    uint8_t slen = buf[pos++];
                    if (pos + slen <= len) {
                        value.assign((const char*)(buf + pos), slen);
                        pos += slen;
                    }
                    break;
                }
                case 0x06: { // Double-long (32bit int)
                    if (pos + 4 <= len) {
                        int32_t v = (buf[pos]<<24) | (buf[pos+1]<<16) | (buf[pos+2]<<8) | buf[pos+3];
                        value = std::to_string(v);
                        pos += 4;
                    }
                    break;
                }
                case 0x12: { // Long unsigned (16bit)
                    if (pos + 2 <= len) {
                        uint16_t v = (buf[pos]<<8) | buf[pos+1];
                        value = std::to_string(v);
                        pos += 2;
                    }
                    break;
                }
                case 0x10: { // Unsigned (8bit)
                    if (pos < len) {
                        uint8_t v = buf[pos];
                        value = std::to_string(v);
                        pos++;
                    }
                    break;
                }
                case 0x0A: { // Octet string (čas/datum)
                    if (pos >= len) break;
                    uint8_t slen = buf[pos++];
                    if (pos + slen <= len) {
                        // prozatím hex string, později možno rozparsovat na datum
                        value = bytes_to_hex(buf+pos, slen);
                        pos += slen;
                    }
                    break;
                }
                default: {
                    // fallback: hex string
                    if (pos < len) {
                        value = "0x" + bytes_to_hex(buf+pos, 1);
                        pos++;
                    }
                    break;
                }
            }

            if (!value.empty()) {
                result[obis] = value;
            }
        }
    }

    return result;
}
