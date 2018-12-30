#include <iterator>
#include <nnxx/message.h>
#include <string>

inline nnxx::message from_str(const std::string &a) {
  return nnxx::make_message(a);
}

inline std::string to_str(const nnxx::message &a) {
  std::string result;
  copy(a.begin(), a.end(), std::back_inserter(result));
  return result;
}

const std::string ready = "ready";
const std::string waitnew = "waitnew";
const std::string card = "card";

const nnxx::message READY = from_str(ready);
const nnxx::message WAITNEW = from_str(waitnew);
const nnxx::message CARD = from_str(card);
