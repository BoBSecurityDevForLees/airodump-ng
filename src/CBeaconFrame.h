#pragma once

#include <iostream>
#include <cstring>

class C80211BeaconFrame
{
private:
    char strDestinationAddress[18];
    char strSourceAddress[18];
    char strBSSID[18];

public:
    C80211BeaconFrame(const u_char* packet);
    ~C80211BeaconFrame();
    char* getDestinationAddress();
    char* getSourceAddress();
    char* getBSSID();
};