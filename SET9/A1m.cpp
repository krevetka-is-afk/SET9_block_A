 #include <iostream>
 #include <vector>
 #include <string>

 using namespace std;

 void merge(vector<string>& arr, int left, int mid, int right) {
   vector<string> merged;
   int i = left, j = mid + 1;

   while (i <= mid && j <= right) {
     int minLen = min(arr[i].size(), arr[j].size());
     bool less = false;
     for (int k = 0; k < minLen; ++k) {
       if (arr[i][k] < arr[j][k]) { less = true; break; }
       if (arr[i][k] > arr[j][k]) { less = false; break; }
     }
     if (arr[i].size() < arr[j].size() && arr[i].substr(0, minLen) == arr[j].substr(0, minLen))
       less = true;

     if (less) merged.push_back(arr[i++]);
     else merged.push_back(arr[j++]);
   }

   while (i <= mid) merged.push_back(arr[i++]);
   while (j <= right) merged.push_back(arr[j++]);

   for (int k = 0; k < merged.size(); ++k)
     arr[left + k] = merged[k];
 }

 void mergeSort(vector<string>& arr, int left, int right) {
   if (left >= right) return;
   int mid = (left + right) / 2;
   mergeSort(arr, left, mid);
   mergeSort(arr, mid + 1, right);
   merge(arr, left, mid, right);
 }

 int main() {
   int n;
   cin >> n;
   vector<string> arr(n);
   for (int i = 0; i < n; ++i) cin >> arr[i];
   mergeSort(arr, 0, n - 1);
   for (const string& s : arr) cout << s << "\n";
 }