#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<iomanip>
using namespace std;

//顺序栈定义
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100 //顺序栈存储空间的初始分配量
typedef int Status;
typedef double SElemType; //存储double类型数据

typedef struct {
    SElemType *base; //栈底指针
    SElemType *top;  //栈顶指针
    int stacksize;   //栈可用的最大容量
} SqStack;

Status InitStack(SqStack &S){
    S.base = new SElemType [MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

Status push(SqStack &S,SElemType e){
    if(S.top - S.base == S.stacksize) return ERROR;
    *S.top = e;
    S.top++;
    return OK;
}

Status pop(SqStack &S,SElemType &e){
    if(S.base == S.top) return ERROR;    
    S.top--;
    e = *S.top;

    return OK;
}

SElemType Calculate(SElemType a,SElemType b,char ch){
    switch(ch){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
    }
    return 0.0;
}

SElemType GetTop(SqStack S){
    if(S.base != S.top) return *(S.top-1);
    return 0;
}

bool mistake = 0;

int main(){
    SqStack S;
    InitStack(S);
    SElemType elem1,elem2,result;        
    char ch;
    while(1){
        cin>>ch;
        if(ch == '=' && S.base == S.top){
            break;
        }else if(ch == '='&& S.base!=S.top) {
            if(mistake){
                if(elem2 == 0) cout<<"错误:除法分母为零"<<'\n'<<"表达式错误"<<endl;
                S.top = S.base;
                mistake = 0;
                continue;
            }
            pop(S,result);
            cout<<fixed<<setprecision(2)<<result<<endl;
        }else if(ch >= '0' && ch <= '9'){
            cin.putback(ch);
            cin>>elem1;
            push(S,elem1);
            continue;
        }else if(ch == '+'||ch == '-'||ch =='*'||ch =='/'){
            cin.putback(ch);
            cin>>ch;
            pop(S,elem2);
            if(elem2 == 0 && ch == '/') {
                mistake = 1;
                continue;                
            }          
            pop(S,elem1);
            result = Calculate(elem1,elem2,ch);
            push(S,result);            
        }else {
            cout<<"错误:未知运算符"<<ch<<'\n'<<"表达式错误"<<endl;
            continue;
        }
    }
    return 0;
}