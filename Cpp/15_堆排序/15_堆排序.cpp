/**
 * @file 15_堆排序.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

// 堆的下沉调整
void siftDown(int arr[], int i, int size) {
    //
    int val = arr[i];
    while (i < size / 2) {
        int child = 2 * i + 1;
        if (child + 1 < size && arr[child + 1] > arr[child]) {
            child = child + 1;
        }
        if (arr[child] > val) {
            arr[i] = arr[child];
            // i继续指向它的孩子，继续调整
            i = child;
        } else {
            break;
        }
    }
    arr[i] = val;
}

// 堆排序
/**
 * 1. 从第一个非叶子节点 (n-1)/2 开始 ， 把二叉堆调整成一个大根堆。
 *    也就是从 (n-1)/2 号位元素开始到堆元素(0)，进行下沉操作。
 * 2. 循环：把堆顶元素和末尾元素进行交换，从0号位开始继续进行堆的下沉。这是就不用考虑最后一个元素
 *    每次循环就少考虑一个元素。
 *
 */
void heapSort(int arr[], int size) {
    // 末尾节点下标
    int n = size - 1;
    // 从第一个非叶子节点
    for (int i = (n - 1) / 2; i >= 0; i--) {
        siftDown(arr, i, size);
    }
    // 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
    for (int i = n; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        // 第三个参数，参与调整的元素的个数
        siftDown(arr, 0, i);
    }
}

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

    heapSort(arr, 10);

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}