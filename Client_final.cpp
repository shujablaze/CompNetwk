#include <iostream>
#include <winsock2.h>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    WSADATA wsconfig;
    SOCKET client;
    
    char buf[4096] = {0};
    int buflen = 4096;
    
    struct sockaddr_in servaddr;
    
    // Setting stubs for Winsock2 library
    if(WSAStartup(MAKEWORD(2,2),&wsconfig) != 0)
    {
        cout << "Couldnt start WSA" << endl;
        return -1;
    }
    
    // Creating a socket to connect to server //AF_INET -> IPV4  SOCK_STREAM -> TCP  0 -> default(IP)
    client = socket(AF_INET,SOCK_STREAM,0);
    
    if(client == INVALID_SOCKET)
    {
        cout << "Couldnt create the socket" << endl;
        return -1;
    }
    
    // Setting up the address structure config
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    servaddr.sin_port = htons(PORT);
    
    // Connecting to server
    if(connect(client,(sockaddr *)&servaddr,sizeof(servaddr)) == SOCKET_ERROR)
    {
        cout << "Error Connecting to server!!" << endl;
        return -1;
    }
    
    bool connected = true;
    cout << "Connected to server" << endl;
    
    while(connected)
    {
        int oneCount = 0;
        int zeroCount = 0;
        
        // Length will have no. of characters received
        int length = recv(client,buf,buflen,0);// 0 -> default flag

        cout <<"Server: " << buf << endl;
        
        // Counting number of 1 and 0 received 
        for(int i=0;i<length;++i){
            if(buf[i]=='0') zeroCount++;
            else if(buf[i]=='1') oneCount++;
        }
        
        cout << "Recieved " << oneCount << " ones and " << zeroCount << " zeros." << endl;
        
        cout << "\n\t\tClient : ";
        gets(buf);
        
        // Sending user response to server
        send(client,buf,buflen,0); // 0 -> default flag
        
        if(!strcmp(buf,"quit"))
        {
            connected = false;
            break;
        }
    }

    // Closing socket
    closesocket(client);
    WSACleanup();
    
    return 0;
}