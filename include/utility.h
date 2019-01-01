#ifndef UTILITY_H
#define UTILITY_H
#include <iterator>
#include <nnxx/message.h>
#include <string>

namespace nfc_scan {
inline nnxx::message from_str(const std::string &a) {
  return nnxx::make_message(a);
}

inline std::string to_str(const nnxx::message &a) {
  std::string result;
  copy(a.begin(), a.end(), std::back_inserter(result));
  return result;
}

const std::string init = "init";
const std::string ready = "ready";
const std::string waitnew = "waitnew";
const std::string card = "card";
const std::string close = "close";

const nnxx::message INIT = from_str(init);
const nnxx::message READY = from_str(ready);
const nnxx::message WAITNEW = from_str(waitnew);
const nnxx::message CARD = from_str(card);
const nnxx::message CLOSE = from_str(close);
}
#endif
