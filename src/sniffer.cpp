#include <csignal>
#include "../libs/defines.h"
#include <iostream>
#include <linux/if_packet.h>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>

int sniff(){
    int socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    struct sockaddr_ll sniffaddr;
    socklen_t addrlen = sizeof(sniffaddr); 
    if (socketfd < 0){
        std::cerr << "error: failed to open Socket, USAGE: sudo ./net\n";
        return 1;
    }
    std::ofstream file("logs.txt", std::ios::app);

    if(!file){
        std::cerr <<"Failed to create logs.pcap"<< std::endl;
        return 1;
    }

    char buffer[2048];
    while (true) {
        int sockfd = recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sniffaddr, &addrlen);
        if(sockfd < 0){
            std::cerr << "error: failed to read socket "<< std::endl;
            return 1;
        }
        
        file << "the dest Ip address is: " << inet_ntoa(*(struct in_addr *)&buffer[30]) <<  std::endl;
        switch(buffer[23]){
            case TCP:
                file << "service is TCP\n";
                break;
            case UDP:
                file << "service is UDP\n";
                break;
            case ICMP:
                file << "service is ICMP\n";
                break;
            case GRE:
                file << "service is GRE\n";
                break;
            case IGMP:
                file << "service is IGMP\n";
                break;
            case ESP:
                file << "service is ESP\n";
                break;
            case OSPF:
                file << "service is OSPF\n";
                break;
            default:
                file << "unlisted service\n";
                return 1;
            
        }
    }

    return 0;
}

int main(){
    std::signal(SIGINT, [](int sig){exit(0);});
    sniff();
    return 0;
}
