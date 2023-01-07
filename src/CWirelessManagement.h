#pragma once

#include <iostream>
#include <cstring>
#include <string>

typedef std::basic_string<wchar_t> wstring;

class CWirelessManagement
{
private:
    char fixedData[12];
    char* strSSID;
    char* strSupportRates;
    int channel;

public:
    CWirelessManagement(const u_char* packet);
    ~CWirelessManagement();

    char* getSSID();
    int getChannel();

};