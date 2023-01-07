#include "CAirodump.h"

CAirodump::CAirodump(char* BSSID, int PWR, int SlashSec, int CH ,int MB, char* ENC, char* CIPHER, char* AUTH, char* ESSID)
{
    this->BSSID.append(BSSID);
    this->PWR = PWR;
    this->SlashSec = SlashSec;
    this->CH = CH;
    this->MB = MB;
    this->ENC.append(ENC);
    this->CIPHER.append(CIPHER);
    this->AUTH.append(AUTH);
    this->ESSID.append(ESSID);
}

CAirodump::~CAirodump()
{

}

void CAirodump::updateAiroDetail(int PWR, int SlashSec, int MB)
{
    this->PWR = PWR;
    this->SlashSec = SlashSec;
    this->MB = MB;
}

void CAirodump::updateData(int Data)
{
    this->Data += Data;
}

void CAirodump::updateBeacons()
{
    this->Beacons++;
}