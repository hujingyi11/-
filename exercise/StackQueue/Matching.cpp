#include <iostream>
using namespace std;

#define MAXSIZE 100  // 定义栈的最大容量
#define OK 1
#define ERROR 0

typedef int Status;
typedef char SElemType;  // 栈中元素类型为字符

// 顺序栈结构
typedef struct {
    SElemType* base;  // 栈底指针
    SElemType* top;   // 栈顶指针
    int stacksize;    // 栈的最大容量
} SqStack;

// 初始化顺序栈：分配内存，设置栈底/栈顶指针和最大容量
Status InitStack(SqStack& S);
// 判断栈是否为空
bool StackEmpty(SqStack S);
// 入栈操作：将元素压入栈顶
Status Push(SqStack& S, SElemType e);
// 出栈操作：弹出栈顶元素并返回
SElemType Pop(SqStack& S);
// 获取栈顶元素（用于匹配时查看栈顶括号）
SElemType GetTop(SqStack S);
// 销毁栈：释放栈占用的内存，避免内存泄漏
void DestroyStack(SqStack& S);
// 检验表达式中括号是否正确匹配的函数
Status Matching();
// 主函数：测试括号匹配功能
int main() {
    // 输入带括号的表达式（以#结束）
    bool isMatched = Matching();
    if (isMatched) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
// 初始化顺序栈：分配内存，设置栈底/栈顶指针和最大容量
Status InitStack(SqStack& S) {
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
        return ERROR;  // 空栈返回错误标记（实际可根据需求调整）
    }
    SElemType e = *--S.top;  // 栈顶指针下移，再取元素（先移后取）
    return e;
}

// 获取栈顶元素（用于匹配时查看栈顶括号）
SElemType GetTop(SqStack S) {
    if (S.top == S.base) {
        cout << "栈空，无栈顶元素！" << endl;
        return ERROR;
    }
    return *(S.top - 1);  // 返回栈顶元素（栈顶指针前一位的元素）
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
Status Matching(){
    SqStack S;
    InitStack(S);
    char ch;
    int flag = 1;
    cin>>ch;
    while(ch != '#' && flag){
        switch(ch){
            case '[':
            case '(':
            Push(S,ch);
            break;
            case ']':
            if(!StackEmpty(S) && GetTop(S)=='[')     
            Pop(S);
            else flag = 0;
            break;
            case ')':
            if(!StackEmpty(S) && GetTop(S) == '(')
            Pop(S);
            else flag = 0;
            break;
        }
        cin>>ch;
    } 
    if(StackEmpty(S) && flag) return OK;
    else return ERROR;
}