#pragma once
#include <iostream>
#include <string>

namespace CHaserCpp {
  class ICHaserSocket {
  public:
    virtual void connect() = 0;
    virtual void send(std::string) = 0;
    virtual void recv(char *buf, int buflen) = 0;
    virtual void close() = 0;
  };
}

#if defined(_WIN32) || defined(_WIN64)
/**
 * Windows用ソケットクラス
 */
#include <winsock2.h>
#include <ws2tcpip.h>

namespace CHaserCpp {
  class CHaserSocket : public ICHaserSocket {
  public:
    CHaserSocket(std::string ip, int port) {
      this->ip = ip;
      this->port = port;
      inet_pton(AF_INET, this->ip.c_str(), &this->addr.sin_addr);
      WSADATA wsaData;
      WSAStartup(MAKEWORD(2, 0), &wsaData);
    }

    void connect() {
      this->sock = socket(AF_INET, SOCK_STREAM, 0);
      this->addr.sin_family = AF_INET;
      this->addr.sin_port = htons(this->port);
      this->addr.sin_addr.S_un.S_addr = inet_addr(this->ip.c_str());
      ::connect(this->sock, (struct sockaddr *)&this->addr, sizeof(this->addr));
    }

    void send(std::string content) {
      ::send(this->sock, content.c_str(), content.size(), 0);
    }

    void recv(char *buf, int buflen) {
      ::recv(this->sock, buf, buflen, 0);
    }

    void close() {
      closesocket(this->sock);
      WSACleanup();
    }

  private:
    std::string ip;
    int port;
    SOCKET sock;
    struct sockaddr_in addr;
  };
}

#elif defined(__linux__) || defined(__APPLE__)
/**
 * Linux/BSD互換システム用ソケットクラス
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace CHaserDevs {
  class CHaserSocket : public ICHaserSocket {
  public:
    CHaserSocket(std::string ip, int port) {
      return;
    }

    void connect() {
      return;
    }

    void send(std::string content) {
      return;
    }

    void recv(char *buf, int buflen) {
      return;
    }

    void close() {
      return;
    }
  };
}

#else
/**
 * 知らないOS
 */
#error "unknown platform"

#endif