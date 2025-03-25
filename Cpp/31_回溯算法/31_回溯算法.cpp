#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/// @brief 打印多少次？
#if 0
void func(int arr[], int i, int length) {
    if (i == length) {  // 递归结束的条件
        for (int j = 0; j < length; j++) {
            cout << arr[j] << " ";
        }
        cout << endl;
    } else {
        func(arr, i + 1, length);
        func(arr, i + 1, length);  // 只执行两次的话 是二叉树 2^3
                                   // func(arr, i + 1, length);  // 三叉树 3^3
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int length = sizeof(arr) / sizeof(arr[0]);
    func(arr, 0, length);
}
#endif

// 子集树代码
#if 0
void func(int arr[], int i, int length, int x[]) {
    if (i == length) {  // 递归结束的条件
        for (int j = 0; j < length; j++) {
            if (x[j] == 1) {  // 只打印选择了 i 节点的值
                cout << arr[j] << " ";
            }
        }
        cout << endl;
    } else {
        x[i] = 1;                     //  选择i节点
        func(arr, i + 1, length, x);  // 遍历i的左孩子
        x[i] = 0;                     // 不选择i节点
        func(arr, i + 1, length, x);  // 遍历i的右孩子
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int length = sizeof(arr) / sizeof(arr[0]);
    int x[3] = {0};
    func(arr, 0, length, x);
}
#endif

// 整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
#if 0
int arr[] = {12, 6, 7, 11, 16, 3, 8};
const int length = sizeof(arr) / sizeof(arr[0]);
int x[length] = {0};      // 子集树辅助数组  记录节点走向左孩子还是右孩子，代表i节点被选择&未被选择
int bestx[length] = {0};  // 记录最优解
// vector<int> x;  可以使用集合来直接记录被选择的值
// vector<int> bestx;
unsigned int minDiff = 0xFFFFFFFF;  // 记录最小的差值
int sum = 0;                        // 记录所选子集数字的总和
int r = 0;                          // 记录未选择数字的和

// 生成子集树
void func(int i) {
    if (i == length) {  // 访问到了子集树的一个叶子节点
        int result = abs(sum - r);
        if (result < minDiff) {
            minDiff = result;
            for (int j = 0; j < length; ++j) {
                bestx[j] = x[j];
            }
        }
    } else {
        // r 的初始值其实是 arr所有数据总和
        r -= arr[i];
        sum += arr[i];
        x[i] = 1;
        func(i + 1);
        sum -= arr[i];
        r += arr[i];

        x[i] = 0;
        func(i + 1);
    }
}

int main() {
    for (int v : arr) {
        r += v;
    }
    func(0);
    for (int i = 0; i < length; ++i) {
        if (bestx[i] == 1) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    cout << "minDiff:" << minDiff << endl;
}
#endif

// 整数选择问题：给定2n个整数，从里面挑选出n个整数，让选择的整数的和，和剩下的整数的和的差最小
#if 0
int arr[] = {12, 6, 7, 11, 16, 3, 8, 4};
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;                     // 记录子集中选择的元素
vector<int> bestx;                 // 记录最优解
int sum = 0;                       // 记录子集中所选数字的和
int r = 0;                         // 记录未选择数字的和
unsigned int minval = 0xFFFFFFFF;  // 记录最小差值
int leftcnt = length;              // 记录未处理的数字的个数
int cnt = 0;                       // 记录遍历的子集的个数，用于测试
 
void func(int i) {
    if (i == length) {
        cnt++;
        if (x.size() != length / 2) {
            return;
        }

        int result = abs(sum - r);
        if (result < minval) {
            minval = result;
            bestx = x;
        }

    } else {
        leftcnt--;  // 表示处理i节点，表示剩余的未处理的元素的个数
        if (x.size() < length / 2) {
            r -= arr[i];
            sum += arr[i];
            x.push_back(arr[i]);
            func(i + 1);  // 遍历i的左孩子，表示选择i号位元素
            x.pop_back();
            r += arr[i];
            sum -= arr[i];
        }
        // 这里右树枝可不可以剪枝呢？
        // 已选择的数字的个数 + 未来能选择的所有的数字的个数(i+1,i+2....n) >= n个元素
        if (x.size() + leftcnt >= length / 2) {
            func(i + 1);  // 遍历i的右孩子，表示不选择i号位元素
        }
        leftcnt++;
    }
}

int main() {
    for (int i = 0; i < length; i++) {
        r += arr[i];
    }
    func(0);

    for (auto v : bestx) {
        cout << v << " ";
    }
    cout << endl;
    cout << "minval = " << minval << endl;
    cout << "cnt = " << cnt << endl;
}
#endif

// 挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
#if 0
int arr[] = {4, 8, 12, 16, 7, 9, 3};
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> x;  // 记录选择的数字
int sum = 0;    // 记录所选择数字的和
int r = 0;      // * 记录未处理的数字的和  不要混淆未处理和未选择

void func(int i) {
    if (i == length) {
        if (sum != number) {
            return;
        }
        for (auto v : x) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        r -= arr[i];  // 处理当前i节点
        // 剪左树枝   已选择的数字的和+即将要选择的数字
        if (sum + arr[i] <= number) {
            sum += arr[i];
            x.push_back(arr[i]);
            func(i + 1);
            sum -= arr[i];
            x.pop_back();
        }
        // 剪右树枝   已选择的数字的和+剩余的可以被选择的数字的和(i+1,i+2....n)
        if (sum + r >= number) {
            func(i + 1);
        }
        r += arr[i];
    }
}

int main() {
    for (int v : arr) {
        r += v;
    }
    func(0);
    return 0;
}

#endif

// 挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
#if 0

int arr[] = {4, 8, 12, 16, 7, 9, 3, 3};
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> vec;  // 存放选择的数字

void func(int i, int number) {
    if (number == 0) {
        for (int v : vec) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        // 以当前节点开始，把剩余元素的孩子节点生成
        for (int k = i; k < length; ++k) {
            // 剩余的元素小于number（待组成的元素值）
            if (number >= arr[k]) {
                // 如果数组里有重复的数据，需要先排序，然后判断
                // 当前层遍历到下一层的时候   arr[k] != arr[k-1]

                vec.push_back(arr[k]);
                // 不允许重复选择元素
                func(k + 1, number - arr[k]);  // 遍历孩子节点，arr[k]的孩子节点

                // 允许重复选择元素
                // func(k, number - arr[k]);
                vec.pop_back();
            }
        }
    }
}

int main() {
    func(0, number);
    return 0;
}
#endif

// 0-1背包问题：有一组物品，其重量分别是:w1,w2,...wn，其价值分别是v1,v2,...,vn，现在有一个背包，其容量是C，
// 问怎么把物品装入背包，能够使背包的价值最大化？
#if 0
int w[] = {12, 5, 8, 9, 6};  // 物品的重量
int v[] = {9, 2, 4, 7, 8};   // 物品的价值
const int length = sizeof(w) / sizeof(w[0]);
int c = 20;         // 背包的容量
int cw = 0;         // 已选择物品的重量
int cv = 0;         // 已选择物品的价值
int r = 0;          // 未选的物品的总价值
vector<int> x;      // 选择的物品
vector<int> bestx;  // 记录最优选择的物品
int bestv = 0;      // 记录装入背包的物品最大价值

void func(int i) {
    if (i == length) {
        if (cv > bestv) {
            bestv = cv;
            bestx = x;
        }
    } else {
        r -= v[i];
        // 已选择物品的重量 + 即将选择的第i号物品的重量
        if (cw + w[i] <= c) {
            cv += v[i];
            cw += w[i];
            x.push_back(w[i]);
            func(i + 1);
            x.pop_back();
            cw -= w[i];
            cv -= v[i];
        }
        // bestv   cv + [i+1,i+2.....n]总价值 > bestv
        if (cv + r >= bestv) {
            func(i + 1);
        }
        r += v[i];
    }
}

int main() {
    for (auto va : v) {
        r += va;
    }
    func(0);

    for (int w : bestx) {
        cout << w << " ";
    }
    cout << endl;
    cout << "bestv:" << bestv << endl;
}

#endif

// 解空间----排列树代码
#if 0

void swap(int arr[], int i, int k) {
    int temp = arr[i];
    arr[i] = arr[k];
    arr[k] = temp;
}

void func(int arr[], int i, int length) {
    if (i == length) {
        for (int j = 0; j < length; ++j) {
            cout << arr[j] << " ";
        }
        cout << endl;
    } else {
        // 生成i节点的所有孩子节点
        for (int k = i; k < length; k++) {
            swap(arr, i, k);
            func(arr, i + 1, length);
            swap(arr, i, k);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int length = sizeof(arr) / sizeof(arr[0]);
    func(arr, 0, length);
}

#endif

// 8皇后的排列次数
#if 0
/**
 在8×8 的国际象棋棋盘上，放置8个皇后，要求它们不能互相攻击。
皇后（Queen） 在国际象棋中可以 横、竖、斜 任意方向移动，因此：
✅ 同一行不能有两个皇后
✅ 同一列不能有两个皇后
✅ 同一对角线（左上 ↘ 右下、左下 ↗ 右上）不能有两个皇后
比如：int ar[] = {1, 3, 5, 7, 2, 0, 6, 4};
. Q . . . . . .  // 第 0 行，第 1 列放皇后
. . . Q . . . .  // 第 1 行，第 3 列放皇后
. . . . . Q . .  // 第 2 行，第 5 列放皇后
. . . . . . . Q  // 第 3 行，第 7 列放皇后
. . Q . . . . .  // 第 4 行，第 2 列放皇后
Q . . . . . . .  // 第 5 行，第 0 列放皇后
. . . . . . Q .  // 第 6 行，第 6 列放皇后
. . . . Q . . .  // 第 7 行，第 4 列放皇后
 */
int cnt = 0;  // 统计8皇后的排列次数
void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
// i表示当前放置皇后棋子的位置
bool judge(int ar[], int i) {
    for (int j = 0; j < i; j++) {
        //
        if (i == j || ar[i] == ar[j] || abs(i - j) == abs(ar[i] - ar[j])) {
            return false;
        }
    }
    return true;
}

void func(int arr[], int i, int length) {
    if (i == length) {
        cnt++;
        for (int j = 0; j < length; ++j) {
            cout << arr[j] << " ";
        }
        cout << endl;
    } else {
        for (int k = i; k < length; k++) {
            swap(arr, i, k);
            // 判断第i个位置的元素，是否满足8皇后的条件   0 - i-1
            if (judge(arr, i)) {
                // 生成孩子节点，也就是说会生成一系列的排列方式
                func(arr, i + 1, length);
            }
            swap(arr, i, k);
        }
    }
}

int main() {
    // 把ar数组的下标当作行，下标对应的元素的值当作列
    int ar[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;
    func(ar, 0, n);
    cout << "cnt:" << cnt << endl;
    return 0;
}

#endif

// 一种实现全排列的代码   满足leetcode刷题测试用例
#if 1
int ar[] = {1, 2, 3};
const int N = 3;
bool state[N];  // 记录所有元素是否被选择的状态  true：选择了  false：未选择
vector<int> vec;
void func(int i) {
    if (i == N) {
        for (int v : vec) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        for (int k = 0; k < N; k++) {
            if (!state[k]) {
                state[k] = true;
                vec.push_back(ar[k]);
                func(i + 1);  // k：表示的是可选择的元素的起始下标     i：表示层数
                vec.pop_back();
                state[k] = false;
            }
        }
    }
}
int main() {
    func(0);
    return 0;
}
#endif