struct DlmsRecord {
    std::string obis;
    std::string value;   // všechno jako text (ANSI)
};

std::string obisToString(const uint8_t* data) {
    char buf[32];
    if (data[5] == 0xFF)
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d.%d",
                 data[0], data[1], data[2], data[3], data[4]);
    else
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d.%d.%d",
                 data[0], data[1], data[2], data[3], data[4], data[5]);
    return std::string(buf);
}

std::vector<DlmsRecord> parseDlmsResponse(const uint8_t* buf, size_t len) {
    std::vector<DlmsRecord> records;
    size_t i = 0;

    // najít první "0x02 0x02"
    while (i + 1 < len && !(buf[i] == 0x02 && buf[i+1] == 0x02)) i++;

    while (i + 10 < len) {
        if (buf[i] != 0x02 || buf[i+1] != 0x02) {
            i++;
            continue;
        }
        i += 2;

        // class-id (2 byty)
        if (i + 2 > len) break;
        i += 2; // classId nepotřebujeme

        // OBIS (6 bytů)
        if (i + 6 > len) break;
        std::string obis = obisToString(&buf[i]);
        i += 6;

        // type + length
        if (i + 2 > len) break;
        uint8_t typeTag = buf[i++];
        uint8_t datalen = buf[i++];
        if (i + datalen > len) break;

        std::string val;
        if (typeTag == 0x09) {
            // visible-string (text)
            val.assign((const char*)&buf[i], (size_t)datalen);
            i += datalen;
        } else {
            // číslo (big-endian) → string ANSI
            uint64_t num = 0;
            for (int j = 0; j < datalen; j++) {
                num = (num << 8) | buf[i++];
            }
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long)num);
            val = tmp;
        }

        records.push_back({ obis, val });
    }

    return records;
}
