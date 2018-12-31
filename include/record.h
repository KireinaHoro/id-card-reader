#ifndef RECORD_H
#define RECORD_H

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/map.hpp>

#include <chrono>
#include <map>
#include <string>

namespace nfc_scan {
struct Record {
public:
  std::string name;
  std::string sex;
  std::chrono::system_clock::time_point register_time;
  std::string student_id;

private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &name;
    ar &sex;
    ar &boost::serialization::make_binary_object(&register_time,
                                                 sizeof(register_time));
    ar &student_id;
  }
};

using TagID = uint32_t;
using Catalog = std::map<TagID, Record>;
}

#endif
