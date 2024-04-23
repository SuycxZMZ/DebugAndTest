//
// Created by yuan su on 24-4-23.
//
#include <iostream>
#include <vector>

class allSort {
public:
    template<typename T>
    void quickSort(std::vector<T>& arr, int left, int right) {
        int i = left, j = right;
        T pivot = arr[(left + right) / 2];

        // Partition
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // Recursion
        if (left < j) quickSort(arr, left, j);
        if (i < right) quickSort(arr, i, right);
    }
};

int main() {
    allSort as;

    std::vector<int> arr = {5, 2, 9, 1, 5, 6};
    as.quickSort(arr, 0, arr.size() - 1);
    std::cout << "--------------qsort-------------" << std::endl;
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;



    return 0;
}


