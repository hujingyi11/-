#include<iostream>
#include<string>
using namespace std;

#define MAXQSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef string QElemType;
typedef int Status;

typedef struct {
    QElemType *base; //初始化时动态分配存储空间
    int front;       //头指针
    int rear;        //尾指针
} SqQueue;

Status InitQueue(SqQueue &Q){
    Q.base = new QElemType [MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front = Q.rear =0;
    return OK;
}

int QueueLength(SqQueue Q){
    return (Q.rear - Q.front + MAXQSIZE ) % MAXQSIZE;
}//count

Status EnQueue(SqQueue &Q,QElemType e){
    if((Q.rear + 1) % MAXQSIZE == Q.front)
        cout<<"FULL"<<endl;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear +1) % MAXQSIZE;
    cout<<"OK"<<endl;
    return OK;
}

Status DeQueue(SqQueue & Q,QElemType &e){
    if(Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}


void print(SqQueue &Q){
    QElemType elem;
    if(Q.front == Q.rear){
        cout<<"EMPTY"<<endl;
    }else {
        DeQueue(Q,elem);
        cout<<elem<<endl;
    }   
}

void head(SqQueue Q){
    if(Q.front == Q.rear){
        cout<<"EMPTY"<<endl;
    }else{
        cout<<Q.base[Q.front]<<endl;
    }
}

void empty(SqQueue Q){
    if(Q.front == Q.rear){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
}

int main(){
    SqQueue Q;
    InitQueue(Q);
    int n;
    cin>>n;
    while(n != 0){
        string str;
        string elem;
        cin>>str;
        if(str == "ADD") {
           cin>>elem;
           EnQueue(Q,elem); 
        }else if(str == "PRINT"){
            print(Q);
        }else if(str == "HEAD"){
            head(Q);
        }else if(str == "COUNT"){
            cout<<QueueLength(Q)<<endl;
        }else if(str == "EMPTY"){
            empty(Q);
        }
        --n;
    }
}