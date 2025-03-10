/*
 * @lc app=leetcode.cn id=61 lang=cpp
 *
 * [61] 旋转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr) {
            return head;
        }
        ListNode* p = head;
        ListNode* q = head;
        int number = 0;
        // 求链表的长度，因为k的长度可能大于链表长度  O(n)
        for (ListNode* k = head; k != nullptr; k = k->next) {
            number++;
        }
        k = k % number;

        // p 正着数移动k位
        for (int i = 0; i < k; i++) {
            p = p->next;
        }
        // 同时移动p、q，直到p到达末尾
        // 这是q 指向 k + 1 位
        while (p->next != nullptr) {
            p = p->next;
            q = q->next;
        }
        // 末尾的节点指向之前的head
        p->next = head;
        // 原来的head 指向k-1
        head = q->next;
        q->next = nullptr;
        return head;
    }
};
// @lc code=end
