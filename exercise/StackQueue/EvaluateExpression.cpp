#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef struct
{//符号栈
    char* base;
    char* top;
    int stacksize;
}SqStack1;

typedef struct
{//数字栈
    double* base;
    double* top;
    int stacksize;
}SqStack2;

typedef int status;

status InitStack(SqStack1 &S);
status InitStack(SqStack2 &S);
status Push1(SqStack1 &S,char ch);
status Push2(SqStack2 &S,double num);
status Pop1(SqStack1 &S,char &ch);
status Pop2(SqStack2 &S,double &num);
char GetTop(SqStack1 S);
double GetTop(SqStack2 S);

int main(){
    return 0;
}

status InitStack(SqStack1 &S){
    S.base = new char [MAXSIZE];
    if(!S.base) return OVERFLOW;
    S.base = S.top;
    S.stacksize = MAXSIZE;
    return OK;
}

status InitStack(SqStack2 &S){
    S.base = new double [MAXSIZE];
    if(!S.base) return OVERFLOW;
    S.base = S.top;
    S.stacksize = MAXSIZE;
    return OK;
}

status Push1(SqStack1 &S,char ch){
    if(S.top - S.base == S.stacksize) return ERROR;
    *S.top = ch;
    S.top++;
    return OK;
}

status Push2(SqStack2 &S,double num){
    if(S.top - S.base == S.stacksize) return ERROR;
    *S.top = num;
    S.top++;
    return OK;
}

status Pop1(SqStack1 &S,char &ch){
    if(S.base == S.top ) return ERROR;
    ch = *(S.top-1);
    S.top--;
    return OK;
}
status Pop2(SqStack2 &S,double &num){
    if(S.base == S.top ) return ERROR;
    num = *(S.top-1);
    S.top--;
    return OK;
}

char GetTop1(SqStack1 S){
    return *(S.top-1);
}
double GetTop2(SqStack2 S){
    return *(S.top-1);
}
double operation(double a,char ch,double b){
    double result;
    switch(ch){
        case '+':
        result = a + b ;
        break;
        case '-':
        result = a - b;
        break;
        case '*':
        result = a * b;
        break;
        case '/':
        result = a / b;
        break;
    }
    return result; //保留两位小数
}

void EvaluateExpress(){
    SqStack1 S1;
    SqStack2 S2;
    InitStack(S1);
    InitStack(S2);

}