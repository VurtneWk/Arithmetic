#include <iostream>

using namespace std;

// 二分搜索非递归实现
#if 0 
int binarySearch(int arr[], int size, int val) {
    int first = 0;
    int last = size - 1;
    // * 注意条件判断
    while (first <= last) {
        int middle = (first + last) / 2;
        if (arr[middle] == val) {
            return middle;
        } else if (arr[middle] > val) {  // 值在左边
            last = middle - 1;
        } else {
            first = middle + 1;
        }
    }
    return -1;
}
#endif

/**
 * 在 arr 数组的 [start,end] 索引范围内查找值val
 * @param arr[] 数组
 * @param start 开始索引
 * @param end 结束索引
 * @param val 要查找的值
 *
 * * 这个函数必须在前面先声明/定义 ， 才能在下面的方法中使用
 */
int binarySearch(int arr[], int start, int end, int val) {
    // 递归结束条件
    if (start > end) {
        return -1;
    }
    int mid = (start + end) / 2;
    if (arr[mid] == val) {
        return mid;
    } else if (arr[mid] > val) {
        return binarySearch(arr, start, mid - 1, val);
    } else {
        return binarySearch(arr, mid + 1, end, val);
    }
}

// 二分搜索递归代码
int binarySearch(int arr[], int size, int val) { return binarySearch(arr, 0, size - 1, val); }

// 测试 二分搜索
int main() {
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << binarySearch(arr, size, 39) << endl;
    cout << binarySearch(arr, size, 45) << endl;
    cout << binarySearch(arr, size, 96) << endl;
    cout << binarySearch(arr, size, 64) << endl;
}
