#include <iostream>
#include <winsock2.h>
#include <thread>
#include <cstring>
#include <vector>
#include <string>

#pragma warning(disable:4996) 
#pragma comment (lib, "Ws2_32.lib")

#define BUFFLEN 4096
#define PORT 8080

using namespace std;

bool connected = 1;
SOCKET client;
// Buffers
char buf[4096] = { 0 };
int buflen = 4096;
int room = 0;
vector<string> messages;

// Thread which will keep adding messages to queue
void reader()
{
    while (connected)
    {
        memset(&buf,0,BUFFLEN);
        recv(client, buf, buflen, 0);
        if (buf[0] != '#') {
            messages.push_back(string(buf));
        }
    }
}

// Function which handles menu and sending messages
void sender()
{
    while (connected)
    {
        try {


            int choice;
            memset(&buf, 0, buflen);
            cout << "\nClient Menu\n" << endl;
            cout << "1.BroadCast 2.Multicast 3.Print messages 4.Clear Screen 5.Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {

            case 1: {
                cout << "Enter message to broadcast : ";
                cin.ignore();
                cin.getline(buf, 4096);

                // 00 header for broadcast
                string message = "00" + string(buf);
                // Sending message
                send(client, message.c_str(), message.size(), 0);

                break;
            }
            case 2:
                cout << "\t1.Join Room 1\n\t2.Join Room 2\n\t3.Send Message\n\t4.Leave Room" << endl;
                cout << "\tChoice: ";
                cin >> choice;

                if (choice == 1) {
                    send(client, "11", 3, 0); // 11 header to join room 1
                    room = 1;
                    cout << "Joined Room 1" << endl;
                }
                else if (choice == 2) {
                    send(client, "12", 3, 0);  // 12 header to join room 1
                    room = 2;
                    cout << "Joined Room 2" << endl;
                }
                else if (choice == 3) {
                    if (room == 0) {
                        cout << "No Room Found" << endl;
                        break;
                    }
                    // Calculating Header 13 or 14 depending on room for multicast
                    string header = "1" + to_string((room + 2));

                    cout << "Enter message for room " << room << " : ";
                    cin.ignore();
                    cin.getline(buf, 4096);

                    string message = header + string(buf);
                    send(client, message.c_str(), message.length(), 0);
                    cout << "Message Sent" << endl;
                }
                else {
                    if (room == 0) {
                        cout << "You are not in any room" << endl;
                        break;
                    }
                    // Calculating Header 15 or 16 depending on room to leave
                    string header = "1" + to_string(room + 4);

                    send(client, header.c_str(), header.size(), 0);
                    cout << "Left room " << room << endl;
                }
                break;

            

case 3:
                // Display Inbox
                cout << "\n\n-----------Messages-------------\n" << endl;

                for (int i = 0; i < messages.size(); ++i) {
                    cout << messages[i] << endl;
                }
                cout << "\n----------------------------------\n";

                break;

            case 4:
                system("cls");
                break;

            case 5:
                send(client, "quit", 5, 0);
                exit(0);
                break;
            }
            if (choice != 4) {
                cout << "\n  Enter any key to return to main menu";
                cin >> choice;
            }
        }
        catch (exception) {
            cout << "Error while sending" << endl;
        }
    }
}

int main()
{
    WSADATA wsconfig;

    // Server Address struct
    struct sockaddr_in servaddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsconfig) != 0)
    {
        cout << "Couldnt start WSA" << endl;
        return -1;
    }
    // Setting up socket for communication 
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client == INVALID_SOCKET)
    {
        cout << "Couldnt create the socket" << endl;
        return -1;
    }

    // Filling server info
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(client, (sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
    {
        cout << "Error Connecting to server!!" << endl;
        return -1;
    }
    bool connected = true;
    cout << "Connected to server" << endl;

    thread t1(reader);
    sender();

    // Joining thread to main thread
    t1.join();

    while (connected);

    closesocket(client);
}
