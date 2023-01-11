#pragma once

#include "CRadioHeader.h"
#include "CBeaconFrame.h"
#include "CWirelessManagement.h"

class CAirodump
{
public:
    int PWR = 0;
    int Beacons = 0;
    int Data = 0;
    int SlashSec = 0;
    int CH = 0;
    int MB = 0;
    std::string ENC;
    std::string CIPHER;
    std::string AUTH;
    std::string ESSID;

    CAirodump(int PWR, int SlashSec, int CH, int MB, char* ENC, char* CIPHER, char* AUTH, char* ESSID);
    ~CAirodump();

    void updateAiroDetail(int PWR, int SlashSec, int MB);
    void updateData(int Data);
    void updateBeacons();
};