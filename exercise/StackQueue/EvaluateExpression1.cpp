#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 运算符栈
typedef struct {
    char* base;
    char* top;
    int stacksize;
} SqStack1;

// 操作数栈
typedef struct {
    double* base;
    double* top;
    int stacksize;
} SqStack2;

// 初始化运算符栈
int InitStack1(SqStack1& S) {
    S.base = new char[MAXSIZE];
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

// 初始化操作数栈
int InitStack2(SqStack2& S) {
    S.base = new double[MAXSIZE];
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

// 运算符栈入栈
int Push1(SqStack1& S, char e) {
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}

// 操作数栈入栈
int Push2(SqStack2& S, double e) {
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}

// 运算符栈出栈
int Pop1(SqStack1& S, char& e) {
    if (S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

// 操作数栈出栈
int Pop2(SqStack2& S, double& e) {
    if (S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

// 获取运算符栈顶元素
char GetTop1(SqStack1 S) {
    if (S.top != S.base) return *(S.top - 1);
    return '\0';
}

// 获取操作数栈顶元素
double GetTop2(SqStack2 S) {
    if (S.top != S.base) return *(S.top - 1);
    return 0.0;
}

// 判断是否是运算符
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=');
}

// 获取运算符优先级
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '(': return 0;
        case '=': return -1;
        default: return -1;
    }
}

// 执行运算
double operate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (fabs(b) < 1e-12) {
                return 0; // 避免除零错误
            }
            return a / b;
        default: return 0;
    }
}

// 表达式求值函数
double EvaluateExpression(char* expression) {
    SqStack1 opStack; // 运算符栈
    SqStack2 numStack; // 操作数栈
    InitStack1(opStack);
    InitStack2(numStack);
    
    Push1(opStack, '='); // 在栈底放入=作为结束标志
    
    int i = 0;
    char ch = expression[i++];
    
    while (ch != '=' || GetTop1(opStack) != '=') {
        if (!isOperator(ch)) {
            // 读取数字
            double num = 0.0;
            bool hasDecimal = false;
            double decimalPlace = 0.1;
            
            while ((ch >= '0' && ch <= '9') || ch == '.') {
                if (ch == '.') {
                    hasDecimal = true;
                } else {
                    if (!hasDecimal) {
                        num = num * 10 + (ch - '0');
                    } else {
                        num = num + (ch - '0') * decimalPlace;
                        decimalPlace *= 0.1;
                    }
                }
                ch = expression[i++];
            }
            Push2(numStack, num);
        } else {
            switch (ch) {
                case '(':
                    Push1(opStack, ch);
                    ch = expression[i++];
                    break;
                    
                case ')':
                    while (GetTop1(opStack) != '(') {
                        char op;
                        Pop1(opStack, op);
                        double b, a;
                        Pop2(numStack, b);
                        Pop2(numStack, a);
                        double result = operate(a, b, op);
                        Push2(numStack, result);
                    }
                    char temp;
                    Pop1(opStack, temp); // 弹出左括号
                    ch = expression[i++];
                    break;
                    
                default:
                    if (getPriority(ch) > getPriority(GetTop1(opStack))) {
                        Push1(opStack, ch);
                        ch = expression[i++];
                    } else {
                        char op;
                        Pop1(opStack, op);
                        double b, a;
                        Pop2(numStack, b);
                        Pop2(numStack, a);
                        double result = operate(a, b, op);
                        Push2(numStack, result);
                    }
                    break;
            }
        }
    }
    
    double finalResult;
    Pop2(numStack, finalResult);
    return finalResult;
}

int main() {
    char expression[100];
    
    while (true) {
        cin.getline(expression, 100);
        
        // 检查是否只有"="
        if (strlen(expression) == 1 && expression[0] == '=') {
            break;
        }
        
        double result = EvaluateExpression(expression);
        cout << fixed << setprecision(2) << result << endl;
    }
    
    return 0;
}