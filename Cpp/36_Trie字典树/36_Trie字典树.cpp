/**
 * @file 36_Trie字典树.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
#include <map>
using namespace std;

class TrieTree {
   public:
    TrieTree() { root_ = new TrieNode('\0', 0); }
    ~TrieTree() {
        queue<TrieNode*> que;
        que.push(root_);
        while (!que.empty()) {
            TrieNode* front = que.front();
            que.pop();
            // 把当前节点的孩子节点全部入队列
            for (auto& pair : front->nodeMap_) {
                que.push(pair.second);
            }
            delete front;  // 释放当前节点资源
        }
    }
    // 添加单词
    void add(const string& word) {
        TrieNode* cur = root_;
        for (int i = 0; i < word.size(); i++) {
            auto childIt = cur->nodeMap_.find(word[i]);
            if (childIt == cur->nodeMap_.end()) {  // 相应字符的节点没有，创建它
                TrieNode* child = new TrieNode(word[i], 0);
                cur->nodeMap_.emplace(word[i], child);
                cur = child;
            } else {  // 相应的字符节点已经存在，移动cur指向对应的字符节点
                cur = childIt->second;
            }
        }
        cur->freqs_++;  // cur指向了word单词的最后一个节点
    }

    // 删除单词
    void remove(const string& word) {
        TrieNode* cur = root_;
        TrieNode* del = root_;  // 从哪个节点开始删除
        char delch = word[0];
        for (int i = 0; i < word.size(); i++) {
            auto childIt = cur->nodeMap_.find(word[i]);
            // 没找到单词 直接退出
            if (childIt == cur->nodeMap_.end()) {
                return;
            }
            // cur->freqs_ > 0 该字符可能是别的某个单词的结尾
            // cur->nodeMap_.size() > 1 该字符之前是和别的单词公共前缀
            if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1) {
                del = cur;
                // 是在nodeMap_里找字符，所以这里指向的字符 是下一个了
                delch = word[i];
            }
            cur = childIt->second;
        }
        // cur指向了末尾字符节点；word单词是存在的
        // 这是最后一个字符
        if (cur->nodeMap_.empty()) {
            // 开始删除
            TrieNode* child = del->nodeMap_[delch];
            del->nodeMap_.erase(delch);
            // 释放相应的节点内存
            queue<TrieNode*> que;
            que.push(child);
            while (!que.empty()) {
                TrieNode* front = que.front();
                que.pop();
                // 把当前节点的孩子节点全部入队列
                for (auto& pair : front->nodeMap_) {
                    que.push(pair.second);
                }
                // 释放当前节点资源
                delete front;
            }
        } else {
            // 准备删除的字符 后续还有别的单词
            // 比如 po ，pool ，然后准备删除po
            cur->freqs_ = 0;
        }
    }

    // 查询单词
    int query(const string& word) {
        TrieNode* cur = root_;
        for (int i = 0; i < word.size(); i++) {
            auto it = cur->nodeMap_.find(word[i]);
            if (it == cur->nodeMap_.end()) {
                return 0;
            } else {
                cur = it->second;  // 移动cur指向下一个单词的字符节点上
            }
        }
        return cur->freqs_;
    }

    // 前序遍历字典树
    void preOrder() {
        string word;
        vector<string> wordList;
        preOrder(root_, word, wordList);
        for (auto word : wordList) {
            cout << word << endl;
        }
        cout << endl;
    }

    // 串的前缀搜索
    vector<string> queryPrefix(const string& prefix) {
        TrieNode* cur = root_;
        for (int i = 0; i < prefix.size(); i++) {
            auto childIt = cur->nodeMap_.find(prefix[i]);
            if (childIt == cur->nodeMap_.end()) {
                return {};
            }
            cur = childIt->second;
        }
        // cur就指向了前缀的最后一个字符节点了
        vector<string> wordlist;
        preOrder(cur, prefix.substr(0, prefix.size() - 1), wordlist);
        return wordlist;
    }

   private:
    struct TrieNode {
        TrieNode(char ch, int freqs) : ch_(ch), freqs_(freqs) {}
        char ch_;                       // 节点存储的字符数据
        int freqs_;                     // 单词的末尾字符存储单词的数量(频率)
        map<char, TrieNode*> nodeMap_;  // 存储孩子节点字符数据和节点指针的对应关系
    };

    void preOrder(TrieNode* cur, string word, vector<string>& wordlist) {
        // 前序遍历 VLR
        if (cur != root_) {
            word.push_back(cur->ch_);
            if (cur->freqs_ > 0) {
                // 已经遍历到一个有效的单词
                wordlist.emplace_back(word);
            }
        }
        // 递归处理孩子节点
        for (auto pair : cur->nodeMap_) {
            preOrder(pair.second, word, wordlist);
        }
    }

    TrieNode* root_;  // 指向树的根节点
};

int main() {
    TrieTree trie;
    trie.add("hello");
    trie.add("hello");
    trie.add("helloo");
    trie.add("hel");
    trie.add("hel");
    trie.add("hel");
    trie.add("china");
    trie.add("ch");
    trie.add("ch");
    trie.add("heword");
    trie.add("hellw");

    cout << trie.query("hello") << endl;
    cout << trie.query("helloo") << endl;
    cout << trie.query("hel") << endl;
    cout << trie.query("china") << endl;
    cout << trie.query("ch") << endl;

    cout << "=====================" << endl;
    trie.preOrder();
    cout << "=====================" << endl;

    vector<string> words = trie.queryPrefix("he");
    for (auto word : words) {
        cout << word << endl;
    }
    cout << endl;

    trie.remove("hellw");
    cout << "=====================" << endl;
    trie.preOrder();
}