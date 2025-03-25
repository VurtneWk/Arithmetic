/**
 * @file 12_快速排序.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

// **三数取中法  注意：数大相乘可能溢出**
int medianOfThree(int arr[], int left, int mid, int right) {
    if ((arr[left] - arr[mid]) * (arr[right] - arr[left]) >= 0)
        return left;
    else if ((arr[mid] - arr[left]) * (arr[right] - arr[mid]) >= 0)
        return mid;
    else
        return right;
}

// 快排分割处理函数
int partation(int arr[], int l, int r) {
    int val = arr[l];  // 左边第一个数作为基准数
    // O(n) * O(logn) = O(nlogn)
    // 空间复杂度：没有开辟别的空间，但是因为递归： O(logn) 递归的深度占用的内存
    while (l < r) {  // 左值 要小于 右值
        // 在右边找比 基准数小的值，如果大于基准数则移动比较下一位
        while (l < r && arr[r] > val) {
            r--;
        }
        // 找到比基准数小的值后，把这个值放到基准数的位置
        if (l < r) {
            arr[l] = arr[r];
            l++;
        }
        // 切换方向查找
        // 在左边找比基准数大的值
        while (l < r && arr[l] < val) {
            l++;
        }
        // 找到之后把值放到r的位置
        if (l < r) {
            arr[r] = arr[l];
            r--;
        }
    }
    // l == r的位置，就是放基准数的位置
    arr[l] = val;
    return l;
}
// 递归进行快速排序 （分治法）
void quickSort(int arr[], int begin, int end) {
    // 结束条件
    if (begin >= end) {
        return;
    }
    // * 优化一：当[begin, end]序列的元素个数小到指定数量，采用插入排序
    // if (end - begin <= 50)
    //{
    // InsertSort(arr, begin, end);
    // return;
    //}

    // *三数取中优化：选出 left, mid, right 三个值的中位数作为 pivot
    // int mid = begin + (end - begin) / 2;
    // int pivotIndex = medianOfThree(arr, begin, mid, end);
    // swap(arr, begin, pivotIndex);  // 把 pivot 放到 `arr[begin]`

    // 在[begin, end]区间的元素做一次快排分割处理
    int position = partation(arr, begin, end);  // 目的是找放基准数的位置
    // 对基准数的左边和右边的序列，再分别进行快排
    quickSort(arr, begin, position - 1);
    quickSort(arr, position + 1, end);
}
//
void quickSort(int arr[], int size) { quickSort(arr, 0, size - 1); }

int main() {
    int arr[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;

    quickSort(arr, 10);

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}