#include <cmath>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <stack>
#include <functional>
#include <iostream>

using namespace std;
using paircmp = function<bool(const pair<int, int>&, const pair<int, int>&)>;
paircmp cmp = [](const pair<int, int>& a, const pair<int, int>& b){
    return a.second > b.second;
};
void test_priority_queue()
{
    // 小根堆，传 大于
    priority_queue<long long, vector<long long>, greater<long long>> _minheap;
    // 大根堆 传 小于
    priority_queue<long long, vector<long long>, less<long long>> _maxheap;

    // 自定义小根堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, paircmp> _min_pairheap(paircmp);
}

void test_lower_bound()
{
    // std::lower_bound 用于在已排序的容器（比如 vector、array 或 deque）中查找第一个大于或等于某个值的元素的位置
    // 找不到则返回 最后一个位置
    vector<int> vec = {1, 2, 3, 4, 5, 6, 6, 6, 8, 8, 9, 10};
    auto it1 = std::lower_bound(vec.begin(), vec.end(), 6);
    auto it2 = std::lower_bound(vec.begin(), vec.end(), 7);
    auto it3 = std::lower_bound(vec.begin(), vec.end(), 11);
    cout << "6 position : " << it1 - vec.begin() << endl;
    cout << "7 position : " << it2 - vec.begin() << endl;
    cout << "11 position : " << it3 - vec.begin() << endl;
    cout << "-----------------------------" << endl;

    // upper_bound 用于在已排序的容器中查找大于某个值的第一个元素的位置
    it1 = std::upper_bound(vec.begin(), vec.end(), 6);
    it2 = std::upper_bound(vec.begin(), vec.end(), 7);
    it3 = std::upper_bound(vec.begin(), vec.end(), 10);
    cout << "6 position : " << it1 - vec.begin() << endl;
    cout << "7 position : " << it2 - vec.begin() << endl;
    cout << "11 position : " << it3 - vec.begin() << endl;

}

int main()
{

    test_priority_queue();
    cout << "-----------------------------" << endl;
    test_lower_bound();

    return 0;
}