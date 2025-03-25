
/**
 * @file 04.归并排序.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

void merge(vector<int>& vec, int begin, int end, int mid) {
    // 定义额外的辅助空间，存储合并的子问题的有序数组
    vector<int> tmp;
    tmp.reserve(end - begin + 1);  // reserve resize
    int i = begin;
    int j = mid + 1;
    while (i <= mid && j <= end) {
        if (vec[i] < vec[j]) {
            tmp.push_back(vec[i++]);
        }
        if (vec[i] > vec[j]) {
            tmp.push_back(vec[j++]);
        }
    }
    while (i <= mid) {
        tmp.push_back(vec[i++]);
    }
    while (j <= end) {
        tmp.push_back(vec[j++]);
    }
    // 这里的vec 下标是直接他自己的下标
    // tmp 是从0开始
    for (int k = begin; k <= end; k++) {
        vec[k] = tmp[k - begin];
    }
}

void mergeSort(vector<int>& vec, int begin, int end) {
    // 子问题划分到一个元素的时候，就代表子问题的解是已知的了
    if (begin == end) {
        return;
    }
    int mid = (begin + end) / 2;
    // 先划分子问题，降低问题规模
    mergeSort(vec, begin, mid);
    mergeSort(vec, mid + 1, end);
    // 向上回溯，回溯的过程中，合并子问题的解
    merge(vec, begin, end, mid);
}

int main() {
    vector<int> vec;
    for (int i = 0; i < 11; ++i) {
        vec.push_back(rand() % 100);
    }

    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;

    mergeSort(vec, 0, vec.size() - 1);
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;
}