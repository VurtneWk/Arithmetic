/**
 * @file 14_二叉堆.cpp
 * @author vurtnewk
 * @brief
 */

#include <functional>
#include <iostream>

using namespace std;

// 优先级队列实现
class PriorityQueue {
   public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int capacity = 20, Comp comp = greater<int>()) : size_(0), capacity_(capacity), comp_(comp) {
        que_ = new int[capacity_];
    }

    PriorityQueue(Comp comp) : size_(0), capacity_(20), comp_(comp) { que_ = new int[capacity_]; }
    ~PriorityQueue() {
        delete[] que_;
        que_ = nullptr;
    }
    // 入堆操作
    // * 数据放入到末尾，然后需要进行上浮操作，用于满足 大/小根堆
    void push(int val) {
        // 扩容
        if (size_ == capacity_) {
            int* p = new int(2 * capacity_);
            memcpy(p, que_, size_ * sizeof(int));
            delete[] que_;
            que_ = p;
            capacity_ *= 2;
        }
        // 只有一个元素 ， 不用进行堆的上浮调整
        if (size_ == 0) {
            que_[size_] = val;
        } else {
            siftUp(size_, val);
        }
        size_++;
    }
    // 出堆操作
    void pop() {
        if (size_ == 0) throw "container is empty!";
        size_--;
        if (size_ > 0) {
            // 删除堆顶元素，还有剩余的元素，要进行堆的下沉调整
            // * 将堆中最后一个元素（通常是数组的最后一个元素）填补到堆顶
            siftDown(0, que_[size_]);
        }
    }
    bool empty() const { return size_ == 0; }

    int top() const {
        if (size_ == 0) throw "container is empty!";
        return que_[0];
    }

    int size() const { return size_; }

   private:
    int* que_;
    int size_;
    int capacity_;
    Comp comp_;
    // 上浮
    void siftUp(int index, int val) {
        // 最多计算到根节点 O(logn)   O(1)
        while (index > 0) {
            // 计算父节点的下标
            // 因为 (i - 1) / 2 可以统一求出左、右子节点的父节点，而 (i - 2) / 2 只适用于右子节点
            int father = (index - 1) / 2;
            //  greater时：左值比有值大则为ture，也就是父节点的值较小
            // 这时就把当前索引的值改为父节点的值
            if (comp_(val, que_[father])) {
                que_[index] = que_[father];
                index = father;
            } else {
                break;
            }
        }
        // 把val放到i的位置
        que_[index] = val;
    }
    // 出堆下沉调整 O(logn)    O(1)
    void siftDown(int i, int val) {
        // i下沉不能超过最后一个有孩子的节点
        // 有孩子的节点:也就是第一个非叶子结点 ==> ((size_-1) -1) / 2 ==> (size_-2)/2
        // ==> size_/2 - 1  所以 i <= size_/2 - 1 ==> i < size_ / 2
        while (i < size_ / 2) {
            // 第 i 个几点的左孩子
            int child = 2 * i + 1;
            if (child + 1 < size_ && comp_(que_[child + 1], que_[child])) {
                // 如果i节点右孩子的值大于左孩子, child记录右孩子的下标
                child += 1;
            }
            // 孩子的值 如果大于val
            if (comp_(que_[child], val)) {
                que_[i] = que_[child];
                i = child;
            } else {
                // 已经满足堆的性质，提前结束
                break;
            }
        }
        // 最后在i的位置 记录val
        que_[i] = val;
    }
};

int main() {
    // PriorityQueue que;  // 基于大根堆实现的优先级队列

    // 基于小根堆实现的优先级队列
    PriorityQueue que([](int a, int b) { return a < b; });
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        que.push(rand() % 100);
    }

    while (!que.empty()) {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;
}