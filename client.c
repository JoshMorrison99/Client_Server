#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

int main(){
	SOCKET client_socket;
	WSADATA wsastructure;
	int result;
	struct sockaddr_in client_addr;
	char recvData[500];
	char sendData[500] = "Hello from the Client!\n";

	result = WSAStartup(MAKEWORD(2, 2), &wsastructure);
	if(result != 0){
		printf("[!] WinSock initialization failed!\n");
		return 1;
	}

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9001);
	client_addr.sin_addr.s_addr = inet_addr("192.168.159.128");

	connect(client_socket, (SOCKADDR*) &client_addr, sizeof(client_addr));
	recv(client_socket, recvData, sizeof(recvData), 0);
	printf("Data from the server: %s\n", recvData);
	send(client_socket, sendData, sizeof(sendData), 0);
	closesocket(client_socket);
	WSACleanup();
    return 0;
}