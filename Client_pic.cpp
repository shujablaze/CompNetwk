#include <iostream>
#include <winsock2.h>
#include <fstream>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

int main()
{
    WSADATA wsconfig;
    SOCKET connection_socket;
    
    char buff[4096] = {0};
    int bufflen = 4096;
    
    struct sockaddr_in servaddr;
    
    if(WSAStartup(MAKEWORD(2,2),&wsconfig) != 0)
    {
        cout << "Couldnt start WSA" << endl;
        return -1;
    }
    
    connection_socket = socket(AF_INET,SOCK_STREAM,0);
    
    if(connection_socket == INVALID_SOCKET)
    {
        cout << "Couldnt create the socket" << endl;
        return -1;
    }
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    if(connect(connection_socket,(sockaddr *)&servaddr,sizeof(servaddr)) == SOCKET_ERROR)
    {
        cout << "Error Connecting to server!!" << endl;
        return -1;
    }
    bool connected = true;
    cout << "Connected to server" << endl;
    
    
    int choice;
    //Stream to read file
    ifstream in;
        //Stream to write file
    ofstream out;
    while(connected){
        
        cout << "--------File Transfer Client--------" << endl;
        cout << "1.Send File\n2.Request File\n3.Clear Screen\n4.End connection" << endl;
        cout << "Your Choice: ";
        cin >> choice;
        
        //FIle name
        string file_name;
        switch(choice){
            
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
                    ///Opening binary file
                    cout << buff << endl;
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
                out.close();
                ZeroMemory(buff,bufflen);
                break;
                
            case 3:
                system("cls");
                break;
                
            case 4:
                connected = false;
                cout << "\nShutting Down..." ;
   
                // Closing socket and cleaning dll
                closesocket(connection_socket);
                WSACleanup();
                exit(0);
                
            default:
                cout << "Invalid Choice" << endl;
                
        }

    }

    return 0;
}