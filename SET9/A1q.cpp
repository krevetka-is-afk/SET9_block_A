 #include <iostream>
 #include <vector>
 #include <string>
 using namespace std;

 int charAt(const string &s, int d) {
   return d < s.length() ? s[d] : -1;
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

 int main() {
   int n;
   cin >> n;
   vector<string> arr(n);
   for (int i = 0; i < n; ++i) cin >> arr[i];
   ternaryQuickSort(arr, 0, n - 1, 0);
   for (const string &s: arr) cout << s << "\n";
 }
