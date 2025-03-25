/**
 * @file 03.最大子段和.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

/*
最大子段和
状态：dp[i] 以第i个元素结尾的字段和的值
状态转移方程：
dp[0] = val < 0 ? 0 : val;  0
dp[1] = ar[1] + dp[0] = 11
dp[2] = ar[2] + dp[1] = -4 + 11 = 7
dp[3] = ar[3] + dp[2] = 13 + 7 = 20
...
dp[i] = ar[i] + dp[i-1]   i > 0  i==0子段和认为是已知的
*/

int main() {
    int ar[] = {-2, 11, -4, 13, -5, -2};
    const int n = sizeof(ar) / sizeof(ar[0]);
    int dp[n] = {0};  // 状态
    dp[0] = ar[0] < 0 ? 0 : ar[0];
    int maxVal = dp[0];
    // O(n)
    for (int i = 1; i < n; i++) {
        // 状态转移方程   子问题的最优解 =》 原问题的最优解
        dp[i] = ar[i] + dp[i - 1];
        if (dp[i] < 0) {
            dp[i] = 0;
        }
        if (maxVal < dp[i]) {
            maxVal = dp[i];
        }
    }
    cout << maxVal << endl;
    return 0;
}