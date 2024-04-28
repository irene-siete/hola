#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

int main(){

    SOCKET client_socket;
    WSADATA wsastructure;
    int result;
    char text[500];
    char sendData[500]= "hola";
    char recvData[500];

    struct sockaddr_in client_addr;

    result = WSAStartup(MAKEWORD(2, 2), &wsastructure);
    if(result!=0){
        printf_s("winsock initialization failed\n");
        return 1;
    }

    client_socket= socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9001);
    client_addr.sin_addr.s_addr = inet_addr(text);

    connect(client_socket, (SOCKADDR*) &client_addr, sizeof(client_addr));
    recv(client_socket, recvData, sizeof(recvData), 0);
    printf_s("data from server: %s\n", recvData);
    send(client_socket, sendData, sizeof(sendData), 0);
    closesocket(client_socket);
    WSACleanup();
    return 0;
}
