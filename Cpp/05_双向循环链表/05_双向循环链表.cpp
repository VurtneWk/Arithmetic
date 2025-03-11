#include <iostream>

using namespace std;

struct Node {
    Node(int data = 0) : data_(data), pre_(nullptr), next_(nullptr) {}

    int data_;
    Node* pre_;
    Node* next_;
};

class DoubleCircleLink {
   public:
    DoubleCircleLink() {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~DoubleCircleLink() {
        Node* p = head_->next_;
        while (p != head_) {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;  // 让P重新指向第一个节点 进行删除
        }
        delete head_;
        head_ = nullptr;
    }
    // 头插法
    void insertHead(int val) {
        // 先处理自己的指针
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        head_->next_->pre_ = node;
        head_->next_ = node;
    }
    // 尾插法
    void insertTail(int val) {
        Node* p = head_->pre_;  // 尾节点
        Node* node = new Node(val);
        node->pre_ = p;
        node->next_ = head_;
        p->next_ = node;
        head_->pre_ = node;
    }
    // 节点删除
    void remove(int val) {
        Node* p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;
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
        while (p != head_) {
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
        while (p != head_) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

   private:
    Node* head_;
};

int main() {
    DoubleCircleLink dlink;

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