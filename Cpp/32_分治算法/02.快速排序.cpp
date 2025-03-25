#include <algorithm>
#include <iostream>
#include <vector>
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

void swap(vector<int> &vec, int i, int j) {
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

/**
 * @param
 * @return  快排基准数索引
 */
int partation(vector<int> &vec, int i, int j) {
    // 避免基准数的值太小，可以使用三数取中 把中间值放到最左边
    int mid = (i + j) / 2;
    int pos = medianOfThree(vec, i, mid, j);
    swap(vec, i, pos);
    // 开始放基准数
    int val = vec[i];
    int left = i;
    int right = j;
    while (left < right) {
        while (left < right && val <= vec[right]) {
            right--;
        }
        if (left < right) {
            vec[left++] = vec[right];
        }
        while (left < right && val >= vec[left]) {
            left++;
        }
        if (left < right) {
            vec[right--] = vec[left];
        }
    }
    vec[left] = val;
    return left;
}

void quickSort(vector<int> &vec, int i, int j) {
    if (i >= j) {
        return;
    }
    int pos = partation(vec, i, j);
    quickSort(vec, i, pos - 1);
    quickSort(vec, pos + 1, j);
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
    quickSort(vec, 0, vec.size() - 1);
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;
}