/**
 * @file 06.01背包.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

/*
0-1背包问题：有一组物品，其重量为
w1,w2,...,wn，其价值为
v1,v2,...,vn，现在有一个背包，其容量是c，问怎么样装入物品，可以使背包的价值最大化？

wn -> c
wn-1 -> c-wn

两个要素：
1.最优子结构性质
2.划分的子问题非独立（有重叠）

状态（描述子问题最优解的性质）：   重量、价值、背包的容量
dp(i，j)：所选的物品范围在i,...,n，背包的容量是j，背包所容纳物品的最大价值

状态转移方程（由子问题的最优解如何合并出原问题的最优解）：
i == n : 只考虑一个物品，就是wn
wn > j : 说明第n个物品无法装入背包的
dp[n][j] = 0
wn <= j：说明第n个物品可以装入背包
dp[n][j] = vn

备注：n -》 n-1,n -> n-2,n-1,n

i,i+1,i+2,...n是可选的物品
wi > j ：说明第i个物品无法装入背包中
dp[i][j] = dp[i+1][j]
wi <= j ： 说明第i个物品能够装入背包   装入物品i，不装入物品i（取最大价值）
dp[i][j] = max{dp[i+1][j],   vi + dp[i+1][j-wi]}

No        1 2 3 4 5 6 7  8  9   10 11 12    c=12
1(8,6)		0 8 8 8 8 8 15 15 15 15 21 21   no
2(6,4)		0 8 8 8 8 8 15 15 15 15 21 21   no
3(4,7)		0 8 8 8 8 8 15 15 15 15 21 21   yes 8
4(2,8)		0 8 8 8 8 8 14 14 14 14 14 14   yes 2 8-2 = 6
5(5,6)		0 0 0 0 6 6  6  6  6 6  6  6    yes
*/

void backStrace(int w[], int v[], int n, int c, int **dp) {
    int bestv = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i][c] != dp[i + 1][c]) {
            // 选择了第i个物品
            cout << w[i] << " ";
            bestv += v[i];
            c -= w[i];
        }
    }

    // 单独处理最后一行（也就是最后一个物品）
    if (dp[n][c] > 0) {
        bestv += v[n];
        cout << w[n] << " ";
    }

    cout << endl;
    cout << "背包的最大价值:" << bestv << endl;
}

int main() {
    int w[] = {8, 6, 4, 2, 5};             // 背包重量
    int v[] = {6, 4, 7, 8, 6};             // 背包价值
    int n = sizeof(w) / sizeof(w[0]) - 1;  // -1 目的是为了后面的公式和注释里一致
    int c = 12;                            // 最大容量
    int **dp = nullptr;                    // 定义dp数组记录子问题的解
    // dp 为 5行13列
    dp = new int *[n + 1];
    for (int i = 0; i < n + 1; i++) {
        dp[i] = new int[c + 1]();  // dp数组的元素内容全部初始化为0
    }
    // 先填写初始状态的值    填写dp二维数组的最后一行   物品n
    for (int j = 1; j <= c; j++) {  // 物品价值至少是1
        if (w[n] > j) {             // 第n个物品的重量 大于 背包剩余容量
            dp[n][j] = 0;           // 放不下了
        } else {                    // 第n个物品的重量  小于等于  背包的剩余容量
            dp[n][j] = v[n];
        }
    }
    // 从n-1 =》 0 行开始 表示所选择的物品是i, i+1, ..., n
    for (int i = n - 1; i >= 0; i--) {  // O(n) * O(c) = O(n*c) = O(n)
        for (int j = 1; j <= c; j++) {
            if (w[i] > j) {               // 第i个物品无法装入背包
                dp[i][j] = dp[i + 1][j];  // 无法放入，容量不变
            } else {
                // 否则，分为放入和不放入两种情况
                // 取两者的最大价值
                // dp[i + 1][j] 不考虑放入自己的情况
                // v[i] + dp[i + 1][j - w[i]] 自己的价值 + 上一个商品在剩余容量下的价值
                dp[i][j] = max(dp[i + 1][j], v[i] + dp[i + 1][j - w[i]]);
            }
        }
    }

    // 便于理解问题，打印dp数组
    /* for (int i = 0; i <= n; ++i) {
         for (int j = 1; j <= c; ++j) {
             cout << dp[i][j] << " ";
         }
         cout << endl;
     }*/

    backStrace(w, v, n, c, dp);

    // 释放dp数组的内存
    for (int i = 0; i < n + 1; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}