/**
 * @file 27_BST树.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
#include <vector>
using namespace std;
// cpp 中的
template <typename T, typename Comp = less<T> >
class BSTree {
   public:
    BSTree(Comp comp = Comp()) : root_(nullptr), comp_(comp) {}
    ~BSTree() {
        if (root_ != nullptr) {
            queue<Node*> que;
            que.push(root_);
            while (!que.empty()) {
                Node* node = que.front();
                que.pop();
                if (node->left_ != nullptr) {
                    que.push(node->left_);
                }
                if (node->right_ != nullptr) {
                    que.push(node->right_);
                }
                delete node;
            }
        }
    }

    // 二叉树节点定义
    struct Node {
        // T() 是一个 值初始化（value initialization） 的操作
        // 如果 T 是一个内置类型（如 int, double） 对应的默认值就是0 ， 0.0
        // 如果 T 是一个自定义类 T() 会调用这个类的默认构造函数
        Node(T data = T()) : data_(data), left_(nullptr), right_(nullptr) {}
        T data_;       // 数据域
        Node* left_;   // 左孩子
        Node* right_;  // 右孩子
    };
    Node* root_;  // 指向BST树的根节点
    Comp comp_;   // 定义一个函数对象

    // 非递归插入操作
    void n_insert(const T& val) {
        Node* p = new Node(val);
        // 树为空，生成根节点
        if (root_ == nullptr) {
            root_ = p;
        }
        // 搜索合适的插入位置，记录父节点的位置
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr) {
            // 开始查找
            if (cur->data_ == val) {
                return;                           // 不插入元素相同的值
            } else if (comp_(cur->data_, val)) {  // 节点值 < val，说明 val 更大，应该去右子树找
                parent = cur;
                cur = cur->right_;
            } else {  // 否则，说明 val 更小，应该去左子树找
                parent = cur;
                cur = cur->left_;
            }
        }
        // 把新节点插入到parent节点的孩子上
        if (comp_(val, parent->data_)) {  // val < parent->data_，插入到左子树
            parent->left_ = p;
        } else {  // val >= parent->data_，插入到右子树
            parent->right_ = p;
        }
    }

    // 递归插入操作
    void insert(const T& val) { root_ = insert(root_, val); }

    // 非递归删除操作
    /**
     * 1. 没有孩子的节点 父节点地址域 nullptr
     * 2. 有一个孩子 孩子写入父节点地址域
     * 3. 删除的节点有两个孩子
     *    找待删除节点的前驱节点（或者后继节点），用前驱或后继节点的值把待删除节点的值覆盖，然后直接删除前驱或后继节点。
     *    前驱： 左子树里的最大值
     *    后继： 右子树里的最小值
     *    前驱or后继最多有一个孩子，或者没有孩子。所以变成了情况1或2。
     */
    void n_remove(const T& val) {
        // 树空直接返回
        if (root_ == nullptr) return;
        // 搜索待删除节点
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                break;
            } else if (comp_(cur->data_, val)) {
                parent = cur;
                cur = cur->right_;
            } else {
                parent = cur;
                cur = cur->left_;
            }
        }
        // 没找到节点
        if (cur == nullptr) return;

        // 情况3 ==> 删除前驱节点（归结成情况1、2）
        if (cur->left_ != nullptr && cur->right_ != nullptr) {
            //
            parent = cur;
            Node* pre = cur->left_;  // 先指向左子树
            // 左子树里往右找最大值
            while (pre->right_ != nullptr) {
                parent = pre;
                pre = pre->right_;
            }
            // 把要删除的节点 用前驱节点代替
            cur->data_ = pre->data_;
            cur = pre;  // 让cur指向前驱节点，转化成情况1，2
        }
        // cur指向删除节点，parent指向其父节点，同一处理情况1或者2
        Node* child = cur->left_;
        if (child == nullptr) child = cur->right_;
        // 特殊情况 表示删除的是根节点 （原来的根节点只有[0,1]个孩子才可能出现这个情况）
        if (parent == nullptr) {
            root_ = child;
        } else {
            // 把待删除节点的孩子(nullptr或者不空)写入其父节点相应地址域中
            // 判断要删除的是父节点的左还是右
            if (parent->left_ == cur) {
                parent->left_ = child;
            } else {
                parent->right_ = child;
            }
        }
        delete cur;
    }

    // 递归删除操作
    void remove(const T& val) { root_ = remove(root_, val); }

    // 非递归查询操作
    bool n_query(const T& val) {
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                return true;
            } else if (comp_(cur->data_, val)) {
                cur = cur->right_;
            } else {
                cur = cur->left_;
            }
        }
        return false;
    }

    // 递归查询操作
    bool query(const T& val) { return nullptr != query(root_, val); }

    // 递归 前序 遍历操作
    void preOrder() {
        cout << "[递归]前序遍历:";
        preOrder(root_);
        cout << endl;
    }

    // 非递归 前序 遍历操作
    void n_preOrder() {
        cout << "[非递归]前序遍历:";
        if (root_ == nullptr) {
            return;
        }
        // 先进后出
        stack<Node*> s;
        s.push(root_);
        while (!s.empty()) {
            Node* top = s.top();
            s.pop();
            cout << top->data_ << " ";     // V
            if (top->right_ != nullptr) {  // R
                s.push(top->right_);
            }
            if (top->left_ != nullptr) {  // L
                s.push(top->left_);
            }
        }
        cout << endl;
    }

    // 递归 中序 遍历操作
    void inOrder() {
        cout << "[递归]中序遍历:";
        inOrder(root_);
        cout << endl;
    }

    // 非递归 中序 遍历操作 LVR
    void n_inOrder() {
        cout << "[非递归]中序遍历:";
        if (root_ == nullptr) {
            cout << endl;
            return;
        }
        // 1.	循环操作：从根节点开始，不断遍历当前节点。
        // 2.	如果当前节点有左子树，将当前节点入栈，并将当前节点移至左子树节点。
        // 3.	如果当前节点没有左子树，则弹出栈顶节点（即当前节点），输出该节点的值，并将当前节点指向右子树。
        // 4.	重复以上步骤，直到遍历完所有节点。
        stack<Node*> s;
        Node* cur = root_;
        while (!s.empty() || cur != nullptr) {
            // cur 不是空时，先入栈，直达cur是空。
            if (cur != nullptr) {
                s.push(cur);
                cur = cur->left_;
            } else {
                // cur 是空的时候出栈，然后指向右子树。
                Node* top = s.top();
                s.pop();
                cout << top->data_ << " ";
                cur = top->right_;
            }
        }
        cout << endl;
    }

    // 递归 后序 遍历操作
    void postOrder() {
        cout << "[递归]后序遍历:";
        postOrder(root_);
        cout << endl;
    }

    // 非递归 后序 遍历操作 LRV ==> VRL
    void n_postOrder() {
        cout << "[非递归]后序遍历:";
        if (root_ == nullptr) {
            cout << endl;
            return;
        }
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        while (!s1.empty()) {
            Node* top = s1.top();
            s1.pop();
            s2.push(top);  // V
            if (top->left_ != nullptr) {
                s1.push(top->left_);  // L
            }
            if (top->right_ != nullptr) {
                s1.push(top->right_);  // R
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->data_ << " ";
            s2.pop();
        }
        cout << endl;
    }

    // 递归 层序 遍历操作
    void levelOrder() {
        cout << "[递归]层序遍历:";
        // 有多少层 就得遍历多少次
        int h = high();
        for (int i = 0; i < h; i++) {
            // 递归调用树的层数次
            levelOrder(root_, i);
        }
        cout << endl;
    }

    // 非递归 层序 遍历操作
    // 深度遍历：使用栈
    // 广度遍历：使用队列
    void n_levelOrder() {
        cout << "[非递归]层序遍历:";
        if (root_ == nullptr) {
            return;
        }
        queue<Node*> que;
        que.push(root_);
        while (!que.empty()) {
            Node* front = que.front();
            que.pop();
            cout << front->data_ << " ";
            if (front->left_ != nullptr) {
                que.push(front->left_);
            }
            if (front->right_ != nullptr) {
                que.push(front->right_);
            }
        }
        cout << endl;
    }

    // 递归 求二叉树层数
    int high() { return high(root_); }

    // 递归求二叉树节点个数
    int number() { return number(root_); }

    //========================== 其它求值问题 ======================================
    // 求满足区间的元素值[i, j] , 放到vec中
    void findValues(vector<T>& vec, int i, int j) { findValues(vec, root_, i, j); }

    // 判断二叉树是否是BST树
    /**
     * 避免只局部判断
     *    40
     *   /  \
     *  20  60
     *     /  \
     *    30  80
     */
    bool isBSTree() {
        Node* pre = nullptr;
        return isBSTree(root_, pre);
    }

    // 判断子树问题
    bool isChildTree(BSTree<T, Comp>& child) {
        // 应该是从子树的根节点开始在大树找对应节点，然后根据子树遍历
        // 在当前二叉树上找child的根节点
        if (child.root_ == nullptr) {
            return true;
        }
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == child.root_->data_) {
                break;
            } else if (comp_(cur->data_, child.root_->data_)) {
                cur = cur->right_;
            } else {
                cur = cur->left_;
            }
        }
        // 上面循环的退出方式有两种，1. cur is null ， 2. 找到值 break
        if (cur == nullptr) {
            return false;
        }
        // 递归遍历
        return isChildTree(cur, child.root_);
    }

    // 最近公共祖先节点 Lowest Common Ancestor
    int getLCA(int val1, int val2) {
        // 这一步之前 理论需要先判断 两个值在不在树上 。 这里是默认存在
        return getLCA(root_, val1, val2);
    }

    // 镜像翻转
    void mirror01() { mirror01(root_); }

    // 镜像对称
    bool mirror02() {
        if (root_ == nullptr) return true;
        return mirror02(root_->left_, root_->right_);
    }

    // 重建二叉树
    // VLR 58 24 0 5 34 41 67 62 64 69 78
    // LVR 0 5 24 34 41 58 62 64 67 69 78
    // 根据前序能知道谁是根，根据中序能知道那些是左子树，那些是右子树。
    // 比如 VLR知道58是根，LVR里58左边是左子树，右边是右子树，
    // 然后VLR24是58的左节点，然后在根据LVR知道0 5是在24的左子树..依次循环
    void rebuild(int pre[], int i, int j, int in[], int m, int n) { root_ = _rebuild(pre, i, j, in, m, n); }

    // 判断平衡树 （高度差不高于1）
    bool isBalance() {
        int l = 0;
        bool falg = true;
        isBalance02(root_, 1, falg);
        return falg;
    }

    // 求中序倒数第K个节点
    int getVal(int k) {
        Node* node = getVal(root_, k);
        if (node == nullptr) {
            string err = "no No.";
            err += k;
            throw err;
        } else {
            return node->data_;
        }
    }

   private:
    // 递归前序遍历的实现 VLR
    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->data_ << " ";  // 操作V
            preOrder(node->left_);       // L
            preOrder(node->right_);      // R
        }
    }

    // 递归中序遍历的实现 LVR
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left_);        // L
            cout << node->data_ << " ";  // 操作V
            inOrder(node->right_);       // R
        }
    }

    // 递归后序遍历的实现 LRV
    void postOrder(Node* node) {
        if (node != nullptr) {
            postOrder(node->left_);      // L
            postOrder(node->right_);     // R
            cout << node->data_ << " ";  // V
        }
    }

    // 递归层序遍历的实现
    // 由于 levelOrder(root, i) 每次都要遍历整棵树的一部分，整体复杂度约 O(n^2)，比 队列实现的 O(n) 慢
    void levelOrder(Node* node, int i) {
        if (node == nullptr) return;
        // 直到 i = 0 时 才输出结果
        if (i == 0) {
            cout << node->data_ << " ";
            return;
        }
        // 如果 i > 0，说明还没到 i 层，需要继续递归寻找
        levelOrder(node->left_, i - 1);
        levelOrder(node->right_, i - 1);
    }

    // 递归实现求二叉树层数 求以node为根节点的子树的高度并返回高度值
    // 高度 = max(左子树高度, 右子树高度) + 1
    int high(Node* node) {
        if (node == nullptr) return 0;
        int left = high(node->left_);    // 递归计算左子树的高度
        int right = high(node->right_);  // 递归计算右子树的高度
        // return left > right ? left + 1 : right + 1
        return max(left, right) + 1;  // 取左右子树高度的较大值 +1（加上当前节点）
    }

    // 递归求二叉树节点个数的实现 求以node为根节点的树的节点总数，并返回
    int number(Node* node) {
        // 代码实际就是求 左孩子个数 + 右孩子个数 + 1
        if (node == nullptr) return 0;
        int left = number(node->left_);    // L
        int right = number(node->right_);  // R
        return left + right + 1;           // V
    }

    // 递归插入操作实现
    Node* insert(Node* node, const T& val) {
        if (node == nullptr) {
            // 递归结束，找到插入val的位置，生成新节点并返回其节点地址
            return new Node(val);
        }
        if (node->data_ == val) {
            return node;
        } else if (comp_(node->data_, val)) {
            node->right_ = insert(node->right_, val);
        } else {
            node->left_ = insert(node->left_, val);
        }
        return node;
    }

    // 递归查询操作实现
    Node* query(Node* node, const T& val) {
        if (node == nullptr) return nullptr;
        if (node->data_ == val) {
            return node;
        } else if (comp_(node->data_, val)) {
            return query(node->right_, val);
        } else {
            return query(node->left_, val);
        }
    }

    // 递归删除操作实现
    Node* remove(Node* node, const T& val) {
        if (node == nullptr) return nullptr;
        if (node->data_ == val) {
            // 情况3
            if (node->left_ != nullptr && node->right_ != nullptr) {
                // 找前驱节点
                Node* pre = node->left_;
                while (pre->right_ != nullptr) {
                    pre = pre->right_;
                }
                // 把原来的节点用前驱节点的值进行覆盖
                node->data_ = pre->data_;
                // 通过递归直接删除前驱节点
                node->left_ = remove(node->left_, pre->data_);
            } else {  // 情况1 、情况2
                if (node->left_ != nullptr) {
                    // 删除节点以后，把非空的左孩子返回，回溯时更新其父节点地址域
                    Node* left = node->left_;
                    delete node;
                    return left;
                } else if (node->right_ != nullptr) {
                    // 删除节点以后，把非空的右孩子返回，回溯时更新其父节点地址域
                    Node* right = node->right_;
                    delete node;
                    return right;
                } else {  // 删除的是没有孩子的节点  叶子节点
                    delete node;
                    // 回溯时更新其父节点地址域为nullptr
                    return nullptr;
                }
            }
        } else if (comp_(node->data_, val)) {
            node->right_ = remove(node->right_, val);
        } else {
            node->left_ = remove(node->left_, val);
        }
        // 把当前节点返回给父节点，更新父节点相应的地址域
        return node;
    }

    //==================================================================

    // 求满足区间的元素值[i, j] , 放到vec中
    void findValues(vector<T>& vec, Node* node, int i, int j) {
        if (node != nullptr) {
            // 在当前节点的左子树中搜索
            // 如果当前节点已经大于i，则左子树还有可能有大于i的数据
            // 如果当前节点已经小于i，则左子树中不可能还有比i大的数据，没必要继续搜索
            if (node->data_ > i) {
                findValues(vec, node->left_, i, j);  // L
            }

            if (node->data_ >= i && node->data_ <= j) {  // V
                vec.push_back(node->data_);              // 存储满足区间元素的值
            }

            // 在当前节点的右子树中搜索
            // 和上面同理,如果当前节点已经大于j，则右子树种也都比j大，没必要搜索
            if (node->data_ < j) {  // R
                findValues(vec, node->right_, i, j);
            }
        }
    }

    // 判断二叉树是否是BST树的实现 利用BST树中序遍历是一个升序的特点
    bool isBSTree(Node* node, Node*& pre) {  // 引用
        if (node == nullptr) {
            return true;
        }
        // LVR
        if (!isBSTree(node->left_, pre)) {
            return false;
        }
        if (pre != nullptr && comp_(node->data_, pre->data_)) {
            return false;
        }
        pre = node;
        return isBSTree(node->right_, pre);
        // 错误的判断
        // V
        // if (node->left_ != nullptr && comp_(node->data_, node->left_->data_))
        //{
        //	return false;
        // }

        // if (node->right_ != nullptr && comp_(node->right_->data_, node->data_))
        //{
        //	return false;
        // }

        // if (!isBSTree(node->left_)) // L 判断当前节点的左子树
        //{
        //	return false;
        // }

        // return isBSTree(node->right_); // R 判断当前节点的右子树
    }

    // 判断子树问题
    bool isChildTree(Node* parent, Node* child) {
        // 如果两棵树都为空，说明结构一致
        if (parent == nullptr && child == nullptr) {
            return true;
        }
        // 其中一个为空，说明结构不一致
        if (parent == nullptr || child == nullptr) {
            return false;
        }
        // 节点值不一致，直接返回 false
        if (parent->data_ != child->data_) {
            return false;
        }
        // 递归判断左右子树
        return isChildTree(parent->left_, child->left_)        // L
               && isChildTree(parent->right_, child->right_);  // R
    }

    // 最近公共祖先节点 Lowest Common Ancestor
    int getLCA(Node* node, int val1, int val2) {
        if (node == nullptr) {
            return -1;
        }
        if (comp_(node->data_, val1) && comp_(node->data_, val2)) {
            return getLCA(node->right_, val1, val2);
        } else if (comp_(val1, node->data_) && comp_(val2, node->data_)) {
            return getLCA(node->left_, val1, val2);
        } else {
            return node->data_;
        }
    }

    // 镜像翻转
    void mirror01(Node* node) {
        if (node == nullptr) {
            return;
        }
        Node* tmp = node->left_;
        node->left_ = node->right_;
        node->right_ = tmp;

        mirror01(node->left_);
        mirror01(node->right_);
    }

    // 镜像对称
    bool mirror02(Node* node1, Node* node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }
        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }
        if (node1->data_ != node2->data_) {
            return false;
        }
        return mirror02(node1->left_, node2->right_) && mirror02(node1->right_, node2->left_);
    }

    // 重建二叉树递归实现
    Node* _rebuild(int pre[], int i, int j, int in[], int m, int n) {
        if (i > j || m > n) {
            return nullptr;
        }
        //      i                          j
        // VLR 58 24 0 5 34 41 67 62 64 69 78
        // LVR 0 5 24 34 41 58 62 64 67 69 78
        //     m            k               n
        // LVR 0 5 24 34 41 的 VLR 就是 24 0 5 34 41
        // 所以要求41在VLR里的索引 => i + (k-m)

        // 创建当前子树的根节点
        Node* node = new Node(pre[i]);  // 拿前序的第一个数字创建子树根节点  V
        for (int k = m; k <= n; k++) {
            // 在中序遍历中找子树根节点的下标k
            if (pre[i] == in[k]) {
                node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1);   // L
                node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);  // R
                return node;
            }
        }
        return node;
    }

    // 判断平衡树 效率比较低
    bool isBalance(Node* node) {
        if (node == nullptr) return true;
        if (!isBalance(node->left_))  // L
            return false;
        if (!isBalance(node->right_))  // R
            return false;
        int left = high(node->left_);
        int right = high(node->right_);
        return abs(left - right) <= 1;  // V
    }

    // 判断平衡树 效率高 递归过程中，记录了节点的高度值  返回节点高度值
    int isBalance02(Node* node, int l, bool& flag) {
        if (node == nullptr) {
            return l;
        }
        int left = isBalance02(node->left_, l + 1, flag);  // L
        if (!flag) return left;
        int right = isBalance02(node->right_, l + 1, flag);  // R
        if (!flag) return right;
        // V
        if (abs(left - right) > 1) {  // 节点失衡了
            flag = false;
        }
        // 返回当前子树的最大高度
        return max(left, right);
    }

    // 求中序倒数第K个节点
    // LVR ==> RVL 正好是 reverse 的关系
    // 所以使用 RVL 就变成正数第K个节点
    int i = 1;
    Node* getVal(Node* node, int k) {
        if (node == nullptr) return nullptr;
        Node* left = getVal(node->right_, k);  // R
        if (left != nullptr) return left;
        // V
        if (i++ == k) {  // 在VRL的顺序下，找到正数第k个元素
            return node;
        }
        return getVal(node->left_, k);  // L
    }
};
#if 0 
int main() {
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (auto& v : arr) {
        bst.n_insert(v);
    }

    // bst.n_insert(12);
    // bst.preOrder();
    // bst.n_remove(12);
    // bst.preOrder();

    // bst.preOrder();
    // bst.inOrder();
    // bst.postOrder();
    // bst.levelOrder();
    // cout << bst.high() << endl;
    // cout << bst.number() << endl;

    // bst.n_preOrder();

    // bst.inOrder();
    // bst.remove(34);
    // bst.inOrder();

    bst.inOrder();
    // bst.n_inOrder();

    // bst.postOrder();
    // bst.n_postOrder();

    // bst.levelOrder();
    // bst.n_levelOrder();

    vector<int> vec;
    bst.findValues(vec, 10, 60);
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;
}
#endif
// 测试是否是BST树
void test01() {
    using Node = BSTree<int>::Node;
    BSTree<int> bst;
    bst.root_ = new Node(40);
    Node* node1 = new Node(20);
    Node* node2 = new Node(60);
    Node* node3 = new Node(30);
    Node* node4 = new Node(80);

    bst.root_->left_ = node1;
    bst.root_->right_ = node2;
    node2->left_ = node3;
    node2->right_ = node4;

    cout << bst.isBSTree() << endl;
}

