#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <vector>

#define BUFFLEN 4096
#define PORT 8080

#define JOIN_ROOM_1 1
#define JOIN_ROOM_2 2
#define SEND_MESSAGE_ROOM_1 3
#define SEND_MESSAGE_ROOM_2 4
#define EXIT_ROOM_1 5
#define EXIT_ROOM_2 6

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
    
    vector<SOCKET> room1_clients;
    vector<SOCKET> room2_clients;
    
    FD_ZERO(&clients);
    
    FD_SET(listening_socket,&clients);
    
    while(true)
    {
        try{
        fd_set clients_copy = clients;
        memset(&buff,0,bufflen);
        int clientCount = select(0,&clients_copy,nullptr,nullptr,nullptr);
        
        for(int i = 0 ; i < clientCount; ++i ){
            
            SOCKET socket = clients_copy.fd_array[i];
            
            // accept connection
            if(socket == listening_socket)
            {
                connection_socket = accept(listening_socket,(sockaddr *)&client_addr,&addrlen);
                FD_SET(connection_socket,&clients);
                cout << "Client " << to_string(connection_socket) << " Joined" << endl;
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
                    // Header matches for broadcast
                    if(buff[0] == '0'){
                        cout << "Received Broadcast request from client " << to_string(socket) << endl;
                        for(int i = 0 ; i < clients.fd_count ; ++i){
                        SOCKET outgoing = clients.fd_array[i];
    
                            if(outgoing != listening_socket && outgoing != socket)
                            {
                                string buffer = string(buff);
                                // Removing headers
                                buffer[0] = ':';
                                buffer[1] = ' ';
                                string final_buff = "(Broadcast) Client " + to_string(socket) + buffer;
                                send(outgoing,final_buff.c_str(),bufflen,0);
                            }
                        }
                    }
                    
                    else if(buff[0] == '1'){
                        cout << "Received Multicast related request from client "; 
                        cout << to_string(socket) << endl;    
                        string message = "";
                        switch(buff[1] - '0'){
                        case JOIN_ROOM_1:
                            room1_clients.push_back(socket);
                            message = "#Joined room 1";
                            break;
                            
                        case JOIN_ROOM_2:
                            room2_clients.push_back(socket);
                            message = "#Joined room 2";
                            break;
                            
                        case SEND_MESSAGE_ROOM_1:
                            for(int i = 0; i < room1_clients.size() ; ++i){
                                if(room1_clients[i] != socket){
                                    string buffer = string(buff);
                                    // Removing headers
                                    buffer[0] = ':';
                                    buffer[1] = ' ';
                                    string final_buff = "(Room 1) Client " + to_string(socket) + buffer;
                                    send(room1_clients[i],final_buff.c_str(),bufflen,0);
                                }
                            }
                            break;
                            
                        case SEND_MESSAGE_ROOM_2:
                            for(int i = 0; i < room2_clients.size() ; ++i){
                                if(room2_clients[i] != socket){
                                    string buffer = string(buff);
                                    // Removing headers
                                    buffer[0] = ':';
                                    buffer[1] = ' ';
                                    string final_buff = "(Room 2) Client " + to_string(socket) + buffer;
                                    send(room2_clients[i],final_buff.c_str(),bufflen,0);
                                }
                            }
                            break;
                            
                        case EXIT_ROOM_1:
                            for(int i = 0; i < room1_clients.size() ; ++i){
                                if(room1_clients[i] == socket){
                                    room1_clients.erase(room1_clients.begin() + i);
                                }
                            }
                            message = "#Left room 1";
                            break;
                            
                        case EXIT_ROOM_2:
                            for(int i = 0; i < room2_clients.size() ; ++i){
                                if(room2_clients[i] == socket){
                                    room2_clients.erase(room2_clients.begin() + i);
                                }
                            }
                            message = "#Left room 1";
                            break;
                        }
                        if(message.size() > 0){
                            send(socket,message.c_str(),message.size(),0);
                        }
                    }
                    
                }
            }
        }
        
        }catch(exception){
            cout << "Error while sending" << endl;
        }
    }
    
    cout << "\nServer Shutting Down..." ;
   
    // Closing socket and cleaning dll
    closesocket(connection_socket);
    closesocket(listening_socket);
    WSACleanup();
    
    return 0;
}