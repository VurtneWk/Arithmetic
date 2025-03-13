/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

#include <istream>

using namespace std;
/**
 * 思路 两个栈s1 s2
 * s1 用于存放push的数据
 * s2 用于存放pop、top时的数据
 * s2 是空时才把数据从s1放到s2
 */
// @lc code=start
class MyQueue {
   public:
    MyQueue() {}

    void push(int x) { s1.push(x); }

    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int val = s2.top();
        s2.pop();
        return val;
    }

    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }

    bool empty() { return s1.empty() && s2.empty(); }

   private:
    stack<int> s1;
    stack<int> s2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end
