#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// 调整以第i个节点为子树的堆
template <typename T>
void heapify(vector<T> &input, int n, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;

  if (left < n && input[left] > input[largest])
    largest = left;
  if (right < n && input[right] > input[largest])
    largest = right;
  if (largest != i) {
    std::swap(input[largest], input[i]);
    heapify(input, n, largest);
  }
}

template <typename T>
void heapSort(vector<T> &input) {
  int n = input.size();
  // 从倒数第二层开始，往上调整
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapify(input, n, i);
  }
  // 交换
  for (int i = n - 1; i >= 0; --i) {
    std::swap(input[0], input[i]);
    heapify(input, i, 0);
  }
}

int main() {

  vector<int> input = {12, 3, 5, 2, 1, 8, 6, 7, 10};
  heapSort(input);
  std::cout << " -------------------- heapSort -------------------- " << std::endl;
  for (int i : input) {
    std::cout << i << " ";
  }

  return 0;
}