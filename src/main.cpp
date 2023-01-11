#include <pcap.h>
#include <map>
#include <ctime>
#include <ncurses.h>
#include "CRadioHeader.h"
#include "CBeaconFrame.h"
#include "CWirelessManagement.h"
#include "CAirodump.h"

void usage()
{
    std::cerr << "syntax : airodump <interface>" << std::endl;
    std::cerr << "sample : airodump mon0" << std::endl;
}

void printErrorInterface(char* strErr)
{
    std::cerr << strErr << std::endl;
    std::cerr << "Check  Interface Or authority" << std::endl;
}

void printAirodump_ng(int CH, std::map<std::string,CAirodump> airodumplist)
{
    move(0,0);
    std::time_t t =std::time(nullptr);
    std::tm* now = std::localtime(&t);

    printw("CH %d\t][ Elapsed: %d s ][ %d-%02d-%02d %d:%d\n", CH, 0, now->tm_year + 1900, now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min);
    printw("\n");
    printw("BSSID\t\t\tPWR\tBecons\t#Data,\t#/s\tCH\tMB\tENC\tCIPHER\tAUTH\tESSID\n");

    for(auto &iter : airodumplist)
    {
        printw("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s\n", iter.first.c_str(), iter.second.PWR, iter.second.Beacons, 
            iter.second.Data, iter.second.SlashSec, iter.second.CH, iter.second.MB, iter.second.ENC.c_str(), 
            iter.second.CIPHER.c_str(), iter.second.AUTH.c_str(), iter.second.ESSID.c_str());
    }
    refresh();
}

int main(int argc, char* argv[])
{
    // 만약 인자로 인터페이스를 제공하지 않았을 경우
    if(argc < 2)
    {
        usage();
        return -1;
    }

    char* interface = argv[1];
    char strErr[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(interface, BUFSIZ, 1, 1, strErr);
    
    // 해당 인터페이스가 없는 경우
    if(handle == nullptr)
    {
        printErrorInterface(strErr);
        return -1;
    }
    
    // Ncurses 객체 초기화
    initscr();

    int CH = 0;
    std::map<std::string, CAirodump> wirelessList;

    // 무한반복을 하며 진행
    while(true)
    {
        struct pcap_pkthdr* header;
        const u_char* packet;

        int res = pcap_next_ex(handle, &header, &packet);
        if(res == 0) continue;
        if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
			break;
		}
        C80211RadioHeader radioHeader = C80211RadioHeader(packet);

        int radioHeaderBackLocation = radioHeader.get80211Length();
        
        char no[5] = "NOPE";
        
        // BeaconFrame인지 확인
        if(packet[radioHeaderBackLocation] == 0x80)
        {
            // BeaconFrame이 맞다면 Beacon정보를 다룰 객체 생성
            C80211BeaconFrame wirelessbeacon = C80211BeaconFrame(&packet[radioHeaderBackLocation]);
            CWirelessManagement wirelessManagement = CWirelessManagement(&packet[radioHeaderBackLocation + 24]);
            CAirodump airoElement = CAirodump(radioHeader.getsignalPower(), 0, wirelessManagement.getChannel(), 
            0, no, no, no, wirelessManagement.getSSID());

            bool checker = false;

            auto loc = wirelessList.find(wirelessbeacon.getBSSID());
            if(loc != wirelessList.end())
            {
                checker = true;
                loc->second.updateAiroDetail(airoElement.PWR, airoElement.SlashSec, airoElement.MB);
                loc->second.updateBeacons();
            }

            if(checker == false)
                wirelessList.insert(std::make_pair(wirelessbeacon.getBSSID(), airoElement));

            CH = wirelessManagement.getChannel();
            printAirodump_ng(CH, wirelessList);
            // std::string iwcommand;
            // iwcommand.append("sudo iwconfig ");
            // iwcommand.append(interface);
            // iwcommand.append(" channel ");
            // iwcommand.append(std::to_string(CH));
            // system(iwcommand.c_str());
        }
        else
            continue;
    }
    getch();
    endwin();
    return 0;
}
