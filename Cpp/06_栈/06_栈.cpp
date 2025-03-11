#include <iostream>

using namespace std;
// 顺序栈

class SeqStack {
   public:
    SeqStack(int size = 10) : mTop(0), mCapacity(size) { mpStack = new int[mCapacity]; }
    ~SeqStack() {
        delete[] mpStack;
        mpStack = nullptr;
    }
    void push(int val) {
        if (mTop == mCapacity) {
            expand();
        }
        mpStack[mTop++] = val;
    }
    void pop() {
        if (mTop == 0) {
            throw "stack is empty!";
        }
        mTop--;
    }
    // 获取栈顶元素
    int top() {
        if (mTop == 0) {
            throw "stack is empty!";
        }
        return mpStack[mTop - 1];
    }
    bool empty() const { return mTop == 0; }
    int size() const { return mTop; }

   private:
    int* mpStack;
    int mTop;       // 栈顶位置
    int mCapacity;  // 容量
    void expand() {
        int* temp = new int[mCapacity * 2];
        // 第三个参数是要复制的字节数
        memcpy(temp, mpStack, mTop * sizeof(int));
        delete[] mpStack;
        mpStack = temp;
        mCapacity = mCapacity * 2
    }
};

int main() {
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    SeqStack s;

    for (int v : arr) {
        s.push(v);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}