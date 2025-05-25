#ifndef STRINGSORTTESTER_H
#define STRINGSORTTESTER_H
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iostream>

class StringSortTester {
public:
  using SortFunction = std::function<void(std::vector<std::string> &, int &)>;

  static void test(const std::string &name,
                   std::vector<std::string> data,
                   SortFunction sorter) {
    int cmpCount = 0;

    auto start = std::chrono::high_resolution_clock::now();
    sorter(data, cmpCount);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[ " << name << " ]\n";
    std::cout << "Time: " << elapsed.count() << " ms\n";
    std::cout << "Comparisons: " << cmpCount << "\n";
    std::cout << "First 3 strings: \n";
    for (int i = 0; i < std::min(3, (int) data.size()); ++i)
      std::cout << "  " << data[i] << "\n";
    std::cout << "\n";
  }
};
#endif //STRINGSORTTESTER_H
