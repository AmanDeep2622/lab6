#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PACKET_SIZE 4096

using namespace std;

int main() {
    int sockfd, status;
    struct ip *ip_header;
    struct icmphdr *icmp_header;
    char packet_buffer[PACKET_SIZE];

    // Create a RAW socket to capture ICMP packets
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    while (true) {
        int packet_size = recv(sockfd, packet_buffer, PACKET_SIZE, 0);
        if (packet_size < 0) {
            perror("Packet receive failed");
            break;
        }

        ip_header = (struct ip *)packet_buffer;
        icmp_header = (struct icmphdr *)(packet_buffer + (ip_header->ip_hl << 2));

        // Print the length of the IP header of the captured ICMP packet
        int ip_header_length = ip_header->ip_hl << 2;
        cout << "IP Header Length: " << ip_header_length << " bytes" << endl;
    }

    close(sockfd);
    return 0;
}
