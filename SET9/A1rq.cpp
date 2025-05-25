#include <iostream>
#include <vector>
#include <string>
using namespace std;

int charAt(const string &s, int d) {
  return d < s.size() ? s[d] : -1;
}

void ternaryQuickSort(vector<string> &a, int lo, int hi, int d) {
  if (lo >= hi) return;
  int lt = lo, gt = hi;
  int v = charAt(a[lo], d);
  int i = lo + 1;

  while (i <= gt) {
    int t = charAt(a[i], d);
    if (t < v) swap(a[lt++], a[i++]);
    else if (t > v) swap(a[i], a[gt--]);
    else i++;
  }

  ternaryQuickSort(a, lo, lt - 1, d);
  if (v >= 0) ternaryQuickSort(a, lt, gt, d + 1);
  ternaryQuickSort(a, gt + 1, hi, d);
}

void msdRadixQuickSort(vector<string> &a, int lo, int hi, int d) {
  const int THRESHOLD = 74;
  if (hi <= lo) return;
  if (hi - lo + 1 < THRESHOLD) {
    ternaryQuickSort(a, lo, hi, d);
    return;
  }

  const int R = 256;
  vector<int> count(R + 2, 0);
  vector<string> aux(hi - lo + 1);

  for (int i = lo; i <= hi; ++i)
    count[charAt(a[i], d) + 2]++;
  for (int r = 0; r < R + 1; ++r)
    count[r + 1] += count[r];
  for (int i = lo; i <= hi; ++i)
    aux[count[charAt(a[i], d) + 1]++] = a[i];
  for (int i = 0; i < aux.size(); ++i)
    a[lo + i] = aux[i];
  for (int r = 0; r < R; ++r)
    msdRadixQuickSort(a, lo + count[r], lo + count[r + 1] - 1, d + 1);
}

int main() {
  int n;
  cin >> n;
  vector<string> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  msdRadixQuickSort(arr, 0, n - 1, 0);
  for (const string &s: arr) cout << s << "\n";
}
