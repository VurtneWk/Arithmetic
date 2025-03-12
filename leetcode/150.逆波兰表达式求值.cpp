/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */
#include <iostream>

// @lc code=start

using namespace std;

class Solution {
   public:
    int calc(int left, int right, char sign) {
        switch (sign) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
        }
        throw "error";
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> _stack;

        for (auto&& str : tokens) {
            // 只有加减乘除 ，（因为可能是负数 所以要判断长度）
            if (str.size() == 1 && (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')) {
                // 遇到运算符
                int right = _stack.top();
                _stack.pop();

                int left = _stack.top();
                _stack.pop();

                int result = calc(left, right, str[0]);
                _stack.push(result);
            } else {
                // 遇到数字
                _stack.push(stoi(str));
            }
        }
        int result = _stack.top();
        _stack.pop();
        return result;
    }
};
// @lc code=end
