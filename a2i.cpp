// #include <iostream>
// #include <vector>
//
// using namespace std;
//
// class HybridSort {
// public:
//     static void sort(vector<int>& arr) {
//         if (arr.empty()) return;
//         mergeSort(arr, 0, arr.size() - 1);
//     }
//
// private:
//     static const int THRESHOLD = 15; // Параметр переключения
//
//     static void mergeSort(vector<int>& arr, int l, int r) {
//         if (r - l + 1 <= THRESHOLD) {
//             insertionSort(arr, l, r);
//         } else {
//             int m = l + (r - l) / 2;
//             mergeSort(arr, l, m);
//             mergeSort(arr, m + 1, r);
//             merge(arr, l, m, r);
//         }
//     }
//
//     static void merge(vector<int>& arr, int l, int m, int r) {
//         int n1 = m - l + 1;
//         int n2 = r - m;
//
//         vector<int> L(n1), R(n2);
//
//         for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
//         for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
//
//         int i = 0, j = 0, k = l;
//         while (i < n1 && j < n2) {
//             if (L[i] <= R[j]) {
//                 arr[k] = L[i];
//                 ++i;
//             } else {
//                 arr[k] = R[j];
//                 ++j;
//             }
//             ++k;
//         }
//
//         while (i < n1) {
//             arr[k] = L[i];
//             ++i;
//             ++k;
//         }
//
//         while (j < n2) {
//             arr[k] = R[j];
//             ++j;
//             ++k;
//         }
//     }
//
//     static void insertionSort(vector<int>& arr, int l, int r) {
//         for (int i = l + 1; i <= r; ++i) {
//             int key = arr[i];
//             int j = i - 1;
//
//             while (j >= l && arr[j] > key) {
//                 arr[j + 1] = arr[j];
//                 --j;
//             }
//             arr[j + 1] = key;
//         }
//     }
// };
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int n;
//     cin >> n;
//
//     vector<int> arr(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> arr[i];
//     }
//
//     HybridSort::sort(arr);
//
//     for (int i = 0; i < n; ++i) {
//         if (i > 0) cout << " ";
//         cout << arr[i];
//     }
//     cout << endl;
//
//     return 0;
// }