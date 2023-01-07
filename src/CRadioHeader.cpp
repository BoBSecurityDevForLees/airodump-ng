#include "CRadioHeader.h"


C80211RadioHeader::C80211RadioHeader(const u_char* packet)
{
    // version
    memcpy(&this->it_version, &packet[0], 1);
    // pad
    memcpy(&this->it_pad, &packet[1], 1);
    // len
    memcpy(&this->it_len, &packet[2], 2);
    // present
    memcpy(&this->it_present, &packet[4], 4);
    // signal
    memcpy(&this->it_signalPW, &packet[18], 1);
}

C80211RadioHeader::~C80211RadioHeader()
{

}

uint C80211RadioHeader::get80211Length()
{
    return this->it_len;
}

int C80211RadioHeader::getsignalPower()
{
    return this->it_signalPW;
}