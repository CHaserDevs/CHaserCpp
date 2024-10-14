#pragma once
#include <string>
#include <array>
#include <iostream>
#include "ISocket.hh"

namespace CHaserCpp {
  /**
   * CHaserと通信するクラス
   */
  class CHaserConnect {
  public:
    CHaserConnect(std::string name);
    ~CHaserConnect();

    std::array<int, 10> getReady();

    std::array<int, 10> walkRight();
    std::array<int, 10> walkLeft();
    std::array<int, 10> walkUp();
    std::array<int, 10> walkDown();

    std::array<int, 10> lookRight();
    std::array<int, 10> lookLeft();
    std::array<int, 10> lookUp();
    std::array<int, 10> lookDown();

    std::array<int, 10> searchRight();
    std::array<int, 10> searchLeft();
    std::array<int, 10> searchUp();
    std::array<int, 10> searchDown();

    std::array<int, 10> putRight();
    std::array<int, 10> putLeft();
    std::array<int, 10> putUp();
    std::array<int, 10> putDown();

  private:
    std::string name;
    std::string ip;
    int port;
    CHaserSocket sock;

    std::array<int, 10> sendCommand(std::string command);
  };
}