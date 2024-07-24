#include <bits/stdc++.h>

using namespace std;

template <typename T, typename Compare = std::less<T>>
class Heap {
public:
    Heap(Compare comp = Compare()) : comp(comp) {}

    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

private:
    std::vector<T> data;
    Compare comp;

    // 用于在插入新元素后，维护堆的性质。
    void heapifyUp(size_t index);
    // 用于在删除堆顶元素后，维护堆的性质。
    void heapifyDown(size_t index);
};

template <typename T, typename Compare>
void Heap<T, Compare>::push(const T& value) {
    data.push_back(value);
    heapifyUp(data.size() - 1);
}

template <typename T, typename Compare>
void Heap<T, Compare>::pop() {
    if (data.empty()) {
        throw std::out_of_range("Heap is empty");
    }
    data[0] = data.back();
    data.pop_back();
    heapifyDown(0);
}

template <typename T, typename Compare>
const T& Heap<T, Compare>::top() const {
    if (data.empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return data[0];
}

template <typename T, typename Compare>
void Heap<T, Compare>::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (!comp(data[index], data[parent])) {
            break;
        }
        std::swap(data[index], data[parent]);
        index = parent;
    }
}

template <typename T, typename Compare>
void Heap<T, Compare>::heapifyDown(size_t index) {
    size_t size = data.size();
    while (true) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < size && comp(data[left], data[smallest])) {
            smallest = left;
        }
        if (right < size && comp(data[right], data[smallest])) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        std::swap(data[index], data[smallest]);
        index = smallest;
    }
}


int main() {

    
    return 0;
}