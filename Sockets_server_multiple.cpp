#include <iostream>
#include <winsock2.h>
#include <cstring>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    WSADATA winsock_config;
    
    SOCKET listening_socket , connection_socket;
    
    struct sockaddr_in server_addr , client_addr;
    
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
    

    // Creating a socket to listen to requests //AF_INET->IPV4  SOCK_STREAM->TCP  0->default(IP)
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
    
    fd_set clients;
    FD_ZERO(&clients);
    
    FD_SET(listening_socket,&clients);
    
    while(true)
    {
        fd_set clients_copy = clients;
        
        int clientCount = select(0,&clients_copy,nullptr,nullptr,nullptr);
        
        for(int i = 0 ; i < clientCount; ++i ){
            
            SOCKET socket = clients_copy.fd_array[i];
            
            // accept connection
            if(socket == listening_socket)
            {
                connection_socket = accept(listening_socket,(sockaddr *)&client_addr,&addrlen);
                FD_SET(connection_socket,&clients);
                
                char welcome[] = "\nWelcome to the chatroom\n";
                send(connection_socket,welcome,sizeof(welcome),0);
            }
            else
            {
                if(recv(socket,buff,bufflen,0) == SOCKET_ERROR)
                {
                    cout << "Failure while reading" << endl;
                    return -1;
                }
                if(!strcmp(buff,"quit"))
                {
                    // Close and remove socket
                    closesocket(socket);
                    FD_CLR(socket,&clients);
                }
                else
                {
                    for(int i = 0 ; i < clients.fd_count ; ++i){
                        SOCKET outgoing = clients.fd_array[i];
    
                        if(outgoing != listening_socket && outgoing != socket)
                        {
                            string final_buff = "Client " + to_string(i) + " " + buff;
                            send(outgoing,final_buff.c_str(),bufflen,0);
                        }
                    }
                }
            }
        }
    }
    
    
    
    cout << "\nServer Shutting Down..." ;
   
    // Closing socket and cleaning dll
    closesocket(connection_socket);
    closesocket(listening_socket);
    WSACleanup();
    
    return 0;
}