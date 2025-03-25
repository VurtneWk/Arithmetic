/**
 * @file 02.斐波那契数列.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

/*
                           func1(5)   参数：指定个数的斐波那契数列   前两个数字了  1  1
            func1(4)                   func1(3)
         func1(3)   func1(2)          func1(2)  func1(1)
         怎么描述子问题最优解的性质 《=》 问题的状态
         dp[i]:斐波那契数列中第i个数字的值
*/

#if 0

int cnt = 0;
int fibonacci(int n, int dp[]) {
    if (dp[n] > 0) {
        cnt++;
        return dp[n];
    }
    if (n == 1 || n == 2) {
        dp[n] = 1;
        return 1;
    } else {
        dp[n] = fibonacci(n - 1, dp) + fibonacci(n - 2, dp);
        return dp[n];
    }
}

int main() {
    const int n = 10;
    int* dp = new int[n + 1]();
    int number = fibonacci(10, dp);
    cout << number << endl;
    cout << cnt << endl;
    return 0;
}

#endif

/*
fibonacci
状态： dp[i] 斐波那契数列中第i个数字的值
状态的转移方程了:
dp[1] = 1
dp[2] = 1
dp[3] = dp[3-1] + dp[3-2] = dp[2] + dp[1] = 2
dp[i] = dp[i-1] + dp[i-2]  条件：i > 2
*/
int main() {
    const int n = 5;
    int dp[n + 1] = {0};
    dp[1] = dp[2] = 1;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n] << endl;
}

int fibonacci(int n) {
    int a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}