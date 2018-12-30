#include <cassert>
#include <iostream>
#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>
#include <string>
#include <system_error>

#include "utility.h"

int main(int argc, char **argv) try {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <address>" << std::endl;
    return EXIT_FAILURE;
  }
  const char *addr = argv[1];

  nnxx::socket s2{nnxx::SP, nnxx::PAIR};

  s2.connect(addr);
  std::cout << "connect succeeded" << std::endl;

  nnxx::message status;
  while ((status = s2.recv()) && s2 != READY)
    ;

  std::cout << "Device ready" << std::endl;

  s2.send(WAITNEW);
  auto response = to_str(s2.recv());

  if (response.find(card) == 0) {
    std::cout << "Card acquired" << std::endl;
    auto id_ref = response.find(' ');
    assert(id_ref != std::string::npos);

    std::cout << "ID: " << response.substr(id_ref + 1) << std::endl;
  }

  return 0;
} catch (const std::system_error &e) {
  std::cerr << e.what() << std::endl;
  return 1;
}
