#include <cstdlib>
#include <iostream>
#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>
#include <string>
#include <system_error>

#include "utility.h"
#include "scan.h"

int main(int argc, char **argv) try {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <address>" << std::endl;
    return EXIT_FAILURE;
  }
  const char *addr = argv[1];

  nnxx::socket s1{nnxx::SP, nnxx::PAIR};

  s1.bind(addr);
  std::cout << "bind succeeded" << std::endl;

  s1.send(READY);

  nnxx::message cmd;

  while (cmd = s1.recv()) {
    if (cmd == WAITNEW) {
      std::cout << "Scan request received" << std::endl;
      std::cout << "Performing scan" << std::endl;
      uint32_t id = wait_new_id();
      std::cout << "Sending id=" << id << " to controller" << std::endl;
      s1.send(from_str(card + ' ' + std::to_string(id)));
    }
  }

} catch (const std::system_error &e) {
  std::cerr << e.what() << std::endl;
  return 1;
}
