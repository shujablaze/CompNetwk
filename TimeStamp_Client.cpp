#include <iostream>
#include <winsock2.h>
#include <thread>


#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    WSADATA wsconfig;
    SOCKET client;
    
    char buf[4096] = {0};
    int buflen = 4096;
    
    //Struct used for address related info
    struct sockaddr_in servaddr;
    //Initializing winsock dll
    if(WSAStartup(MAKEWORD(2,2),&wsconfig) != 0)
    {
        cout << "Couldnt start WSA" << endl;
        return -1;
    }
    
    //Creating socket for client
    client = socket(AF_INET,SOCK_STREAM,0);
    
    if(client == INVALID_SOCKET)
    {
        cout << "Couldnt create the socket" << endl;
        return -1;
    }
    
    //Setting up server info struct
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    //Connecting to server
    if(connect(client,(sockaddr *)&servaddr,sizeof(servaddr)) == SOCKET_ERROR)
    {
        cout << "Error Connecting to server!!" << endl;
        return -1;
    }
    
    //Time at which connection was granted
    time_t connection_ts = std::time(nullptr);
    cout <<"Connected to server at "<<std::asctime(std::localtime(&connection_ts)) << endl;
    
    bool connected = true;
    
    while(connected)
    {
        cout << "\n\t\tClient : ";
        gets(buf);
        
        send(client,buf,buflen,0);
        //Timestamp at which client sent data to server
        time_t sending_ts = std::time(nullptr);
        
        cout <<"\n\t\t   " <<std::asctime(std::localtime(&sending_ts)) << endl;
        
        if(!strcmp(buf,"quit"))
        {
            connected = false;
            break;
        }
    
        recv(client,buf,buflen,0);
        //Time at which data was received
        time_t receiving_ts = std::time(nullptr);

        cout <<"Server: " << buf << endl;
        cout <<"   " <<std::asctime(std::localtime(&receiving_ts)) << endl;
    }
    
    closesocket(client);
}