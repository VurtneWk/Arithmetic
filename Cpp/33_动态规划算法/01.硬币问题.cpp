/**
 * @file 01.硬币问题.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

/*
  硬币选择问题：有1，3，5分面额的硬币，给定一个面值11，问组成给定面值所需要的最少的硬币数量是多少？？？
11:    1 + (10)                                   3 + (8)                                5 + (6)
10:  1+(9)   3+(7)   5+(5)
                                           8:   1+(7)  3+(5)  5+(3)
                                                                                       6:   1+(5)  3+(3)  5+(1)

 */

const int n = 100;
int dp[n + 1] = {0};  // dp[n] : 组成价值n需要的硬币最少数量
int cnt = 0;          // 代码测试

/*
参数n表示面值， 返回值表示组成面值n所需要的最少的硬币数量
*/
int func1(int n) {
    if (dp[n] > 0) {  // dp[n]这个子问题已经被求解过了
        cnt++;
        return dp[n];
    }
    if (n == 1 || n == 3 || n == 5) {
        dp[n] = 1;  // 代表了一个子问题最优解的性质（状态）
        return 1;
    } else if (n == 2 || n == 4) {
        dp[n] = 2;
        return 2;
    } else {
        int n1 = func1(n - 1) + 1;  // 选择了1分硬币
        int n2 = func1(n - 3) + 1;  // 选择了3分硬币
        int n3 = func1(n - 5) + 1;  // 选择了5分硬币
        dp[n] = min({n1, n2, n3});
        return dp[n];
    }
}

int minCoins(int c) {
    vector<int> v = {1, 3, 5};

    // 只存储最近5个状态
    int prev1 = 0, prev2 = INT_MAX, prev3 = INT_MAX, prev4 = INT_MAX, prev5 = INT_MAX;

    int res = 0;
    for (int i = 1; i <= c; i++) {
        res = INT_MAX;
        for (int coin : v) {
            if (i >= coin) {
                int temp = INT_MAX;
                if (coin == 1)
                    temp = prev1;
                else if (coin == 3)
                    temp = prev3;
                else if (coin == 5)
                    temp = prev5;

                if (temp != INT_MAX) {
                    res = min(res, temp + 1);
                }
            }
        }

        // 滚动更新状态
        prev5 = prev4;
        prev4 = prev3;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = res;
    }
    return res;
}

int main() {
    // int num = func1(n);
    // cout << "num:" << num << endl;
    // cout << "cnt:" << cnt << endl;

    /*
问题的状态：dp[i] 组成面值i所需要的最少的硬币数量
状态转移方程：
dp[0] = 0
dp[1] = 1 + dp[1-1] = 1
dp[2] = 1 + dp[2-1] = 1 + dp[1] = 1 + 1 = 2
dp[3] :
           1 + dp[3-1] = 1 + dp[2] = 1 + 2 = 3    选择了3个1分硬币
           1 + dp[3-3] = 1 + dp[0] = 1  选择了1个3分硬币
dp[4]:
           1 + dp[4-1] = 1 + dp[3] = 1 + 1 = 2   1,3
           1 + dp[4-3] = 1 + dp[1] = 1 + 1 = 2   3,1
dp[5]:
           1 + dp[5-1] = 1 + dp[4] = 1 + 2 = 3
           1 + dp[5-3] = 1 + dp[2] = 1 + 2 = 3
           1 + dp[5-5] = 1 + dp[0] = 1  最优解   1个5分硬币

从上面的理论推导，得到下面的状态转移方程：
* dp[i] = min {1 + dp[i-vj]}   i表示面值   vj表示第j个硬币的面额 条件 i>=Vj
    */

    int v[] = {1, 3, 5};
    int length = sizeof(v) / sizeof(v[0]);
    int c = 100;
    int *dp = new int[c + 1]();  // dp[c]   dp[0] = 0
    for (int i = 1; i <= c; i++) {
        dp[i] = i;  // 表示初始全部由1分硬币组成 （最坏情况）
        // 遍历所有硬币面值 v[j]，尝试用 v[j] 更新 dp[i]
        for (int j = 0; j < length; j++) {
            // 判断条件 if (i >= v[j]) → 只有 i 至少等于 v[j] 才能使用 v[j] 硬币。
            // 计算 dp[i-v[j]]+1，如果比 dp[i] 小，就更新 dp[i]，保证最少硬币数量
            if (i >= v[j] && (1 + dp[i - v[j]]) < dp[i]) {
                dp[i] = 1 + dp[i - v[j]];  // 取最优解
            }
        }
    }
    cout << dp[c] << endl;
    delete[] dp;

    cout << "minCoins:" << minCoins(100) << endl;
}