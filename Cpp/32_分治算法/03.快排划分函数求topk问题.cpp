/**
 * @file 03.快排划分函数求topk问题.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
using namespace std;

int medianOfThree(vector<int> &vec, int left, int mid, int right) {
    if ((vec[left] < vec[mid] && vec[mid] < vec[right]) || (vec[right] < vec[mid] && vec[mid] < vec[left])) {
        return mid;  // mid 是中位数
    } else if ((vec[mid] < vec[left] && vec[left] < vec[right]) || (vec[right] < vec[left] && vec[left] < vec[mid])) {
        return left;  // left 是中位数
    } else {
        return right;  // right 是中位数
    }
}
// 快排划分函数，调整基准数
static int partation(vector<int> &vec, int i, int j) {
    // 三数取中
    int midIndex = (i + j) / 2;
    int mid = medianOfThree(vec, i, midIndex, j);
    swap(vec[i], vec[mid]);

    int val = vec[i];
    int l = i;
    int r = j;
    while (l < r) {
        while (l < r && val <= vec[r]) {
            r--;
        }
        if (l < r) {
            vec[l++] = vec[r];
        }
        while (l < r && val >= vec[l]) {
            l++;
        }
        if (l < r) {
            vec[r--] = vec[l];
        }
    }
    vec[l] = val;
    return l;
}

// 和快排的主要区别就只是递归时的控制
// 找第k大的，  vec.size()-k 小的 下标
int max_select_topk(vector<int> &vec, int i, int j, int k) {
    // pos表示基准数的位置
    int pos = partation(vec, i, j);
    // 基准数的位置和top k的k值相等了
    if (vec.size() - k == pos) {
        return pos;
    } else if (vec.size() - k > pos) {  // topk应该在基准数的右边
        return max_select_topk(vec, pos + 1, j, k);
    } else {  // topk应该落在基准数的左边
        return max_select_topk(vec, i, pos - 1, k);
    }
}

int min_select_topk(vector<int> &vec, int i, int j, int k) {
    // pos表示基准数的位置
    int pos = partation(vec, i, j);
    if (pos == k - 1) {
        return pos;
    } else if (pos > k - 1) {
        return min_select_topk(vec, i, pos - 1, k);
    } else {
        return min_select_topk(vec, pos + 1, j, k);
    }
}

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100);
    }
    cout << "未排序前整个集合:";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // 求第top 10大的元素
    int pos = max_select_topk(vec, 0, vec.size() - 1, 4);

    // cout << "初步排序后整个集合:";
    // for (int i = 0; i < vec.size(); ++i) {
    //     cout << vec[i] << " ";
    // }
    // cout << endl;

    cout << "第topk大的:" << vec[pos] << endl;
    cout << "前topk大的:";
    for (int i = pos; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // // 找topl小的
    pos = min_select_topk(vec, 0, vec.size() - 1, 4);
    // cout << "初步排序后整个集合:";
    // for (int i = 0; i < vec.size(); ++i) {
    //     cout << vec[i] << " ";
    // }
    // cout << endl;
    cout << "第topk小的:" << vec[pos] << endl;
    cout << "前topk小的:";
    for (int i = 0; i <= pos; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    sort(vec.begin(), vec.end());
    for (int v : vec) {
        cout << v << " ";
    }

    cout << endl;
}