// 测试子树判断问题
void test02() {
    int ar[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v : ar) {
        bst.insert(v);
    }
    using Node = BSTree<int>::Node;
    BSTree<int> bst1;
    bst1.root_ = new Node(67);
    Node* node1 = new Node(62);
    Node* node2 = new Node(69);
    Node* node3 = new Node(64);
    Node* node4 = new Node(78);
    bst1.root_->left_ = node1;
    bst1.root_->right_ = node2;
    node1->right_ = node3;
    // node2->right_ = node4;
    cout << bst.isChildTree(bst1) << endl;
}

// 测试LCA问题
void test03() {
    int ar[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v : ar) {
        bst.insert(v);
    }
    cout << bst.getLCA(62, 34) << endl;
}

// 测试镜像对称
void test04() {
    using Node = BSTree<int>::Node;
    BSTree<int> bst;
    /**
     *
         40
       /   \
      20    20
     /  \   / \
    10  15 15 10
     */
    bst.root_ = new Node(40);
    Node* node1 = new Node(20);
    Node* node2 = new Node(20);
    Node* node3 = new Node(10);
    Node* node4 = new Node(15);
    Node* node5 = new Node(15);
    Node* node6 = new Node(10);

    bst.root_->left_ = node1;
    bst.root_->right_ = node2;
    node1->left_ = node3;
    node1->right_ = node4;

    node2->left_ = node5;
    node2->right_ = node6;

    cout << bst.mirror02() << endl;
}

