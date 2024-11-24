#ifndef MAIN_SORTTESTER_H
#define MAIN_SORTTESTER_H

#include <vector>
#include <chrono>
#include <fstream>
#include "ArrayGenerator.h"

class SortTester {
 public:
  void Sort();

 private:
  ArrayGenerator arrayGenerator_;


  void QuickSort(std::vector<int>& arr, int l, int r, std::mt19937& rnd);

  void InsertionSort(std::vector<int>& arr, int l, int r);

  void Heapify(std::vector<int>& arr, int i, int l, int r);
  void BuildMaxHeap(std::vector<int>& arr, int l, int r);
  void HeapSort(std::vector<int>& arr, int l, int r);

  void IntroSort(std::vector<int>& arr, int l, int r, int recursion_cnt, std::mt19937& rnd);
};

#endif  // MAIN_SORTTESTER_H
