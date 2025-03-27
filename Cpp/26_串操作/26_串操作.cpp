/**
 * @file 26_串操作.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

// BF算法 Brute Force（暴力算法），即暴力枚举法
// 时间复杂度：O(n)*O(m) =  O(n*m)   空间复杂度： O(1)
int BF(string s, string t) {
    int i = 0;
    int j = 0;
    while (i < s.size() && j < t.size()) {  // O(n)
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;  // 复位i，指向之前开始匹配字符的下一个字符  O(m)
            j = 0;
        }
    }
    if (j == t.size()) {  // 找到了
        return i - j;
    } else {
        return -1;
    }
}

// KMP算法  时间复杂度：O(n) + O(m) = O(n+m)  空间复杂度：O(m)

// KMP算法求解子串的next数组
int* getNext(string str) {
    int* next = new int[str.size()];
    int j = 0;    // j用来遍历子串
    int k = -1;   // k表示公共前后缀的长度
    next[j] = k;  // next 0 : -1
    while (j < str.size() - 1) {
        if (k == -1 || str[k] == str[j]) {
            j++;
            k++;
            // kmp算法的优化
            if (str[k] == str[j]) {
                next[j] = next[k];
            } else {
                next[j] = k;
            }
        } else {
            // 子串没遇到相同的字母之前，k实际一直为0
            // 遇到相同字母之后同时 k++和j++
            k = next[k];  // 做k值回溯，继续找最长的公共前后缀
        }
    }
    return next;
}

// 名称来源于三位发明 者：Knuth、Morris 和 Pratt（因此缩写为 KMP）

int KMP(string s, string t) {
    int i = 0;
    int j = 0;

    // 计算一个子串对应的next数组
    int* next = getNext(t);
    unique_ptr<int> ptr(next);  // delete操作

    cout << t << " : ";
    for (int m = 0; m < t.size(); m++) {
        cout << next[m] << " ";
    }
    cout << endl;

    // j < t.size() 有问题！！！ j = -1 11111111111  size_t  unsigned int
    int size1 = s.size();
    int size2 = t.size();
    while (i < size1 && j < size2) {  // O(n)
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            // KMP的核心是不回退i，只回退j值
            j = next[j];  // 如果首字母匹配失败，这里j == -1

            // i = i - j + 1;  // 复位i，指向之前开始匹配字符的下一个字符  O(m)
            // j = 0;
        }
    }
    if (j == t.size()) {  // 找到了
        return i - j;
    } else {
        return -1;
    }
}

int main() {
    string s = "abcabdefabcabc";  //"ABCDCABDEFG";
    string t = "abcabc";          //"ABD";
    // string s = "ABaaCDCABDEFG";
    // string t = "ABD";

    int pos = KMP(s, t);
    cout << pos << endl;
}