#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

// 节点类型
struct Node {
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node *next_;
};

// 单链表实现 （这个链表头节点[哨兵节点]不存数据）
class Clink {
   public:
    Clink() {
        // head_ 初始化指向头节点
        head_ = new Node();
    }
    ~Clink() {
        // 节点的释放
        Node *p = head_;
        while (p != nullptr) {
            // 头节点设置为 下一个节点
            head_ = head_->next_;
            delete p;  // 删除当前的节点（头）
            p = head_;
        }
        head_ = nullptr;
    }

    // 链表尾插法 O(n)
    void insertTail(int val) {
        // 查找尾节点
        Node *p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }

        // 生成新节点
        Node *node = new Node(val);
        // 把新节点挂载尾节点后
        p->next_ = node;
    }

    // 链表头插法 O(1)
    void insertHead(int val) {
        // 生成新节点
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    // 链表节点的删除
    void remove(int val) {
        // 查找
        Node *q = head_;
        Node *p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                q->next_ = p->next_;
                delete p;
                return;
            } else {
                q = p;
                p = p->next_;
            }
        }
    }
    // 删除多个节点
    void removeAll(int val) {
        // 上一个节点
        Node *lastNode = head_;
        // 当前有值的节点
        Node *currentNode = head_->next_;
        while (currentNode != nullptr) {
            if (currentNode->data_ == val)  // 当前的值相同，需要删除
            {
                lastNode->next_ = currentNode->next_;
                delete currentNode;
                currentNode = lastNode->next_;  // 指向下一个节点
            } else {
                // 如果数据不相同  移动两个指针的位置
                lastNode = currentNode;
                currentNode = currentNode->next_;
            }
        }
    }
    // 搜索 list O(n)   数组的搜索 下表访问/随机访问arr[i]O(1)  搜索O(n)
    bool find(int val) {
        Node *p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                return true;
            } else {
                p = p->next_;
            }
        }
        return false;
    }
    // 链表打印
    void show() {
        Node *p = head_->next_;
        while (p != nullptr) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
    // 逆序

   private:
    Node *head_;  // 指向链表的头节点
    friend void reverseLink(Clink &link);
    friend bool getLaskKNode(Clink &link, int k, int &val);
    friend void mergeLink(Clink &link1, Clink &link2);
};

// 单链表测试
#if 0
int main()
{
        Clink link;
        srand(time(0));
        for (int i = 0; i < 10; i++)
        {
                int val = rand() % 100;
                link.insertHead(val);
                cout << val << " ";
        }
        cout << endl;

        link.insertTail(23);
        link.insertHead(23);
        link.insertHead(23);
        // link.remove(23);
        link.show();

        link.removeAll(23);
        link.show();
}
#endif

// 单链表逆序 (头插法)
#if 0
void reverseLink(Clink &link) {
    Node *head = link.head_;      // 记录原来的头节点
    Node *p = link.head_->next_;  // 第二个节点
    if (p == nullptr) {
        return;
    }

    head->next_ = nullptr;  // 把头节点断开

    while (p != nullptr) {
        Node *q = p->next_;  // 记录下一个节点
        // p指针指向的节点进行头插
        p->next_ = head->next_;
        head->next_ = p;
        p = q;  // 准备遍历下一个节点
    }
}

// 单链表逆序测试
int main()
{
        Clink link;
        srand(time(0));
        for (int i = 0; i < 10; i++)
        {
                int val = rand() % 100;
                link.insertTail(val);
        }
        link.show();
        reverseLink(link);
        link.show();
}
#endif

// 单链表求倒数第K个节点
#if 0
bool getLaskKNode(Clink &link, int k, int &val) {
    Node *pre = link.head_;
    Node *p = link.head_;
    if (k < 1) {
        return false;
    }
    for (int i = 0; i < k; i++) {
        p = p->next_;
        if (p == nullptr) {
            return false;
        }
    }
    // 两个指针差是K，然后同时往后移动，当p是nullptr时，pre正好指向倒数第k个
    while (p != nullptr) {
        pre = pre->next_;
        p = p->next_;
    }
    val = pre->data_;
    return true;
}

