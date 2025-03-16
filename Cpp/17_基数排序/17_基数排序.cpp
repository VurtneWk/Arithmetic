#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 基数排序
// 时间复杂度： O(nd)
// 空间复杂度： O(n)
// 稳定性： 稳定
void radixSort(int arr[], int size) {
    int maxData = arr[0];
    // O(n)
    for (int i = 0; i < size; i++) {
        if (maxData < abs(arr[i])) {
            maxData = abs(arr[i]);
        }
    }
    int len = to_string(maxData).size();
    vector<vector<int>> vecs;
    int mod = 10, dev = 1;
    // O(d) d:数据长度
    for (int i = 0; i < len; i++, mod *= 10, dev *= 10) {
        // 20个桶，为了能处理负数 -9 ~ 9
        vecs.resize(20);
        // O(n)
        for (int j = 0; j < size; j++) {
            int index = arr[j] % mod / dev + 10;
            vecs[index].push_back(arr[j]);
        }
        int index = 0;
        // O(20)
        for (auto vec : vecs) {
            // O(n)     O(20)*O(n) = O(20n)==> O(n)
            for (auto v : vec) {
                arr[index++] = v;
            }
        }
        vecs.clear();
    }
}

int main() {
    int arr[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }

    arr[9] = -123;
    arr[6] = -38;

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;

    radixSort(arr, 10);

    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}
