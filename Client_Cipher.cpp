#include <iostream>
#include <winsock2.h>
#include <thread>


#define BUFFLEN 4096
#define PORT 8080

using namespace std;

string encrypt_text(string text,string key);
string decrypt_text(string text,string key);

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
    
    string key,encrypted,decrypted;
    
    while(connected)
    {
        cout << "\n\t\tClient : ";
        cin.sync();
        getline(cin,decrypted);
        cout << "\t\tEnter encryption key: ";
        cin >> key;
        encrypted = encrypt_text(decrypted,key);
        
        send(client,encrypted.c_str(),buflen,0);
        
        if( encrypted.length() == 0 || key.length() ==0 )
        {
            connected = false;
            break;
        }
    
        recv(client,buf,buflen,0);

        cout <<"\nServer: " << buf << endl;
        encrypted = string(buf);
        cout << "Enter decryption key: ";
        cin >> key;
        decrypted = decrypt_text(encrypted,key);
        cout << "Decrypted : " << decrypted << endl;
    }

    
    closesocket(client);
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