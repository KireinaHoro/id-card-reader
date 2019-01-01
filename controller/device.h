#ifndef DEVICE_CONTROL_H
#define DEVICE_CONTROL_H

#include "record.h"
#include "utility.h"

#include <cstdint>
#include <string>

#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>

namespace nfc_scan {

class Scanner {
  nnxx::socket s{nnxx::SP, nnxx::PAIR};

public:
  Scanner(const Scanner &) = delete;
  Scanner(const std::string &a) {
    s.connect(a.c_str());
    nnxx::message status;
    s.send(INIT);
    while ((status = s.recv()) && s != READY)
      ;
  }

  ~Scanner() {
    s.send(CLOSE);
    s.close();
  }

  TagID scan() {
    s.send(WAITNEW);
    auto response = to_str(s.recv());
    assert(response.find(card) == 0);
    auto id_ref = response.find(' ');
    assert(id_ref != std::string::npos);

    uint64_t id = std::stoul(response.substr(id_ref + 1));
    assert(id <= UINT_MAX);
    return TagID(id);
  }
};
}

#endif
