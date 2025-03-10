
#include <iostream>

using namespace std;

// 单向循环列表
class CirCleLink {
   public:
    CirCleLink() {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CirCleLink() {}

   private:
    // 节点
    struct Node {
        Node(int data = 0) : data_(data), next_(nullptr) {}
        int data_;
        Node* next_;
    };
    Node* head_;
    Node* tail_;
};
