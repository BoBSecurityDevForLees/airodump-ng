#include <iostream>

class C80211RadioHeader
{
private:
    uint8_t it_version;
    uint8_t it_pad;
    uint16_t it_len;
    uint32_t it_present;

public:
    C80211RadioHeader();
    ~C80211RadioHeader();

    uint get80211Length();
};