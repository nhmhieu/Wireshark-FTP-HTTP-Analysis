#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

// Bắt buộc link thư viện ws2_32 cho Windows
#pragma comment(lib, "ws2_32.lib")

int main() {
    // 1. Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    const char* hostname = "www.google.com";
    const char* port = "80";

    std::cout << "[1] Resolving hostname: " << hostname << "..." << std::endl;

    // 2. DNS Lookup
    struct addrinfo hints, *res = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP

    if (getaddrinfo(hostname, port, &hints, &res) != 0) {
        std::cerr << "DNS lookup failed!" << std::endl;
        WSACleanup();
        return 1;
    }

    // 3. Create Socket
    SOCKET sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }

    // 4. Connect to Server
    std::cout << "[2] Connecting to " << hostname << " on port " << port << "..." << std::endl;
    if (connect(sock, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "Connection failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(res);

    std::cout << "-> Connection established!" << std::endl << std::endl;

    // 5. Send HTTP GET Request
    std::string request = 
        "GET / HTTP/1.1\r\n"
        "Host: www.google.com\r\n"
        "User-Agent: SocketLab/1.0\r\n"
        "Connection: close\r\n"
        "\r\n";

    std::cout << "[3] Sending HTTP GET Request..." << std::endl;
    if (send(sock, request.c_str(), (int)request.length(), 0) == SOCKET_ERROR) {
        std::cerr << "Send request failed!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 6. Receive Response
    std::cout << "[4] Receiving HTTP Response from server..." << std::endl << std::endl;
    char buffer[4096];
    int bytes_received;
    std::string response = "";

    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received < 0) {
        std::cerr << "Receive data failed!" << std::endl;
    } else {
        std::cout << "======== HTTP RESPONSE CONTENT ========" << std::endl;
        std::cout << response << std::endl;
        std::cout << "=======================================" << std::endl;
    }

    // 7. Cleanup & Close Socket
    closesocket(sock);
    WSACleanup();
    std::cout << std::endl << "[5] Socket connection closed." << std::endl;

    return 0;
}