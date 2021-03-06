#include <boost/archive/binary_iarchive.hpp>
#include <boost/io/ios_state.hpp>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include <signal.h>
#include <unistd.h>

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

std::atomic<bool> exiting;

void sigint_handler(int sig) { exiting.store(true); }

int main() {
  struct sigaction sa;
  sa.sa_handler = sigint_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGINT, &sa, nullptr) == -1) {
    perror("sigaction");
    return EXIT_FAILURE;
  }

  std::cout << "会議チェックイン" << std::endl;
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

  std::ifstream ifs(filename, std::ios::binary);
  {
    boost::archive::binary_iarchive ia(ifs);
    ia >> catalog;
  }

  std::cout << "チェックインを開始します。Ctrl-Cを押すと終了します。"
            << std::endl;
  std::cout << "生徒カードをスキャンしてください。" << std::endl;

  while (true) {
    try {
      if (exiting.load()) {
        break;
      }
      TagID id = s.scan();
      MINOR_SEP
      std::cout << "カード番号：";
      {
        boost::io::ios_flags_saver ifs(std::cout);
        std::cout << "0x";
        std::cout << std::hex << std::setw(8) << std::setfill('0');
        std::cout << id << std::endl;
      }
      Record rec = catalog.at(id);

      std::cout << "名前：" << rec.name << std::endl;
      std::cout << "性別：" << rec.sex << std::endl;
      std::cout << "登録時間：";
      std::time_t register_time =
          std::chrono::system_clock::to_time_t(rec.register_time);
      std::cout << std::ctime(&register_time);
      std::cout << "生徒番号：" << rec.student_id << std::endl;
    } catch (std::out_of_range &) {
      std::cout << "未登録の生徒カードです。" << std::endl;
      continue;
    } catch (...) {
      std::cout
          << "また別のカードをスキャンして、スキャナーの状態を直してください。"
          << std::endl;
    }
  }
  std::cout << "チェックインを終了いたします。" << std::endl;

  return EXIT_SUCCESS;
}
