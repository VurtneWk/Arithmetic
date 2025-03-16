/**
 * @file 20_大数据查重.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
#include <unordered_set>
using namespace std;
#if 0
int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 10000; i++) {
        vec.push_back(rand() % 10000);
    }
    // 问题1
    // 找第一个出现重复的数字
    // 找所有重复出现的数字
    unordered_set<int> s1;  // unordered_set 对应java
    for (auto key : vec) {
        auto it = s1.find(key);  // O(1)
        if (it == s1.end()) {
            s1.insert(key);
        } else {
            cout << "key :" << key << endl;
            break;  // 所有的就去掉break
        }
    }
    // 问题2
    // 统计重复数字以及出现的次数
    unordered_map<int, int> m1;
    for (int key : vec) {
        // pair first second
        auto it = m1.find(key);  // O(1)   m1.find(key) 返回一个 iterator，指向 key 对应的键值对
        if (it == m1.end()) {
            m1.emplace(key, 1);
        } else {
            it->second += 1;  // it->first 表示键（key） t->second 表示值（value）
        }

        // m1[key]++; // 这个可以直接实现上面的功能
    }

    for (auto pair : m1) {
        if (pair.second > 1) {
            cout << "key:" << pair.first << " cnt:" << pair.second << endl;
        }
    }

    // 问题3
    // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
    unordered_set<int> s1;
    for (auto key : vec) {
        s1.emplace(key);
    }
}
#endif

int main() {
    string src = "jjhffiyuhrtytrs";
    // 找出来第一个没有重复出现过的字符
    unordered_map<int, int> m;
    for (auto ch : src) {
        m[ch]++;
    }
    for (char ch : src) {
        if (m[ch] == 1) {
            cout << "第一个没有重复出现过的字符是：" << ch << endl;
            return 0;
        }
    }
    cout << "所有字符都有重复出现过!" << endl;
    return 0;
}

/*
查重的面试相关问题

有两个文件分别是a和b，里面放了很多ip地址(url地址、email地址)，让你找出来两个文件重复的ip，输出出来

==> 把a文件中所有的ip存放在一个哈希表中，然后依次遍历文件b里面的ip，每
遍历一个ip，在哈希表中搜索一下，搜到的，即是两个文件重复的ip并输出
    用到了哈希表的查询O(1)

有两个文件分别是a和b，各自存放在约1亿条ip地址，每个ip地址是4个字节限制内存使用100M，让找出来两个文件中重复的ip地址并输出
==> 创建同等的 a1-an , b1-bn 个文件，
通过挨个读取a,b的地址取摸后放到对应的ax/bx文件，然后只需要对比两边同序号的文件即可。
*/