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
    
    if(WSAStartup(MAKEWORD(2,2),&wsconfig) != 0)
    {
        cout << "Couldnt start WSA" << endl;
        return -1;
    }
    
    client = socket(AF_INET,SOCK_STREAM,0);
    
    if(client == INVALID_SOCKET)
    {
        cout << "Couldnt create the socket" << endl;
        return -1;
    }
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    if(connect(client,(sockaddr *)&servaddr,sizeof(servaddr)) == SOCKET_ERROR)
    {
        cout << "Error Connecting to server!!" << endl;
        return -1;
    }
    bool connected = true;
    cout << "Connected to server" << endl;
    
    while(connected)
    {
        cout << "\n\t\tShuja : ";
        gets(buf);
        
        send(client,buf,buflen,0);
        
        if(!strcmp(buf,"quit"))
        {
            connected = false;
            break;
        }
    
        recv(client,buf,buflen,0);

        cout <<"Server: " << buf << endl;
    }
    
    closesocket(client);
}