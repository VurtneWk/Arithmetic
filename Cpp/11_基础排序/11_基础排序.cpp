
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

/**
 * 选择排序
 */
void choiceSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // 记录最小值索引
        int index = i;
        // 每次是从记录的元素的下一个开始
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[index]) {
                index = j;
            }
        }
        // 如果找到和一开始记录的最小值不一样，则进行交换
        if (index != i) {
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }
}

/**
 * 插入排序
 */
void insertSort(int arr[], int size) {
    // 从第一个开始
    for (int i = 1; i < size; i++) {
        int val = arr[i];  // 要比较的值
        int j = i - 1;
        // 和前面的进行比较
        while (j >= 0 && arr[j] > val) {
            arr[j + 1] = arr[j];  // 如果前面的值大于当前值，后移
            j--;
        }
        arr[j + 1] = val;  // 找到位置后插入
    }
}

/**
 * 希尔排序
 */
void shellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap = gap / 2) {
        // 从第一个开始
        for (int i = gap; i < size; i++) {
            int val = arr[i];  // 要比较的值
            int j = i - gap;
            // 和前面的进行比较
            while (j >= 0 && arr[j] > val) {
                arr[j + gap] = arr[j];  // 如果前面的值大于当前值，后移
                j -= gap;
            }
            arr[j + gap] = val;  // 找到位置后插入
        }
    }
}

#if 0
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

    shellSort(arr, 10);
    for (auto &&i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
#endif

int main() {
    const int COUNT = 100000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    int* drr = new int[COUNT];

    srand(time(NULL));

    for (int i = 0; i < COUNT; i++) {
        int val = rand() % COUNT;
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
        drr[i] = val;
    }

    clock_t begin, end;

    begin = clock();
    bubbleSort(arr, COUNT);
    end = clock();
    cout << "BubbleSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    choiceSort(brr, COUNT);
    end = clock();
    cout << "ChoiceSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    insertSort(crr, COUNT);
    end = clock();
    cout << "InsertSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    shellSort(drr, COUNT);
    end = clock();
    cout << "ShellSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
}