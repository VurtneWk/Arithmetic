#include <iostream>

using namespace std;

struct Node {
    Node(int data = 0) : data_(data), pre_(nullptr), next_(nullptr) {}

    int data_;
    Node* pre_;
    Node* next_;
};

class DoubleLink {
   public:
    DoubleLink() { head_ = new Node(); }
    ~DoubleLink() {
        Node* p = head_;
        while (p != nullptr) {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }
    // 头插法
    void insertHead(int val) {
        // 先处理自己的指针
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        // 如果不是一开始 只有一个头节点的话，处理原来的第二个节点
        if (head_->next_ != nullptr) {
            head_->next_->pre_ = node;
        }
        head_->next_ = node;
    }
    // 尾插法
    void insertTail(int val) {
        // 先找尾节点
        Node* p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }
        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
    }
    // 节点删除
    void remove(int val) {
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                // p 如果是最后一个，则 p->next_ 是null
                if (p->next_ != nullptr) {
                    p->next_->pre_ = p->pre_;
                }
                // 如果想要删除多个，则去掉 return ，去掉下面的注释
                // Node* temp = p->next_;
                delete p;
                // p = temp;
                return;
            }
            p = p->next_;
        }
    }

    // 节点搜索
    bool find(int val) {
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                return true;
            } else {
                p = p->next_;
            }
        }
        return false;
    }
    // 链表节点输出
    void show() {
        Node* p = head_->next_;
        while (p != nullptr) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

   private:
    Node* head_;
};

int main() {
    DoubleLink dlink;

    dlink.insertHead(100);

    dlink.insertTail(20);
    dlink.insertTail(12);
    dlink.insertTail(78);
    dlink.insertTail(32);
    dlink.insertTail(7);
    dlink.insertTail(90);
    dlink.show();

    dlink.insertHead(200);
    dlink.show();

    dlink.remove(200);
    dlink.show();

    dlink.remove(90);
    dlink.show();

    dlink.remove(78);
    dlink.show();
}