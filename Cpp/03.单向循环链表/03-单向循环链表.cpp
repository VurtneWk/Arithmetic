
#include <iostream>

using namespace std;

// 单向循环列表
class CircleLink {
   public:
    CircleLink() {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircleLink() {
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
        if (node->next_ == head_) {
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
    void show() const {
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
// 测试 单向循环链表
#if 0
int main() {
    CircleLink clink;
    srand(time(0));
    clink.insertHead(100);

    for (int i = 0; i < 10; i++) {
        clink.insertTail(rand() % 100);
    }

    clink.insertTail(200);
    clink.show();

    clink.remove(200);
    clink.show();

    clink.insertTail(300);
    clink.show();
}
#endif

// 约瑟夫环问题

/**
 * 约瑟夫环是一个数学的应用问题：已知n个人（以编号1，2，3...n分别表示）围坐在一张圆桌周围，
 * 从编号为k的人开始报数，数到m的那个人出列，它的下一个人又从1开始报数，数到m的那个人又出列，
 * 依此规律重复下去，直到圆桌周围的人全部出列，输出人的出列顺序。
 */

struct Node {
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node* next_;
};

void joseph(Node* head, int k, int m) {
    Node* p = head;
    Node* q = head;  // 目的是指向p的前一个
    // q指向最后一个
    while (q->next_ != head) {
        q = q->next_;
    }
    // 先找到k， 然后开始数
    for (int i = 1; i < k; i++) {
        q = p;
        p = p->next_;
    }
    for (;;) {
        for (int i = 1; i < m; i++) {
            q = p;
            p = p->next_;
        }
        cout << p->data_ << " ";
        if (q == p) {
            delete p;
            break;
        }
        q->next_ = p->next_;
        delete p;
        p = q->next_;
    }
}
int main() {
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);

    head->next_ = n2;
    n2->next_ = n3;
    n3->next_ = n4;
    n4->next_ = n5;
    n5->next_ = n6;
    n6->next_ = n7;
    n7->next_ = n8;
    n8->next_ = head;

    joseph(head, 1, 1);
}