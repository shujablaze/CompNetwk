#include <iostream>
#include <winsock2.h>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    // Datastructure for stubs of winsock2 config
    WSADATA winsock_config;
    
    SOCKET listening_socket , connection_socket;
    
    // Address structures
    struct sockaddr_in server_addr,client_addr;
    
    int addrlen = sizeof(client_addr);
    int bufflen = BUFFLEN;
    int msglen;
    
    char buff[BUFFLEN] = {0};
    
    
    // Sets up stubs for Ws2_32.dll
    if(WSAStartup(MAKEWORD(2,2),&winsock_config) != 0)
    {
        cout << "Couldnt link Ws2_32.lib dll" <<endl;
        return -1;
    }
    

    // Creating a socket to listen to requests //AF_INET -> IPV4  SOCK_STREAM -> TCP  0 -> default(IP)
    listening_socket = socket(AF_INET,SOCK_STREAM,0);

    if(listening_socket == INVALID_SOCKET){
        cout << "Could not create the listening socket" <<endl;
        return -1;
    }

    // Setting up the address structure config
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Assigning localhost as address
    server_addr.sin_port = htons( PORT );
    
    // Binding host and port to the created socket
    if( bind(listening_socket,(sockaddr *)&server_addr,sizeof(server_addr) ) != 0)
    {
        cout << "Could not bind the listening socket" <<endl;
        return -1;
    }
    
    // Listening for requests
    if(listen(listening_socket,5) < 0)
    {
        cout << "Failure while listen call" << endl;
        return -1;
    }
    cout << "---------------SERVER---------------" << endl;
    cout << "Listening to requests.....\n" <<endl;
    
    // Creates a new socket to carry out conversation with client while old socket is free for listening 
    connection_socket = accept(listening_socket,(sockaddr *)&client_addr,&addrlen);
    
    
    if(connection_socket == INVALID_SOCKET)
    {
        cout << "Failed to accept client socket connection" << endl;
        return -1;
    }
    
    // No need for listening socket if we only have one client here.
    // closesocket(listening_socket);
    bool connected = true;
    bool flag = false;
    
    while(connected){
        // Dialogue Box 
        
        cout << "\n\t\tServer :  ";
        gets(buff);
        
        // Checking if string entered has 1s and 0s only
        for(int i=0;i<strlen(buff);++i){
            if(buff[i]!='0' && buff[i]!='1'){
                flag = true;
            }
        }
        
        if(flag){
            cout << "Only binary strings are allowed try again..." << endl;
            flag = false;
            continue;
        }
        
        // Sending data in buffer
        send(connection_socket,buff,bufflen,0);
        
        // Storing data in buffer
        if(recv(connection_socket,buff,bufflen,0) == SOCKET_ERROR)
        {
            cout << "Failure while reading" << endl;
            return -1;
        }
        
        // Checking if client want to leave
        if(!strcmp(buff,"quit"))
        {
            connected = false;
            break;
        }
        
        cout << "Client :  " << buff << endl;
    }
    
    cout << "\nServer Shutting Down..." ;
   
    // Closing socket and cleaning dll
    closesocket(connection_socket);
    closesocket(listening_socket);
    WSACleanup();
    
    return 0;
}