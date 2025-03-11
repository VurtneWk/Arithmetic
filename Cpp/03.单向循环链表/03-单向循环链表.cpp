
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
    ~CirCleLink() {
        Node* p = head_->next_;
        while (p != head_) {
            // 头 指向 p的下一个节点
            head_->next_ = p->next_;
            // 删除p
            delete p;
            // p 指向 头 指向的下一个节点
            p = head_->next_;
        }
        delete head_;
    }
    // 尾插法
    void insertTail(int val) {
        Node* node = new Node(val);
        node->next_ = tail_->next_;  // 等于 node->next_ = head_;
        tail_->next_ = node;
        tail_ = node;  // 更新末尾指针 ， 指向新节点
    }
    // 头插法
    void insertHead(int val) {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        if (node->next_ == head) {
            tail_ = node;
        }
    }
    void remove(int val) {
        Node* q = head_;         // 要删除的节点的上一个
        Node* p = head_->next_;  // 要删除的节点
        while (p != head_) {
            if (p->data_ == val) {
                // 找到删除节点
                q->next_ = p->next_;
                delete p;
                // 如果删除的 p 是一个末尾节点
                if (q->next_ == head_) {
                    tail_ = q;
                }
                return;
            } else {
                p = p->next_;
                q = q->next_;
            }
        }
    }

    // 查询
    bool find(int val) {
        Node* p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                return true;
            }
            p = p->next_;
        }
        return false;
    }
    // 打印链表
    void Show() const {
        Node* p = head_->next_;
        while (p != head_) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

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

int main() {
    CircleLink clink;
    srand(time(0));
    clink.insertHead(100);

    for (int i = 0; i < 10; i++) {
        clink.insertTail(rand() % 100);
    }

    clink.insertTail(200);
    clink.Show();

    clink.remove(200);
    clink.show();

    clink.insertTail(300);
    clink.show();
}