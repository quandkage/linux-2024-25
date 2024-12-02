#include <iostream>
#include "../WatchDog/WatchDog.hpp"


int main() {
  std::string path = "/home/robert/Desktop/linux-2024-25/Demo/DirWatcher/very_corrupted_business_documents";
  wathcer(path);

  return 0;
}