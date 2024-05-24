//
// Created by yuan su on 24-4-23.
//
#include <iostream>
#include <vector>

class allSort {
public:
    /**
     * @brief 快排
     * @tparam T
     * @param input
     * @param left
     * @param right
     */
    template<typename T>
    void _qqsort(std::vector<T>& input, int left, int right) {
        int i = left;
        int j = right;
        int privot = input[(i + j) / 2];
        while (i <= j) {
            while (input[i] < privot) ++i;
            while (input[j] > privot) --j;
            if (i <= j) {
                std::swap(input[i++], input[j--]);
            }
        }
        if (j > left) _qqsort(input, left, j);
        if (i < right) _qqsort(input, i, right);
    }


    /**
     * @details 合并两个有序数组
     * @tparam T
     * @param arr
     * @param left
     * @param mid
     * @param right
     */
    template <typename T>
    void merge(std::vector<T>& arr, int left, int mid, int right) {
        // 左边数组长度
        int n1 = mid - left + 1;
        // 右边数组长度
        int n2 = right - mid;

        // 临时数组大小为合并后的数组大小
        std::vector<T> tempArr(right - left + 1);

        int i = left, j = mid + 1, k = 0;

        // 合并两个有序子数组到临时数组中
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                tempArr[k++] = arr[i++];
            } else {
                tempArr[k++] = arr[j++];
            }
        }

        // 将剩余元素复制到临时数组中
        while (i <= mid) {
            tempArr[k++] = arr[i++];
        }
        while (j <= right) {
            tempArr[k++] = arr[j++];
        }

        // 将临时数组的内容复制回原始数组
        for (int p = 0; p < k; p++) {
            arr[left + p] = tempArr[p];
        }
    }

    /**
     * @details 归并排序主函数
     * @tparam T
     * @param arr
     * @param left
     * @param right
     */
    template <typename T>
    void mergeSort(std::vector<T>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // 递归排序左右两部分
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // 合并排序后的两部分
            merge(arr, left, mid, right);
        }
    }
};

int main() {
    allSort as;

    std::vector<int> arr = {5, 2, 9, 1, 5, 6};
    as._qqsort(arr, 0, arr.size() - 1);
    std::cout << "--------------qsort-------------" << std::endl;
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;

    std::vector<int> arr2 = {5, 2, 9, 1, 5, 6};
    as.mergeSort(arr2, 0, arr2.size() - 1);
    std::cout << "--------------mergesort-------------" << std::endl;
    for (int i : arr2) std::cout << i << " ";
    std::cout << std::endl;


    return 0;
}


