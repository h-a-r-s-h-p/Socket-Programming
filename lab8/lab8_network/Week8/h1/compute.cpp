#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<bits/stdc++.h>
#define MAX 1024
#define PORT_ADD 12500
#define PORT_SUB 12501
#define PORT_MUL 12502
#define PORT_IDIV 12503
#define TCP_PORT 9555                          // the listening port for h3, i.e. h3 will send on this port
#define SA struct sockaddr
using namespace std;


int main(int arg, char *argv[]){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX] = {0};
    sock=socket(AF_INET, SOCK_STREAM, 0);     // creating socket
    if (sock < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
       
    int a,b;
    string op;
    a=stoi(argv[1]);
    b=stoi(argv[2]);
    op=argv[3];
    cout<<"op= "<<op<<endl;
    serv_addr.sin_family = AF_INET;
    if(op=="ADD") serv_addr.sin_port = htons(PORT_ADD);            // if operation is ADD, then connecting to PORT_ADD
    else if(op=="SUB") serv_addr.sin_port=htons(PORT_SUB);         // else if it is SUB, then connectinig to PORT_SUB
    else if(op=="MUL") serv_addr.sin_port= htons(PORT_MUL);
    else serv_addr.sin_port=htons(PORT_IDIV);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.1.3", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    // cout<<"numbers in client: "<<a<<" "<<b<<endl;
    string temp=to_string(a)+" "+to_string(b)+" 192.168.1.2 "+ to_string(TCP_PORT);       // it is storing the two operands, IPaddress of h1 and port it is listening on for h3
    for(int i=0;i<temp.size();i++){
        buffer[i]=temp[i];                                                                 // converting the string to char array
    }
    buffer[temp.size()]='\0';
    write(sock, buffer, sizeof(buffer));                                                // sending to h2
    



    //TCP connection with h3
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 9555
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( TCP_PORT );
       
    // Forcefully attaching socket to the port 9555
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
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen))<0)
    {
        perror("Not accepted");
        exit(EXIT_FAILURE);
    }


    read(new_socket,buffer, sizeof(buffer));                                  // reading from h3

    int i=0;
    while(buffer[i]!='\0'){
        cout<<buffer[i++];                                                     // result from h3
    }
    cout<<endl;
    return 0;
}