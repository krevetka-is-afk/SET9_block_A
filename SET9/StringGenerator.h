#ifndef STRINGGENERATOR_H
#define STRINGGENERATOR_H
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class StringGenerator {
public:
  static const std::string allowedChars;

  static std::string randomString(int minLen = 10, int maxLen = 200) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(minLen, maxLen);
    std::uniform_int_distribution<int> charDist(0, allowedChars.size() - 1);

    int len = lenDist(rng);
    std::string s;
    for (int i = 0; i < len; ++i)
      s += allowedChars[charDist(rng)];
    return s;
  }

  static std::vector<std::string> generateRandom(int size) {
    std::vector<std::string> result(size);
    for (auto &str: result)
      str = randomString();
    return result;
  }

  static std::vector<std::string> generateReversed(int size) {
    auto result = generateRandom(size);
    std::sort(result.begin(), result.end(), std::greater<>());
    return result;
  }

  static std::vector<std::string> generateAlmostSorted(int size, int swaps = 10) {
    auto result = generateRandom(size);
    std::sort(result.begin(), result.end());

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, size - 1);
    for (int i = 0; i < swaps; ++i) {
      int a = dist(rng), b = dist(rng);
      std::swap(result[a], result[b]);
    }
    return result;
  }
};

const std::string StringGenerator::allowedChars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#%:;^&*()-";
#endif //STRINGGENERATOR_H
