//Testing
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    WSADATA winsock_config;
    
    SOCKET listening_socket , connection_socket;
    
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
    
    int choice;
        //Stream to read file
        ifstream in;
        //Stream to write file
        ofstream out;
    while(connected){
        
        cout << "--------File Transfer Server--------" << endl;
        cout << "1.Send File\n2.Request File\n3.Clear Screen\n4.End connection" << endl;
        cout << "Your Choice: ";
        cin >> choice;

        string file_name;
        switch(choice){
            ZeroMemory(buff,bufflen);
            case 1:
                ZeroMemory(buff,bufflen);
                cout << "Waiting for file name from client.." << endl;
                if(recv(connection_socket,buff,bufflen,0) == SOCKET_ERROR)
                {
                    cout << "Failure while reading" << endl;
                    return -1;
                }
                
                // If client requested for text file
                if(!strcmp(buff,"text")){
                    ZeroMemory(buff,bufflen);
                    recv(connection_socket,buff,bufflen,0);
                    //Opening text file 
                    in.open(buff);
                }
                else if(!strcmp(buff,"img")){
                    ZeroMemory(buff,bufflen);
                    recv(connection_socket,buff,bufflen,0);
                    cout << buff << endl;
                    ///Opening binary file
                    in.open(buff,ios::binary);
                }
                // Helper variable
                char *memblock;
                int char_read; // To keep count of characters read from file
        
                if(in.is_open())
                {   //Sending till file is not completely read
                    while(in)
                    {   //Memory buffer to read file in chunks of 4KB
                        memblock = new char[bufflen];
                        //Reading 4KB chunks of file
                        in.read(memblock,bufflen);
                        //Sending 4Kb of file
                        send(connection_socket,memblock,in.gcount(),0);
                        //Deallocating memory buffer
                        delete [] memblock;
                    }
                    //Sending end of file acknowledgment
                    ZeroMemory(buff,bufflen);
                    strcpy(buff,"File Sent");
                    cout << buff << endl;
                    send(connection_socket,buff,bufflen,0);
                    //exit(0);
                    in.close();
                }
                else {
                    ZeroMemory(buff,bufflen);
                    strcpy(buff,"File Doesnt Exists");
                    cout << buff << endl;
                    send(connection_socket,buff,bufflen,0);
                }
                break;
                    
            case 2:
                ZeroMemory(buff,bufflen);
                int type;
                cout << "\n1.Request Image File\n2.Request Text File" << endl;
                cout << "Your choice: ";
                cin >> type;
                
                cout << "Enter file name with extension: ";
                cin >> file_name;
                // Sending header to tell file type
                if(type==1){
                    send(connection_socket,"img",3,0);
                    out.open(file_name.c_str(),ios::binary);
                }
                else{
                    send(connection_socket,"text",4,0);
                    out.open(file_name.c_str());
                }
                //Sending file name
                send(connection_socket,file_name.c_str(),file_name.size(),0);
                
                //RECEIVING FILE FROM SERVER
                int datarec; // To keep track of character received 
                while(1){
                    datarec = recv(connection_socket,buff,bufflen,0);
                    if(!strcmp(buff,"File Doesnt Exists")){
                        cout << "NO SUCH FILE EXISTS" << endl;
                        break;
                    }
                    if(!strcmp(buff,"File Sent")){
                        cout << "FILE RECEIVED" << endl;
                        break;
                    }
                    out.write(buff,datarec);
                    ZeroMemory(buff,bufflen);
                }
                //Closing write stream
                ZeroMemory(buff,bufflen);
                out.close();
                break;
                
            case 3:
                system("cls");
                break;
                
            case 4:
                connected = false;
                cout << "\nServer Shutting Down..." ;
   
                // Closing socket and cleaning dll
                closesocket(connection_socket);
                closesocket(listening_socket);
                WSACleanup();
                exit(0);
                
            default:
                cout << "Invalid Choice" << endl;
                
        }

    }

    return 0;
}