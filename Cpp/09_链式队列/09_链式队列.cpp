
#include <iostream>

using namespace std;

// 双向循环列表

class LinkQueue {
   public:
    LinkQueue() {
        _head = new Node();
        // 双向循环链表 初始化时 都指向自己
        _head->_next = _head;
        _head->_pre = _head;
    }
    ~LinkQueue() {
        Node* p = _head->_next;
        while (p != _head) {
            _head->_next = p->_next;
            p->_next->_pre = _head;
            delete p;
            p = _head->_next;
        }
        delete _head;
        _head = nullptr;
    }
    // 入队 放到尾部
    void push(int val) {
        Node* node = new Node(val);
        node->_next = _head;
        node->_pre = _head->_pre;
        _head->_pre->_next = node;
        _head->_pre = node;
    }
    // 出队 删除头部
    void pop() {
        if (_head->_next == _head) {  // 队列为空
            throw "queue is empty!";
        }
        Node* p = _head->_next;
        _head->_next = p->_next;
        p->_next->_pre = _head;
        delete p;
    }
    // 获取队头元素
    int front() const {
        if (_head->_next == _head) {
            throw "queue is empty!";
        }
        return _head->_next->_data;
    }
    int back() const {
        if (_head->_next == _head) {
            throw "queue is empty!";
        }
        return _head->_pre->_data;
    }
    // 判空
    bool empty() const { return _head->_next == _head; }

   private:
    struct Node {
        Node(int data = 0) : _data(data), _next(nullptr), _pre(nullptr) {}
        int _data;
        Node* _pre;
        Node* _next;
    };
    Node* _head;  // 指向头结点
};
int main() {
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    LinkQueue que;

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