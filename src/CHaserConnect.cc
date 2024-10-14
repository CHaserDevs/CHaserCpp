#include "./CHaserConnect.hh"
#include <iostream>
#include "CHaserConnect.hh"

using namespace CHaserCpp;

CHaserConnect::CHaserConnect(std::string name) : name(name), sock("127.0.0.1", 0) {
  this->name = name;

  std::cout << "接続先IPアドレスを入力してください" << std::endl;
  std::cin >> this->ip;
  std::cout << "接続先ポート番号を入力してください" << std::endl;
  std::cin >> this->port;

  if (this->ip == "localhost") {
    this->ip = "127.0.0.1";
  }
  
  this->sock = CHaserSocket(this->ip, this->port);

  try {
    sock.connect();
    std::cout << this->name << "はサーバーに接続しました" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << this->name << "はサーバーに接続できませんでした" << std::endl;
    std::cerr << "サーバーが起動しているかどうか or ポート番号、IPアドレスを確認してください" << std::endl;
    std::cerr << e.what() << std::endl;
  }

  this->sock.send(this->name);
}

CHaserConnect::~CHaserConnect() {
  this->sock.close();
}

std::array<int, 10> CHaserConnect::getReady() {
  return this->sendCommand("gr");
}

std::array<int, 10> CHaserConnect::walkRight() {
  return this->sendCommand("wr");
}

std::array<int, 10> CHaserConnect::walkLeft() {
  return this->sendCommand("wl");
}

std::array<int, 10> CHaserConnect::walkUp() {
  return this->sendCommand("wu");
}

std::array<int, 10> CHaserConnect::walkDown() {
  return this->sendCommand("wd");
}

std::array<int, 10> CHaserConnect::lookRight() {
  return this->sendCommand("lr");
}

std::array<int, 10> CHaserConnect::lookLeft() {
  return this->sendCommand("ll");
}

std::array<int, 10> CHaserConnect::lookUp() {
  return this->sendCommand("lu");
}

std::array<int, 10> CHaserConnect::lookDown() {
  return this->sendCommand("ld");
}

std::array<int, 10> CHaserConnect::searchRight() {
  return this->sendCommand("sr");
}

std::array<int, 10> CHaserConnect::searchLeft() {
  return this->sendCommand("sl");
}

std::array<int, 10> CHaserConnect::searchUp() {
  return this->sendCommand("su");
}

std::array<int, 10> CHaserConnect::searchDown() {
  return this->sendCommand("sd");
}

std::array<int, 10> CHaserConnect::putRight() {
  return this->sendCommand("pr");
}

std::array<int, 10> CHaserConnect::putLeft() {
  return this->sendCommand("pl");
}

std::array<int, 10> CHaserConnect::putUp() {
  return this->sendCommand("pu");
}

std::array<int, 10> CHaserConnect::putDown() {
  return this->sendCommand("pd");
}

std::array<int, 10> CHaserConnect::sendCommand(std::string command) {
  std::array<int, 10> result;
  char response[10];

  try {
    this->sock.send(command);
    this->sock.recv(response, sizeof(response));
  } catch (const std::exception &e) {
    std::cerr << this->name << "はサーバーに接続できませんでした" << std::endl;
    std::cerr << "サーバーが起動しているかどうか or ポート番号、IPアドレスを確認してください" << std::endl;
    std::cerr << e.what() << std::endl;
  }

  for (int i = 0; i < 10; i++) {
    result[i] = response[i] - '0';
  }

  return result;
}