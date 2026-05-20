#include<iostream>
using namespace std;

int MAXSIZE = 100;

typedef struct BitNode{
    BitNode *lchild,*rchild;
    char data;
}BitNode,*BiTree;

typedef struct{
    BitNode *base;
    BitNode *top;
    int size;
}SqStack1;//操作数栈

typedef struct{
    char *base;
    char *top;
    int size;
}SqStack2;//运算符栈

void InitStack(SqStack1 &S){
    S.base = new BitNode [MAXSIZE];
    if(!S.base) return ;
    S.top = S.base;
    S.size = MAXSIZE;
}
void InitStack(SqStack2 &S){
    S.base = new char [MAXSIZE];
    if(!S.base) return ;
    S.top = S.base;
    S.size = MAXSIZE;
}
void Push(SqStack1 &S,BitNode n){
    if(S.top - S.base == S.size) return ;
    *S.top++ = n;
}
void Push(SqStack2 &S,char e){
    if(S.top - S.base == S.size) return ;
    *S.top++ = e;
}
void Pop(SqStack1 &S,BitNode &e){
    if(S.base == S.top) return ;
    e = *--S.top;
}
void Pop(SqStack2 &S,char &e){
    if(S.base == S.top) return ;
    e = *--S.top;
}
// int GetTop(SqStack1 S){
//     return *--S.top;
// }
char GetTop(SqStack2 S){
    return *--S.top;
}

BiTree CreateExpTree(BiTree &BT,BitNode *ch1,BitNode *ch2,char ch3){  // 创建表达式树
    BT = new BitNode ;
    BT->data = ch3;
    if(ch1){
        BT->lchild = new BitNode;
        BT->lchild = ch1;
    }else{
        BT->lchild = NULL;
    }
    if(ch2){
        BT->lchild = new BitNode;
        BT->lchild = ch2;
    }else{
        BT->lchild = NULL;
    }
    return BT;
}

bool In(char ch){
    if(ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/') return 1;
    else return 0;
}

int getPriority(char ch){
    switch(ch){
        case '+' :
        case '-' : return 1;
        case '*' :
        case '/' : return 2;
        case '(' :
        case ')' : return 0;
        case '#' : return -1;
        break;
    }
    return 0;
}
char Precede(char ch1,char ch2){
    int n1 = getPriority(ch1);
    int n2 = getPriority(ch2);
    int n = n1-n2;
    if(n1 == -1 && n1==n2)return '=';
    if(n1 == 0 && n1==n2) return '=';
    if(n>=0) return '>';
    else return '=';
}
void InitExpTree( BitNode* T){
    SqStack1 EXPT;//暂存表达式树的根结点
    SqStack2 OPTR;//暂存运算符   
    InitStack(EXPT);
    InitStack(OPTR);
    Push(OPTR,'#');
    char ch;
    cin>>ch;
    while(ch != '#'||GetTop(OPTR) != '#'){
        if(!In(ch)){
            T = CreateExpTree(T,NULL,NULL,ch);
            Push(EXPT,*T);
            cin>>ch;
        }
        else{
            switch(Precede(GetTop(OPTR),ch)){
                case '<':
                    Push(OPTR,ch);
                    cin>>ch;
                    break;
                case '>':
                    char theta;
                    BitNode *a,*b;
                    Pop(OPTR,theta);
                    Pop(EXPT,*b);
                    Pop(EXPT,*a);
                    CreateExpTree(T,a,b,theta);
                    Push(EXPT,*T);
                    break;
                case '=':
                    char x;
                    Pop(OPTR,x);
                    cin>>ch;
                    break;
            }
        }
    }
}

int GetValue(char ch,int a,int b){
    switch(ch){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        break;
    }
    return 0;
}
int EvaluateExpTree(BiTree T){// 计算表达式树的值
    int lvalue = 0,rvalue = 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return T->data-'0';
    else {
        lvalue = EvaluateExpTree(T->lchild);
        rvalue = EvaluateExpTree(T->rchild);
        return GetValue(T->data,lvalue,rvalue); 
    }
}     
void DestroyTree(BiTree T){// 销毁表达式树
    if(T){
        DestroyTree(T->lchild);
        DestroyTree(T->lchild);
        delete T;
    }
}

int main(){
    int n;
    cin>>n;
    BiTree BT;
    while(n){
        InitExpTree(BT);
        EvaluateExpTree(BT);
        DestroyTree(BT);
        --n;
    }
    return 0;
}