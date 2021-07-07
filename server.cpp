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

    SOCKET server = socket(AF_INET, SOCK_DGRAM, 0);
    cout << "Socket number: " << server << endl;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);

    cout << "Address: " << addr.sin_addr.S_un.S_addr << endl;
    cout << "Addr1: " << (int)addr.sin_addr.S_un.S_un_b.s_b1 << endl;
    cout << "Addr2: " << (int)addr.sin_addr.S_un.S_un_b.s_b2 << endl;
    cout << "Addr3: " << (int)addr.sin_addr.S_un.S_un_b.s_b3 << endl;
    cout << "Addr4: " << (int)addr.sin_addr.S_un.S_un_b.s_b4 << endl;
    cout << "Port: " << addr.sin_port << endl;

    if(bind(server, (sockaddr*) &addr, sizeof(sockaddr_in))){
        cout << "Biding error" << endl;
        closesocket(server);
        WSACleanup();

        return -2;
    }

    char* buf = new char[BUFFER];

    while(true)
    {
        sockaddr_in from;
        int fromlen = sizeof(sockaddr_in);
        cout << "Waiting for client message..." << endl;
        int msg_len = recvfrom(server, buf, BUFFER, 0, (sockaddr*) &from, &fromlen);
        if(msg_len)
        {
            int err = WSAGetLastError();
            cout << "Receive error: " << err << endl;
            closesocket(server);
            WSACleanup();
            return -3;    
        }

        string client(inet_ntoa(from.sin_addr));
        int client_port = ntohs(from.sin_port);
        string msg(buf, msg_len);
        cout << "Message from " << client << ":" << client_port << ":" << msg << endl;

        if(msg == "quit"){
            break;
        }
    }

    delete[] buf;

    closesocket(server);
    WSACleanup();
    return 0;   
}