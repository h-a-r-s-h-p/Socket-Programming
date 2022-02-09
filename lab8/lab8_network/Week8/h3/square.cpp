#include<bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define UDP_PORT    8567                             // port h3 listening on

#define MAX 1024
  
// Driver code

int main(){
    // UDP socket creation

    int sockfd;
    struct sockaddr_in servaddr, clieaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {      // creating socket 
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }



    memset(&servaddr, 0, sizeof(servaddr));
    memset(&clieaddr,0, sizeof(clieaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(UDP_PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    while(1){
        char buff[MAX];                                     // stores the char array from h2
        socklen_t clientlen=sizeof(clieaddr);
        // cout<<"check1\n";
        int n=recvfrom(sockfd,(char *) buff, MAX, MSG_WAITALL, (struct sockaddr*)&clieaddr, &clientlen);
        buff[n]='\0';
        string buffStr=buff;
        cout<<"buffStr= "<<buffStr<<endl;                  // printing the received array
        string temp="";                                    // stores the integer to be squared
        int i=0;
        while(buff[i]!=' ') temp+=buffStr[i++];
        int num_received=stoi(temp);
        cout<<"num_received "<<num_received<<endl;
        int result=num_received*num_received;

        
        string result_str = to_string(result);              // converting the result to string
        char result_to_send_to_h1[MAX];                     // this would be sent to h1 via TCP socket and will contain the squared value
        for(int i=0;i<result_str.size();i++) result_to_send_to_h1[i]=result_str[i];
        result_to_send_to_h1[result_str.size()]='\0';

        
        char h1_IP_address[12];                             // ID address is of h1
        h1_IP_address[11]='\0';
        string port_string="";                              // port number h1 is listening on
        int h1_port;
        i++;                                                // i was pointing on space, so increased by 1
        int j=0;
        while (buff[i]!=' ')                                // IP address is until another space
        {
            /* code */
            h1_IP_address[j++]=buff[i++];
        }
        
        i++;
        while (buff[i]!='\0')                               // port number is untill the string does not terminate
        {
            /* code */
            port_string+=buff[i++];
        }
        
        string h1_IPaddr= h1_IP_address;
        cout<<"IP add= "<<h1_IPaddr<<endl;
        cout<<"Port in h3= "<<port_string<<endl;
        h1_port=stoi(port_string);
        
        
        
        //TCP connection with h1
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char buffer[MAX] = {0};
        sock=socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }     
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(h1_port);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, h1_IP_address, &serv_addr.sin_addr)<=0) 
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        write(sock, result_to_send_to_h1, sizeof(result_to_send_to_h1));
    }
    return 0;
}