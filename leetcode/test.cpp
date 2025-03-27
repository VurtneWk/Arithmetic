

#include <iostream>
using namespace std;

int lengthOfLongestSubstring(string s) {
    if (s.size() == 1) {
        return 1;
    } else if (s.size() == 0) {
        return 0;
    } else {
        int i = 0;
        int j = 1;
        int max = 1;
        int curMax = 1;
        while (i < s.size() && j < s.size()) {
            if (s[i] != s[j]) {
                curMax++;
                j++;
            } else {
                if (max < curMax) {
                    max = curMax;
                }
                curMax = 0;
                i = j;
                j++;
            }
        }
        return max;
    }
}
int main() {
    int val = lengthOfLongestSubstring("pwwkew");
    cout << val << endl;
}