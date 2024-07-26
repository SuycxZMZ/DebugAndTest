//
// Created by Suycx on 24-7-26.
//
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int binarySearch(vector<int>&arr, int left, int right, int target) {
    if (left > right) return -1;
    int mid = -1;
    int l = left, r = right;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (target == arr[mid]) {
            return mid;
        } else if (target > arr[mid]) {
            l = mid + 1;
        } else if (target < arr[mid]) {
            r = mid - 1;
        }
    }
    // l 最终会调整到大于target的第一个元素，而r会调整到小于target的第一个元素
    if (l <= right) return l;
    return -1;
}


int main() {

    vector<int> arr = {1, 2, 5, 7, 7, 7, 7, 8, 9, 10, 12, 14, 15, 16, 17};
    // 手写的二分查找
    cout << binarySearch(arr, 0, arr.size() - 1, 6) << endl;

    // lower_bound 返回不小于目标的第一个元素迭代器
    cout << (std::lower_bound(arr.begin(), arr.end(), 7) - arr.begin()) << endl;

    // upper_bound 返回大于目标的第一个元素的迭代器
    cout << (std::upper_bound(arr.begin(), arr.end(), 7) - arr.begin()) << endl;

    return 0;
}