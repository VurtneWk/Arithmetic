/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第 N 个结点
 */

struct ListNode {
    int val;
    struct ListNode* next;
};

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // 函数内部给链表加一个头
    struct ListNode head_;
    head_.next = head;

    struct ListNode* p = &head_;
    struct ListNode* q = &head_;
    // p 指针先前进n步
    for (int i = 0; i < n; i++) {
        if (p == NULL) {
            return head;
        }
        p = p->next;
    }
    // p和q 开始同时移动，p的下一个位置是null时，q就正好时倒数的n+1位
    while (p->next != NULL) {
        q = q->next;
        p = p->next;
    }
    // 缓存 倒数第N位的数据
    struct ListNode* del = q->next;
    // n+1位的指针 指向 n-1位的数据
    q->next = q->next->next;
    free(del);  // 删除倒数n位的数据
    return head_.next;
}
// @lc code=end
