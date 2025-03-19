/**
 * @file 24_大数据TopK-快排分割.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

// 快排分割函数
int partation(int arr[], int begin, int end) {
    int val = arr[begin];
    int i = begin;
    int j = end;
    while (i < j) {
        // 在右边找比 基准值大的值
        // * 找最大值最小值 ， 只需要更改这里即可
        while (i < j && arr[j] > val) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j];
            i++;
        }
        // * 找最大值最小值 ， 只需要更改这里即可
        while (i < j && arr[i] < val) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = val;
    return i;  // 基准值的索引
}

// 求top k的函数
void selectTopK(int arr[], int begin, int end, int k) {
    int pos = partation(arr, begin, end);
    if (pos == k - 1) {  // 如果 基准数索引 是要找的前k项，就返回
        return;
    } else if (pos > k - 1) {
        // 只需要左边找
        selectTopK(arr, begin, pos - 1, k);
    } else {
        // 右边找
        selectTopK(arr, pos + 1, end, k);
    }
}

int main() {
    int arr[] = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    int size = sizeof arr / sizeof arr[0];

    // 求值最小的前3个元素
    int k = 7;
    selectTopK(arr, 0, size - 1, k);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < k; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}