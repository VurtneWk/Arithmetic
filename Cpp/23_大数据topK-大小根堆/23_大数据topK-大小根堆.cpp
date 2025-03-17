
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

#if 0

int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 1000; i++) {
        vec.push_back(rand() % 10000);
    }
// 求vec 中 值 最小的前5个元素
#if 0
    priority_queue<int> maxHeap;
    int k = 5;
    // 由前k个元素构建一个大根堆
    for (int i = 0; i < k; i++) {
        maxHeap.push(vec[i]);
    }

    for (int i = k; i < vec.size(); i++) {
        if (maxHeap.top() > vec[i]) {
            maxHeap.pop();
            maxHeap.push(vec[i]);
        }
    }
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << endl;
        maxHeap.pop();
    }
#endif

    // 求vec 中 值 最大的前5个元素
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k = 5;
    // 由前k个元素构建一个大根堆
    for (int i = 0; i < k; i++) {
        minHeap.push(vec[i]);
    }

    for (int i = k; i < vec.size(); i++) {
        if (minHeap.top() < vec[i]) {
            minHeap.pop();
            minHeap.push(vec[i]);
        }
    }
    while (!minHeap.empty()) {
        cout << minHeap.top() << endl;
        minHeap.pop();
    }
}

#endif

int main() {
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        vec.push_back(rand() % 1000);
    }

// 统计重复次数最小的前3个数字
#if 0
    int k = 3;
    unordered_map<int, int> map;
    // 在map中记录重复次数
    for (auto key : vec) {
        map[key]++;
    }
    using Type = pair<int, int>;
    // Type&：按引用传递（避免拷贝，提高效率）
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> maxHeap([](Type& a, Type& b) -> bool { return a.second < b.second; });

    auto it = map.begin();

    for (int i = 0; i < k; i++, it++) {
        maxHeap.push(*it);
    }

    for (; it != map.end(); it++) {
        if (maxHeap.top().second > it->second) {
            maxHeap.pop();
            maxHeap.push(*it);
        }
    }

    while (!maxHeap.empty()) {
        cout << "key:" << maxHeap.top().first << " cnt:" << maxHeap.top().second << endl;
        maxHeap.pop();
    }
#endif
    // 统计重复次数最大的前3个数字
    int k = 3;
    unordered_map<int, int> map;
    for (auto key : vec) {
        map[key]++;
    }

    // 放入大根堆的时候，需要放key-value键值对
    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> minheap([](Type& a, Type& b) -> bool { return a.second > b.second; });

    auto it = map.begin();
    for (int i = 0; i < k; i++, ++it) {
        minheap.push(*it);
    }

    for (; it != map.end(); ++it) {
        if (minheap.top().second < it->second) {
            minheap.pop();
            minheap.push(*it);
        }
    }

    while (!minheap.empty()) {
        cout << "key:" << minheap.top().first << " cnt:" << minheap.top().second << endl;
        minheap.pop();
    }
}