// 测试重建二叉树
void test05() {
    BSTree<int> bst;
    int pre[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    int in[] = {0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78};
    bst.rebuild(pre, 0, 10, in, 0, 10);
    bst.preOrder();
    bst.inOrder();
}

/**
 *
 *  树的形状
       58
      /   \
    24     67
   /  \    / \
  0   34  62  69
   \    \   \   \
    5   41   64  78

    如果中序遍历相同，则 BST 结构唯一，即使画法不同，本质上还是同一棵 BST。
    如果中序遍历不同，那肯定是两棵不同的 BST，结构也完全不同。
    视觉上的不同 ≠ 结构不同，只是画法不同，但如果父子关系变了，那就是结构真的不同了
 */
int main() {
    // test01();
    // int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    // BSTree<int> bst;
    // for (auto& v : arr) {
    //     bst.n_insert(v);
    // }
    // cout << bst.isBSTree() << endl;

    // test02();
    // test03();

    // int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    // BSTree<int> bst;
    // for (auto& v : arr) {
    //     bst.n_insert(v);
    // }
    // bst.levelOrder();
    // bst.mirror01();
    // bst.levelOrder();
    // bst.preOrder();
    // bst.inOrder();

    // test04();

    // test05();

    // int ar[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    // BSTree<int> bst;
    // for (int v : ar) {
    //     bst.insert(v);
    // }
    // cout << bst.isBalance() << endl;
    // bst.insert(12);
    // cout << bst.isBalance() << endl;

    using Elm = pair<int, string>;
    using Functor = function<bool(pair<int, string>, pair<int, string>)>;
    BSTree<Elm, Functor> bst([](Elm p1, Elm p2) -> bool { return p1.first > p2.first; });
}