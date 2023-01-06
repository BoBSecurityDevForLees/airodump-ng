#include <pcap.h>
#include <string>
#include <iostream>

void usage()
{
    std::cerr << "syntax : airodump <interface>" << std::endl;
    std::cerr << "sample : airodump mon0" << std::endl;
}

void printErrorInterface(char* interface)
{
    std::cerr << interface << " can't access" << std::endl;
    std::cerr << "Check input InterFace" << std::endl;
}

int main(int argc, char* argv[])
{
    // 만약 인자로 인터페이스를 제공하지 않았을 경우
    if(argc > 2)
        usage();

    char* interface;
    char strErr[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(interface, BUFSIZ, 1, 1, strErr);
    
    // 해당 인터페이스가 없는 경우
    if(handle == nullptr)
        printErrorInterface(interface);

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

        

    }

    return 0;
}