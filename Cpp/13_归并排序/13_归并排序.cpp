/**
 * @file 13_归并排序.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    // int* p = new int[r - l + 1];
    vector<int> p(r - l + 1);  // vector 可自动管理内存
    int index = 0, i = l, j = m + 1;
    // 比较两段的大小，合并到p数组中
    while (i <= m && j <= r) {
        // 左边的值更小
        if (arr[i] <= arr[j]) {
            p[index++] = arr[i++];
        } else {  // 右边的值更小
            p[index++] = arr[j++];
        }
    }
    // 左边 或者 右边没有之后就会退出上面的循环
    while (i <= m) {
        p[index++] = arr[i++];
    }
    while (j <= r) {
        p[index++] = arr[j++];
    }
    // 最后要把合并好的大段有序的结果，拷贝到原始的arr数组的[l,r]区间内
    // for (i = l, j = 0; i <= r; i++, j++) {
    //     arr[i] = p[j];
    // }
    for (int k = 0; k < p.size(); k++) {
        arr[l + k] = p[k];
    }

    // delete[] p;
}

void mergeSort(int arr[], int begin, int end) {
    // 递归结束条件
    if (begin >= end) return;
    // * 可以小规模优化：插入排序
    // if (end - begin <= 32) {
    //     insertionSort(arr, begin, end);
    //     return;
    // }

    // 递
    // 拆分数组，当拆分到 begin >= end 时会return
    // int mid = (begin + end) / 2; 下面这个可以避免 begin + end 溢出
    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    // 归并 [begin,mid] [mid+1,end] 把两个分小段有序的序列，合并成大段有序的序列
    merge(arr, begin, mid, end);
}

void mergeSort(int arr[], int size) { mergeSort(arr, 0, size - 1); }

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

    mergeSort(arr, 10);

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}