#include <boost/archive/binary_oarchive.hpp>
#include <boost/io/ios_state.hpp>

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "device.h"
#include "record.h"

#define MAJOR_SEP std::cout << "======================" << std::endl;
#define MINOR_SEP std::cout << "----------------------" << std::endl;

#define CHECK_STREAM                                                           \
  if (std::cin.fail() || std::cin.eof()) {                                     \
    std::cin.clear();                                                          \
    break;                                                                     \
  }

using namespace std::string_literals;
using namespace nfc_scan;

Catalog catalog;

int main() {
  std::cout << "新入社員登録プログラム" << std::endl;
  MAJOR_SEP

  std::cout << "スキャナーのアドレスを入力してください：";
  std::string dev_addr;
  std::cin >> dev_addr;
  std::cout << "スキャナーに接続しています…" << std::endl;
  Scanner s(dev_addr);
  std::cout << "スキャナーに接続しました。" << std::endl;
  MAJOR_SEP

  std::cout << "データベースファイルの名前を入力してください：";
  std::string filename;
  std::cin >> filename;
  MAJOR_SEP

  std::ofstream ofs(filename, std::ios::binary);
  std::cout << "これより登録を開始します。Ctrl-Dを押すと終了します。"
            << std::endl;

  while (true) {
    Record rec;
    MINOR_SEP
    std::cout << "名前：";
    std::cin >> rec.name;
    CHECK_STREAM
    std::cout << "性別：";
    std::cin >> rec.sex;
    CHECK_STREAM
    std::cout << "登録時間は現時点にします。" << std::endl;
    rec.register_time = std::chrono::system_clock::now();
    std::cout << "生徒番号：";
    std::cin >> rec.student_id;
    CHECK_STREAM
    std::cout << "生徒カードをスキャンしてください。" << std::endl;
    TagID id = s.scan();
    std::cout << "カード番号：";
    {
      boost::io::ios_flags_saver ifs(std::cout);
      std::cout << "0x";
      std::cout << std::hex << std::setw(8) << std::setfill('0');
      std::cout << id << std::endl;
    }

    MINOR_SEP
    std::cout << rec.name << "さんの登録が完了致しました。" << std::endl;

    catalog[id] = std::move(rec);
  }

  MAJOR_SEP
  std::cout << "データベースの保存を行います。" << std::endl;
  {
    boost::archive::binary_oarchive oa(ofs);
    oa << catalog;
  }

  std::cout << "データベースの保存が完了致しました。" << std::endl;

  return EXIT_SUCCESS;
}