// 单链表求倒数第K个节点测试
int main() {
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        link.insertTail(val);
    }
    link.show();

    reverseLink(link);
    link.show();

    int kval;
    int k = 8;
    if (getLaskKNode(link, k, kval)) {
        cout << "倒数第" << k << "个节点的值:" << kval << endl;
    }
}
#endif

// 合并两个有序单链表 (都合并到 link1 上面)
#if 0
void mergeLink(Clink &link1, Clink &link2) {
    Node *last = link1.head_;
    Node *p = link1.head_->next_;
    Node *q = link2.head_->next_;
    link2.head_->next_ = nullptr;
    while (p != nullptr && q != nullptr) {
        // p 链表的数据小
        if (p->data_ < q->data_) {
            last->next_ = p;  // 主链表 先指向小的这个node
            p = p->next_;     // 小的node 往后移动一位
        } else {
            last->next_ = q;
            q = q->next_;
        }
        // 主链表 也往后移动一位
        last = last->next_;
    }
    if (p != nullptr) {
        last->next_ = p;
    } else {
        last->next_ = q;
    }
}

int main() {
    int arr[] = {25, 37, 52, 78, 88, 92, 98, 108};
    int brr[] = {13, 23, 40, 56, 62, 77, 109};

    Clink link1;
    Clink link2;

    for (int v : arr) {
        link1.insertTail(v);
    }

    for (int v : brr) {
        link2.insertTail(v);
    }

    link1.show();
    link2.show();

    mergeLink(link1, link2);
    link1.show();
    link2.show();
}
#endif

// 单链表判断是否有环？ 求环的入口节点 --- 快慢指针
#if 0
/**
 * 求环的入口节点 :
 * fast遍历的节点数量 = 2 * slow遍历的节点数量
 * x 是起点到入口的距离
 * y 是入口到 相遇点的距离
 * a 是相遇点到 末尾的距离
 * x + y + a + y = 2 (x + y) 得出 a = x
 * 这是在起点和相遇点分别定义一个指针P1 P2，然后同时移动，当相遇时的点就是入口
 */
bool isLinkHasCircle(Node *head, int &val) {
    Node *fast = head;
    Node *slow = head;
    while (fast != nullptr && fast->next_ != nullptr) {
        fast = fast->next_->next_;
        slow = slow->next_;
        if (slow == fast) {
            // 快慢指针再次遇见，链表存在环
            fast = head;
            while (fast != slow) {
                fast = fast->next_;
                slow = slow->next_;
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
}

int main() {
    Node head;

    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n3;

    int val;
    if (isLinkHasCircle(&head, val)) {
        cout << "链表存在环，环的入口节点是：" << val << endl;
    }
}
#endif

// 判断两个单链表是否相交 如果相交，返回相交节点的值
#if 1
/**
 * 思路： 如果有相交，那相交之后的长度一致，不一致的是相交之前，所以先计算两个链表的长度差值。
 * 从差值开始同步移动
 *
 */
bool isLinkHasMerge(Node *head1, Node *head2, int &val) {
    int cnt1 = 0, cnt2 = 0;
    Node *p = head1->next_;
    Node *q = head2->next_;
    while (p != nullptr) {
        cnt1++;
        p = p->next_;
    }

    while (q != nullptr) {
        cnt2++;
        q = q->next_;
    }
    p = head1;
    q = head2;
    if (cnt1 > cnt2) {
        int offset = cnt1 - cnt2;
        while (offset-- > 0) {
            p = p->next_;
        }
    } else {
        int offset = cnt2 - cnt1;
        while (offset-- > 0) {
            q = q->next_;
        }
    }
    while (p != nullptr && q != nullptr) {
        if (p == q) {
            val = p->data_;
            return true;
        }
        p = p->next_;
        q = q->next_;
    }
    return false;
}

int main() {
    Node head1;
    Node n1(25), n2(67), n3(32), n4(18);
    // head-> 25 -> 67 -> 32 -> 18
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;

    Node head2;
    Node n5(31);
    // head-> 31 -> 32
    head2.next_ = &n5;
    n5.next_ = &n3;

    int val;
    if (isLinkHasMerge(&head1, &head2, val)) {
        cout << "链表相交，相交节点是：" << val << endl;
    }
}
#endif
