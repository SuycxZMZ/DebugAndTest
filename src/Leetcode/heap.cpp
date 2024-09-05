#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class heap {
public:
    heap(Compare comp = Compare()) : _cmp(comp) {}

    void push(const T& v);
    void pop();
    const T& top() const;
    bool empty() const { return _data.empty(); }
    size_t size() const { return _data.size(); }

private:
    std::vector<T> _data;
    Compare _cmp;

    // 上滤操作，用于插入节点
    void heap_ifUp(size_t idx);

    // 下滤操作，用于pop操作
    void heap_ifDown(size_t idx);
};

// push,加入尾部，上滤
template <typename T, typename Compare>
void heap<T, Compare>::push(const T& v) {
    _data.push_back(v);
    heap_ifUp(_data.size() - 1);
}

// pop,将首元素弹出，其实就是最后一个元素加到头上，做下滤
template <typename T, typename Compare>
void heap<T, Compare>::pop() {
    if (_data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    _data[0] = _data.back();
    _data.pop_back();
    heap_ifDown(0);
}

template <typename T, typename Compare>
const T& heap<T, Compare>::top() const {
    if (_data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return _data[0];    
}

// 上滤
template <typename T, typename Compare>
void heap<T, Compare>::heap_ifUp(size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;  // 父节点索引
        if (_cmp(_data[idx], _data[parent])) { // 父节点优先级高，那么就退出循环，结束了
            break;
        }
        std::swap(_data[idx], _data[parent]);
        idx = parent;  // 更新，下一轮
    }
}

// 下滤
template <typename T, typename Compare>
void heap<T, Compare>::heap_ifDown(size_t idx) {
    size_t sz = _data.size();
    while (true) {
        // 计算左右子节点的索引
        size_t left = 2 * idx + 1;
        size_t right = left + 1;
        size_t small = idx;

        if (left < sz && _cmp(_data[small], _data[left])) { // 左子节点优先级高，要调整
            small = left;
        }
        if (right < sz && _cmp(_data[small], _data[right])) { // 右子节点优先级高
            small = right;
        }
        if (small == idx) { // 传入索引优先级已经是最高了
            break;
        }

        std::swap(_data[idx], _data[small]); // 交换，接着下滤
        idx = small;
    }
}

int main() {
    heap<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);
    maxHeap.push(9);    

    std::cout << "-------------- max Heap test --------------" << std::endl;
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << std::endl;

    heap<int, std::greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(5);
    minHeap.push(9);     
    std::cout << "-------------- min Heap test --------------" << std::endl;
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;


    return 0;
}