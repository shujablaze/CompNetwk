#include <iostream>
#include <winsock2.h>

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

string encrypt_text(string text,string key);
string decrypt_text(string text,string key);

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
    string key,encrypted,decrypted;
    
    while(connected){
        // Storing data in buffer
        if(recv(connection_socket,buff,bufflen,0) == SOCKET_ERROR)
        {
            cout << "Failure while reading" << endl;
            return -1;
        }
        
        // Checking if client want to leave
        if(strlen(buff) == 0)
        {
            connected = false;
            break;
        }
        
        // Dialogue Box 
        cout << "\nClient :  " << buff << endl;
        encrypted = string(buff);
        cout << "Enter decryption key: ";
        cin>>key;
        decrypted = decrypt_text(encrypted,key);
        cout << "Decrypted : " << decrypted << endl;
        
        cout << "\n\t\tServer :  ";
        cin.sync();
        getline(cin,decrypted);
        cout << "\t\tEnter encryption key: ";
        cin >> key;
        encrypted = encrypt_text(decrypted,key);
        
        // Sending data in buffer
        send(connection_socket,encrypted.c_str(),bufflen,0);
    }
    
    cout << "\nServer Shutting Down..." ;
   
    // Closing socket and cleaning dll
    closesocket(connection_socket);
    closesocket(listening_socket);
    WSACleanup();
    
    return 0;
}

string encrypt_text(string text,string key){
    string vigenere_key = key;
    while(vigenere_key.length() < text.length()){
        vigenere_key += key;
    }
    
    key = vigenere_key;
    
    for(int i=0;i<text.length();++i){
        if(text[i] >= 65 && text[i] < 91){
            text[i] = (text[i]  + toupper(key[i]) - 130) % 26 + 65;
        }
        else if(text[i] >= 97 && text[i] < 123){
            text[i] = (text[i] + tolower(key[i]) - 194) % 26 + 97;
        }
    }
    return text;
}

string decrypt_text(string text,string key){
    string vigenere_key = key;
    while(vigenere_key.length() < text.length()){
        vigenere_key += key;
    }
    
    key = vigenere_key;
    
    for(int i=0;i<text.length();++i){
        if(text[i]>=65 && text[i] < 91){
            text[i] = (text[i]  - toupper(key[i])) % 26;
            text[i] = (text[i] < 0)? text[i] + 26 + 65 : text[i] + 65;
        }
        else if(text[i]>=97 && text[i] < 123){
            text[i] = (text[i] - tolower(key[i])) % 26;
            text[i] = (text[i] < 0)? text[i] + 26 + 97 : text[i] + 97;
        }
    }
    return text;
}