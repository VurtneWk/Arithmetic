/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */
#include <iostream>
using namespace std;

// @lc code=start
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 1) {
            return 1;
        } else if (s.size() == 0) {
            return 0;
        } else {
            int i = 0;
            int j = 1;
            int max = 0;
            while (i < s.size() && j < s.size()) {
                if (s[i] == s[j]) {
                    max++;
                    j++;
                } else {
                                }
            }
        }
    }
};
// @lc code=end
