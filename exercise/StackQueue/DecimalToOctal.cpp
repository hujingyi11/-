#include <iostream>
using namespace std;
 
// 常量与类型定义
#define MAXSIZE 100  // 顺序栈的最大容量
#define OK 1
#define ERROR 0
 
// 栈元素类型（十进制转八进制需存储整数余数，故用int）
typedef int SElemType;
// 函数返回状态类型
typedef int Status;
 
// 顺序栈结构体定义（数值转换依赖栈存储八进制余数）
typedef struct {
    SElemType* base;   // 栈底指针（指向栈的起始地址）
    SElemType* top;    // 栈顶指针（指向栈顶元素的下一个位置）
    int stacksize;     // 栈的最大容量
} SqStack;

// 初始化顺序栈：分配内存，设置栈底/栈顶指针和最大容量
Status InitStack(SqStack& S);
// 判断栈是否为空
bool StackEmpty(SqStack S);
// 入栈操作：将元素压入栈顶
Status Push(SqStack& S, SElemType e);
// 出栈操作：弹出栈顶元素并返回
SElemType Pop(SqStack& S);
// 销毁栈：释放栈占用的内存，避免内存泄漏
void DestroyStack(SqStack& S);
//十进制转八进制
void DecimalToOctal(int N);
int main() {
    int decimalNum;

    cin >> decimalNum;

    // 调用转换函数，输出结果
    DecimalToOctal(decimalNum);
 
    return 0;
}
// 初始化顺序栈：分配内存，设置栈底/栈顶指针和最大容量
Status InitStack(SqStack& S) {
    // 为栈分配MAXSIZE大小的连续内存
    S.base = new SElemType[MAXSIZE];
    if (!S.base) {  // 内存分配失败
        cout << "栈内存分配失败！" << endl;
        return ERROR;
    }
    S.top = S.base;         // 栈空时，栈顶指针 = 栈底指针
    S.stacksize = MAXSIZE;  // 设置栈的最大容量
    return OK;
}

// 判断栈是否为空
bool StackEmpty(SqStack S) {
    return S.top == S.base;  // 栈顶 == 栈底 → 栈空
}

// 入栈操作：将元素压入栈顶
Status Push(SqStack& S, SElemType e) {
    // 检查栈是否已满（栈顶指针 - 栈底指针 == 最大容量）
    if (S.top - S.base == S.stacksize) {
        cout << "栈满，无法入栈！" << endl;
        return ERROR;
    }
    *S.top++ = e;  // 元素存入栈顶，栈顶指针上移
    return OK;
}

// 出栈操作：弹出栈顶元素并返回
SElemType Pop(SqStack& S) {
    // 检查栈是否为空
    if (S.top == S.base) {
        cout << "栈空，无法出栈！" << endl;
        return ERROR;  // 空栈返回错误标记
    }
    SElemType e = *--S.top;  // 栈顶指针下移，再取元素（先移后取）
    return e;
}

// 销毁栈：释放栈占用的内存，避免内存泄漏
void DestroyStack(SqStack& S) {
    if (S.base) {         // 若栈底指针非空（栈已初始化）
        delete[] S.base;  // 释放连续内存
        S.stacksize = 0;  // 重置最大容量
        S.base = S.top = NULL;  // 指针置空，避免野指针
    }
}

/* 请在这里填写答案 */
void DecimalToOctal(int N){
    SqStack S;
    InitStack(S);
    while(N != 0){
        Push(S,N%8);
        N = N/8;
    }
    while(!StackEmpty(S)){
        cout<<Pop(S);
    }
    cout<<endl;
    DestroyStack(S);
}