/*
 * @lc app=leetcode.cn id=27 lang=c
 *
 * [27] 移除元素
 */

// @lc code=start
int removeElement(int* nums, int numsSize, int val) {
      int* p = nums;
      int* q = nums + numsSize - 1;
      while (p <= q) {
            // q 找不等于val的元素
            if (*q == val) {
                  q--;
                  continue;
            }
            if (*p == val) {
                  *p = *q;
                  q--;
            }
            p++;
      }
      return p - nums;
}
// @lc code=end
