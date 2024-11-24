#include "SortTester.h"

void SortTester::Sort() {
  std::mt19937 rnd(time(nullptr));

  const int cnt = 50;
  std::ofstream out;
  for (std::string folder_name : {"../random_array", "../almost_sorted_array", "../reversed_array"}) {
    out.open(folder_name + "/data.csv");
    for (int n = 500; n <= 10000; n += 100) {
      std::vector<int> arr;
      if (folder_name == "../random_array") {
        arr = arrayGenerator_.GetRandomArr(n);
      } else if (folder_name == "../almost_sorted_array") {
        arr = arrayGenerator_.GetAlmostSortedArr(n);
      } else if (folder_name == "../reversed_array") {
        arr = arrayGenerator_.GetReversedArr(n);
      }
      std::vector<int> arr_copy(n);

      double total1 = 0;
      for (int i = 0; i < cnt; ++i) {
        std::copy(arr.begin(), arr.end(), arr_copy.begin());

        auto start = std::chrono::high_resolution_clock::now();
        QuickSort(arr_copy, 0, n - 1, rnd);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        int64_t sec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        total1 += sec;
      }

      double total2 = 0;
      for (int i = 0; i < cnt; ++i) {
        std::copy(arr.begin(), arr.end(), arr_copy.begin());

        auto start = std::chrono::high_resolution_clock::now();
        IntroSort(arr_copy, 0, n - 1, 1, rnd);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        int64_t sec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        total2 += sec;
      }

      double total3 = 0;
      for (int i = 0; i < cnt; ++i) {
        std::copy(arr.begin(), arr.end(), arr_copy.begin());

        auto start = std::chrono::high_resolution_clock::now();
        std::sort(arr_copy.begin(), arr_copy.end());
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        int64_t sec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        total3 += sec;
      }

      out << n << " " << total1 / cnt << " " << total2 / cnt << " " << total3 / cnt << "\n";
    }
    out.close();
  }
}

void SortTester::IntroSort(std::vector<int>& arr, int l, int r, int recursion_cnt, std::mt19937& rnd) {
  if (l >= r) {
    return;
  }
  if (r - l + 1 < 16) {
    return InsertionSort(arr, l, r);
  }
  if (recursion_cnt >= 2 * std::log2(arr.size())) {
    return HeapSort(arr, l, r);
  }

  int i = l;
  int j = r;
  int pivot = arr[l + rnd() % (r - l)];
  while (i <= j) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (arr[j] > pivot) {
      --j;
    }
    if (i <= j) {
      std::swap(arr[i++], arr[j--]);
    }
  }
  IntroSort(arr, l, j, recursion_cnt + 1, rnd);
  IntroSort(arr, i, r, recursion_cnt + 1, rnd);
}

void SortTester::HeapSort(std::vector<int>& arr, int l, int r) {
  BuildMaxHeap(arr, l, r);
  for (int i = l; i <= r; ++i) {
    std::swap(arr[l], arr[r - i + l]);
    Heapify(arr, l, l, r - i + l - 1);
  }
}

void SortTester::BuildMaxHeap(std::vector<int>& arr, int l, int r) {
  for (int i = r; i >= l; --i) {
    Heapify(arr, i, l, r);
  }
}

void SortTester::Heapify(std::vector<int>& arr, int i, int l, int r) {
  while (l + 2 * (i - l) + 1 <= r && arr[l + 2 * (i - l) + 1] >= arr[i] ||
         l + 2 * (i - l) + 2 <= r && arr[l + 2 * (i - l) + 2] >= arr[i]) {
    int k = l + 2 * (i - l) + 1;
    if (k + 1 <= r && arr[k + 1] > arr[k]) {
      ++k;
    }
    std::swap(arr[i], arr[k]);
    i = k;
  }
}

void SortTester::InsertionSort(std::vector<int>& arr, int l, int r) {
  for (int i = l; i <= r; ++i) {
    for (int j = i - 1; j >= l && arr[j + 1] < arr[j]; --j) {
      std::swap(arr[j], arr[j + 1]);
    }
  }
}

void SortTester::QuickSort(std::vector<int>& arr, int l, int r, std::mt19937& rnd) {
  if (l >= r) {
    return;
  }
  int i = l;
  int j = r;
  int pivot = arr[l + rnd() % (r - l)];
  while (i <= j) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (arr[j] > pivot) {
      --j;
    }
    if (i <= j) {
      std::swap(arr[i++], arr[j--]);
    }
  }
  QuickSort(arr, l, j, rnd);
  QuickSort(arr, i, r, rnd);
}
