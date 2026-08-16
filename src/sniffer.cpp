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

volatile sig_atomic_t running = true;

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
    while (running) {
        int sockfd = recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sniffaddr, &addrlen);
        if(sockfd < 0){
            std::cerr << "error: failed to read socket "<< std::endl;
            return 1;
        }
        uint32_t size_ip = (buffer[14] & 0x0F) * 4;
        uint32_t next_init = 14 + size_ip;

        file << "the source IP address is : " << inet_ntoa(*(struct in_addr *)&buffer[26]) << std::endl;      
        file << "the dest Ip address is: " << inet_ntoa(*(struct in_addr *)&buffer[30]) <<  std::endl;
        
        switch(buffer[23]){
            case TCP:
                file << "service is TCP\n" << "the dest PORT is: " << ntohs(*(uint16_t *)&buffer[next_init + 2]) << "\n" << "the source PORT is " << ntohs(*(uint16_t *)&buffer[next_init]) << "\n";
                
                break;
            case UDP:
                file << "service is UDP\n" << "the dest PORT is: "<<ntohs(*(uint16_t *)&buffer[next_init + 2]) << "\n" << "the source PORT is: " << ntohs(*(uint16_t *)&buffer[next_init]) <<"\n";
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
                file << "unlisted service service number is: " << buffer[23] << "\n" ;
                break;
        }
    }

    return 0;
}

int main(){
    std::signal(SIGINT, [](int sig){running = false;});
    sniff();
    return 0;
}
