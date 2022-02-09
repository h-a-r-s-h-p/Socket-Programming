#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <linux/if_packet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

using namespace std;

int main()
{

	struct sockaddr_in source_addr, dest_addr;

	int packet_size;
	unsigned char *buffer = (unsigned char *)malloc(65536);


	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1)
	{
		perror("Failed to create socket");
		exit(1);
	}

	while (1)
	{
		packet_size = recvfrom(sock, buffer, 65536, 0, NULL, NULL);

		struct ether_header *eth = (struct ether_header *)buffer;
		cout << "Source MAC address= ";

        for(int i=0;i<6;i++){
            char hexa_string[20];
            sprintf(hexa_string, "%X", (unsigned)eth->ether_shost[i]); //convert number to hex
            cout<<hexa_string<<":";
        }
		cout<<endl;
		cout << "Destination MAC address= ";

        for(int i=0;i<6;i++){
            char hexa_string[20];
            sprintf(hexa_string, "%X", (unsigned)eth->ether_dhost[i]); //convert number to hex
            cout<<hexa_string<<":";
        }
		

		struct iphdr *ip_packet = (struct iphdr *)(buffer + sizeof(struct ethhdr));
		memset(&source_addr, 0, sizeof(source_addr));
		source_addr.sin_addr.s_addr = ip_packet->saddr;   
		memset(&dest_addr, 0, sizeof(dest_addr));
		dest_addr.sin_addr.s_addr = ip_packet->daddr;

        cout<<"Source IP Address= "<<(char*)inet_ntoa(source_addr.sin_addr)<<endl;
        cout<<"Destination IP Address= "<<(char*)inet_ntoa(dest_addr.sin_addr)<<endl;
		cout << endl<<endl;
	}

	return 0;
}