/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* temp = head;
        int nextAdd = 0;
        while (l1 != nullptr || l2 != nullptr) {
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;

            int result = val1 + val2 + nextAdd;
            int currentVal = result % 10;
            nextAdd = result / 10;

            // 创建新节点
            if (head == nullptr) {
                head = new ListNode(currentVal);
                temp = head;
            } else {
                temp->next = new ListNode(currentVal);
                temp = temp->next;
            }

            // 移动指针
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        if (nextAdd != 0) {
            temp->next = new ListNode(nextAdd);
        }
        return head;
    }
};
// @lc code=end
