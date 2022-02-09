#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<bits/stdc++.h>
#define MAX 1024
#define TCP_PORT 12503
#define UDP_PORT 8567
#define h3addr "192.168.1.4"
#define SA struct sockaddr

using namespace std;


int main(){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( TCP_PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while(1){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen))<0)
        {
            perror("Not accepted");
            exit(EXIT_FAILURE);
        }



    
    
        // UDP connection
        int sockfd2;
        struct sockaddr_in     servaddr2;
    
        // Creating socket file descriptor
        if ( (sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("UDP socket creation failed");
            exit(EXIT_FAILURE);
        }
    
        memset(&servaddr2, 0, sizeof(servaddr2));
        
        // Filling server information
        servaddr2.sin_family = AF_INET;
        servaddr2.sin_port = htons(UDP_PORT);
        servaddr2.sin_addr.s_addr = inet_addr(h3addr);
        
            
        int num1,num2;
        read(new_socket,buffer,sizeof(buffer));
        string buffStr=buffer;
        cout<<"buffStr= "<<buffStr<<endl;
        int i=0;
        string num1str="";
        while(buffer[i]!=' '){
            num1str+=buffer[i++];
        }
        num1=stoi(num1str);
        cout<<"num1= "<<num1<<endl;

        string num2str="";
        i++;
        while(buffer[i]!=' '){
            num2str+=buffer[i++];
        }
        num2=stoi(num2str);
        cout<<"num2= "<<num2<<endl;
        int result= num1/num2;


        // sending as UDP packet to h3
        string temp=to_string(result);
        string tosend="";
        for(int j=0;j<temp.size();j++) tosend+=temp[j];
        tosend+=' ';
        i++;
        while(buffer[i]!='\0'){
            tosend+=buffer[i++];
        }


        // cout<<"tosend= "<<tosend<<endl;
        char buffer2[tosend.length()+1];
        for(int i=0;i<tosend.length();i++) buffer2[i]=tosend[i];
        buffer2[tosend.length()]='\0';
        i=0;
        // while(buffer2[i]!='\0') cout<<buffer2[i++];
        cout<<endl;
        sendto(sockfd2,(const char *) buffer2, strlen(buffer2), MSG_CONFIRM, (const struct sockaddr*)&servaddr2, sizeof(servaddr2));
        cout<<"result = "<<result<<endl;
    }
    // sendto(sockfd2, buff, sizeof(buff), 0, (struct sockaddr* )&servaddr2, sizeof(servaddr2));
    

      
    return 0;
}