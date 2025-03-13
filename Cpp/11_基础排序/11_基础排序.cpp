
/**
 * @file 11_基础排序.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

/**
 * 冒泡排序
 */
void bubbleSort(int arr[], int size) {
    // 趟数   最后一趟只剩下 1个元素，所以 size - 1
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;  // 用于优化，防止已排序的数组继续遍历
        // 每一趟的处理 每趟要比上一趟少处理一个数
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int arr[10];
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }

    for (auto &&i : arr) {
        cout << i << " ";
    }
    cout << endl;

    bubbleSort(arr, 10);
    for (auto &&i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}