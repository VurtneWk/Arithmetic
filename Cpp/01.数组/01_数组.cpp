// 01_数组.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <iostream>
using namespace std;

// leetcode：27

#if 0
/**
 * 可扩容数组实现
 */
class Array {
   public:
    Array(int size = 10) : mCur(0), mCapacity(size) { mpArr = new int[mCapacity](); }
    ~Array() {
        delete[] mpArr;
        mpArr = nullptr;
    }
    // 默认增加元素
    void push_back(int val) {
        if (mCur == mCapacity) {
            expand(2 * mCapacity);
        }
        mpArr[mCur++] = val;
    }
    // 末尾删除元素
    void pop_back() {
        if (mCur == 0) {
            return;
        }
        mCur--;
    }
    // 按位置增加元素
    void insert(int pos, int val) {
        if (pos < 0 || pos > mCur) {
            return;  // throw "pos invalid!"
        }
        if (mCur == mCapacity) {
            expand(2 * mCapacity);
        }
        // 移动元素
        for (int i = mCur - 1; i >= pos; i--) {
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++;
    }
    // 按元素删除
    void erase(int pos) {
        if (pos < 0 || pos > mCur) {
            return;
        }
        for (int i = pos + 1; i < mCur; i++) {
            mpArr[i - 1] = mpArr[i];
        }
        mCur--;
    }
    // 元素查询
    int find(int val) {
        for (int i = 0; i < mCur; i++) {
            if (mpArr[i] == val) {
                return i;
            }
        }
        return -1;
    }
    void show() const {
        for (int i = 0; i < mCur; i++) {
            cout << mpArr[i] << " ";
        }
        cout << endl;
    }

   private:
    int *mpArr;     // 指向 堆上 可扩容的内存
    int mCapacity;  // 数组的容量
    int mCur;       // 数组有效元素个数
    /**
     * 扩容
     */
    void expand(int size) {
        int *p = new int[size];
        //
        memcpy(p, mpArr, sizeof(int) * mCapacity);
        delete[] mpArr;
        mpArr = p;
        mCapacity = size;
    }
};

int main() {
    Array arr;
    // 初始化 C 语言的随机数种子 ， 确保 rand() 生成的随机数每次运行程序时不同
    // time(0)：返回当前的 UNIX 时间（从 1970 年 1 月 1 日到现在的秒数）
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100);
    }
    arr.show();

    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if (pos != -1) {
        arr.erase(pos);
        arr.show();
    }
}

#endif

#if 0
// 逆序字符串
void reverse(char arr[], int size) {
      cout << arr << "  " << size << endl;
      char* p = arr;
      char* q = arr + size - 1;
      while (p < q) {
            char ch = *p;
            *p = *q;
            *q = ch;
            p++;
            q--;
      }
}

int main() {
      char arr[] = "hello world";
      reverse(arr, strlen(arr));
      cout << arr << endl;
}
#endif

// 偶数到左边，奇数到右边
void adjustArray(int arr[], int size) {
      int* p = arr;
      int* q = arr + size - 1;
      while (p < q) {
            // p->奇数
            while (p < q) {
                  if ((*p & 0x1) == 1) {
                        break;
                  }
                  p++;
            }

            // q <- 偶数
            while (p < q) {
                  if ((*q & 0x1) == 0) {
                        break;
                  }
                  q--;
            }

            // p->奇数   q->偶数
            if (p < q) {
                  int tmp = *p;
                  *p = *q;
                  *q = tmp;
                  p++;
                  q--;
            }
      }
}

int main() {
      int arr[10] = {0};
      srand(time(0));
      for (int i = 0; i < 10; i++) {
            arr[i] = rand() % 100;
      }
      for (auto v : arr) {
            cout << v << " ";
      }
      cout << endl;

      adjustArray(arr, 10);

      for (auto v : arr) {
            cout << v << " ";
      }
      cout << endl;
}