#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "StringGenerator.h"
#include "StringSortTester.h"

// Объявления сортировок
void mergeSort(std::vector<std::string> &, int &); // A1m
void ternaryQuickSortWrapper(std::vector<std::string> &, int &); // A1q
void msdRadixSort(std::vector<std::string> &, int &); // A1r
void msdRadixWithQuickSort(std::vector<std::string> &, int &); // A1rq

// Запуск тестов
void runAllTests(int size, std::ofstream &logFile) {
  using namespace std;

// Вид входных данных
  vector<pair<string, function<vector<string>(int)>>> generators = {
    {"random", [](int size) { return StringGenerator::generateRandom(size); }},
    {"reversed", [](int size) { return StringGenerator::generateReversed(size); }},
    {"almost_sorted", [](int size) { return StringGenerator::generateAlmostSorted(size); }}
  };

// Сортировки
  vector<pair<string, StringSortTester::SortFunction> > algorithms = {
    {"MergeSort", mergeSort},
    {"QuickSort", ternaryQuickSortWrapper},
    {"MSD Radix", msdRadixSort},
    {"MSD+Quick", msdRadixWithQuickSort}
  };

  for (auto &[genName, genFunc]: generators) {
    auto baseData = genFunc(size);
    for (auto &[algName, sorter]: algorithms) {
      vector<string> data = baseData;
      int cmpCount = 0;

      auto start = chrono::high_resolution_clock::now();
      sorter(data, cmpCount);
      auto end = chrono::high_resolution_clock::now();
      chrono::duration<double, std::milli> elapsed = end - start;

      logFile << size << "," << genName << "," << algName << "," << elapsed.count() << "," << cmpCount << "\n";

      cout << genName << " / " << algName << ": " << elapsed.count() << " ms, comparisons: " << cmpCount << "\n";
    }
  }
}

int main() {
  // заводим выходной поток
  std::ofstream log("results.csv");
  log << "Size,Generator,Algorithm,TimeMs,Comparisons\n";

  for (int size = 100; size <= 3000; size += 100) {
    runAllTests(size, log);
  }

  log.close();
  return 0;
}

//////////
// A1m
void merge(std::vector<std::string> &arr, int left, int mid, int right, int &cmpCount) {
  std::vector<std::string> merged;
  int i = left, j = mid + 1;

  while (i <= mid && j <= right) {
    int minLen = std::min(arr[i].size(), arr[j].size());
    bool less = false;
    for (int k = 0; k < minLen; ++k) {
      ++cmpCount;
      if (arr[i][k] < arr[j][k]) {
        less = true;
        break;
      } else if (arr[i][k] > arr[j][k]) {
        less = false;
        break;
      }
    }
    if (arr[i].size() < arr[j].size()) ++cmpCount;

    if (less || (arr[i].size() < arr[j].size() && arr[i].substr(0, minLen) == arr[j].substr(0, minLen))) {
      merged.push_back(arr[i++]);
    } else {
      merged.push_back(arr[j++]);
    }
  }
  while (i <= mid) merged.push_back(arr[i++]);
  while (j <= right) merged.push_back(arr[j++]);

  for (int k = 0; k < merged.size(); ++k)
    arr[left + k] = merged[k];
}

void mergeSortHelper(std::vector<std::string> &arr, int left, int right, int &cmpCount) {
  if (left >= right) return;
  int mid = (left + right) / 2;
  mergeSortHelper(arr, left, mid, cmpCount);
  mergeSortHelper(arr, mid + 1, right, cmpCount);
  merge(arr, left, mid, right, cmpCount);
}

void mergeSort(std::vector<std::string> &arr, int &cmpCount) {
  mergeSortHelper(arr, 0, arr.size() - 1, cmpCount);
}

/////////////
// A1q
int charAt(const std::string& s, int d) {
  return d < s.length() ? s[d] : -1;
}

void ternaryQuickSort(std::vector<std::string>& a, int lo, int hi, int d, int& cmpCount) {
  if (lo >= hi) return;
  int lt = lo, gt = hi;
  int v = charAt(a[lo], d);
  int i = lo + 1;

  while (i <= gt) {
    int t = charAt(a[i], d);
    ++cmpCount;
    if (t < v) std::swap(a[lt++], a[i++]);
    else if (t > v) std::swap(a[i], a[gt--]);
    else i++;
  }

  ternaryQuickSort(a, lo, lt - 1, d, cmpCount);
  if (v >= 0) ternaryQuickSort(a, lt, gt, d + 1, cmpCount);
  ternaryQuickSort(a, gt + 1, hi, d, cmpCount);
}

void ternaryQuickSortWrapper(std::vector<std::string>& arr, int& cmpCount) {
  ternaryQuickSort(arr, 0, arr.size() - 1, 0, cmpCount);
}

//////////
// A1r
void msdRadixSortImpl(std::vector<std::string>& a, int lo, int hi, int d, int& cmpCount) {
  if (hi <= lo) return;

  const int R = 256;
  std::vector<int> count(R + 2, 0);
  std::vector<std::string> aux(hi - lo + 1);

  for (int i = lo; i <= hi; ++i)
    count[charAt(a[i], d) + 2]++;

  for (int r = 0; r < R + 1; ++r)
    count[r + 1] += count[r];

  for (int i = lo; i <= hi; ++i)
    aux[count[charAt(a[i], d) + 1]++] = a[i];

  for (int i = 0; i < aux.size(); ++i)
    a[lo + i] = aux[i];

  for (int r = 0; r < R; ++r)
    msdRadixSortImpl(a, lo + count[r], lo + count[r + 1] - 1, d + 1, cmpCount);
}

void msdRadixSort(std::vector<std::string>& arr, int& cmpCount) {
  msdRadixSortImpl(arr, 0, arr.size() - 1, 0, cmpCount);
}

///////////
// A1rq
void msdRadixWithQuickImpl(std::vector<std::string>& a, int lo, int hi, int d, int& cmpCount) {
  const int THRESHOLD = 74;
  if (hi <= lo) return;
  if (hi - lo + 1 < THRESHOLD) {
    ternaryQuickSort(a, lo, hi, d, cmpCount);
    return;
  }

  const int R = 256;
  std::vector<int> count(R + 2, 0);
  std::vector<std::string> aux(hi - lo + 1);

  for (int i = lo; i <= hi; ++i)
    count[charAt(a[i], d) + 2]++;

  for (int r = 0; r < R + 1; ++r)
    count[r + 1] += count[r];

  for (int i = lo; i <= hi; ++i)
    aux[count[charAt(a[i], d) + 1]++] = a[i];

  for (int i = 0; i < aux.size(); ++i)
    a[lo + i] = aux[i];

  for (int r = 0; r < R; ++r)
    msdRadixWithQuickImpl(a, lo + count[r], lo + count[r + 1] - 1, d + 1, cmpCount);
}

void msdRadixWithQuickSort(std::vector<std::string>& arr, int& cmpCount) {
  msdRadixWithQuickImpl(arr, 0, arr.size() - 1, 0, cmpCount);
}