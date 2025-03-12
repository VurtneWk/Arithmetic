
#include <iostream>

using namespace std;

class Queue {
   public:
    Queue(int size = 10) : _capacity(size), _front(0), _rear(0), _size(0) { _queue = new int[_capacity]; }
    ~Queue() {
        delete[] _queue;
        _queue = nullptr;
    }

    void push(int val) {
        // 队尾有一个位置保留是空的，
        if ((_rear + 1) % _capacity == _front) {
            // 队列满了 扩容
            expand(2 * _capacity);
        }
        _queue[_rear] = val;
        _rear = (_rear + 1) % _capacity;
        _size++;
    }
    // 出队
    void pop() {
        if (_front == _rear) {
            throw "queue is empty!";
        }
        _front = (_front + 1) % _capacity;
        _size--;
    }
    int front() const {
        if (_front == _rear) {
            throw "queue is empty!";
        }
        return _queue[_front];
    }
    int back() const {
        if (_front == _rear) {
            throw "queue is empty!";
        }
        // * (_rear - 1 + _capacity) % _capacity 是为了避免负数
        return _queue[(_rear - 1 + _capacity) % _capacity];
    }
    bool empty() const { return _front == _rear; }
    int size() const {
        // * 遍历一遍 O(n)
        // int size = 0;
        // for (int i = _front; i != _rear; i = (i + 1) % _capacity) {
        //     size++;
        // }
        return _size;
    }

   private:
    int* _queue;
    int _capacity;
    int _front;  // 队头
    int _rear;   // 队尾
    int _size;   // 长度
    void expand(int size) {
        int* temp = new int[size];
        // * 环形队列不能直接使用memcpy进行拷贝
        int i = 0;
        int j = _front;
        for (; j != _rear; i++, j = (j + 1) % _capacity) {
            temp[i] = _queue[j];
        }
        delete[] _queue;
        _queue = temp;
        _capacity = size;
        _front = 0;
        _rear = i;
    }
};

int main() {
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    Queue que;

    for (int v : arr) {
        que.push(v);
    }

    cout << que.front() << endl;
    cout << que.back() << endl;

    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl;
    cout << que.back() << endl;

    while (!que.empty()) {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}
