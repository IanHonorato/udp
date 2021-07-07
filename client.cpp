#include <iostream>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <String>

#pragma comment (lib, "Ws2_32.lib")

#define IP "192.168.1.12"
#define PORT 51234
#define BUFFER 16

using namespace std;

int main(){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData))
    {
        cout << "start error" << endl;
        return -1;
    }

    SOCKET client = socket(AF_INET, SOCK_DGRAM, 0);
    cout << "Socket number: " << client << endl;

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    cout << "Address: " << server_addr.sin_addr.S_un.S_addr << endl;
    cout << "Addr1: " << (int)server_addr.sin_addr.S_un.S_un_b.s_b1 << endl;
    cout << "Addr2: " << (int)server_addr.sin_addr.S_un.S_un_b.s_b2 << endl;
    cout << "Addr3: " << (int)server_addr.sin_addr.S_un.S_un_b.s_b3 << endl;
    cout << "Addr4: " << (int)server_addr.sin_addr.S_un.S_un_b.s_b4 << endl;
    cout << "Port: " << server_addr.sin_port << endl;

   while(true)
    {
        string msg;
        cout << "Type message: ";
        cin >> msg;
        int msg_len = sendto(client, msg.c_str(), msg.length(), 0, (sockaddr*) &server_addr, sizeof(sockaddr_in));
        if(msg_len < 0)
        {
            int err = WSAGetLastError();
            cout << "Send error: " << err << endl;
            closesocket(client);
            WSACleanup();
            return -4;    
        }
        if(msg == "quit"){
            break;
        }
    }

    closesocket(client);

    WSACleanup();
    return 0;   
}