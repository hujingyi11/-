#include<iostream>
using namespace std;
#define MAXSIZE 10000
#define MAX(a,b) ((a)>(b)?(a):(b))
int min_index[MAXSIZE];
typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*Bitree;
void CreateTree(Bitree &T); //创建二叉树
void init_array(int* arr, int n); 
int MaxWidth(Bitree T, int depth, int index); //计算二叉树的最大宽度（二叉树的最大宽度是指二叉树所有层中结点个数的最大值）
int main()
{
    while(1)
    {
        Bitree T;
        CreateTree(T);
        if(T==NULL)
        {
            break;
        }
        init_array(min_index, MAXSIZE);
        int max;
        max = MaxWidth(T, 1, 1);
        cout << max << endl;
    }
    return 0;
}
void CreateTree(Bitree &T) //创建二叉树
{
    ElemType ch;
    cin >> ch;
    if (ch == '0')
    {
        T = NULL;
    }
    else
    {
        T = new BiTNode;
        T->data = ch;
        CreateTree(T->lchild);
        CreateTree(T->rchild);
    }
}
void init_array(int* arr, int n)
{
    int i;
    for (i = 0;i < n;i++)
    {
        *(arr + i) = -1;
    }
}

/* 请在这里填写答案 */

typedef struct 
{
    BiTNode **base;
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.base = new BiTNode* [1000];
    if(!Q.base) exit(0);
    Q.front = Q.rear = 0;
}

void EnQueue(SqQueue &Q,BiTNode* ch){
    if((Q.rear+1) % 1000 == Q.front){
        exit(0);
    }
    Q.base[Q.rear] = ch;
    Q.rear = (Q.rear + 1) % 1000;
}

void Pop(SqQueue &Q,BiTNode* &e){
    e = Q.base[Q.front];
    Q.front = (Q.front+1) %1000;
}

int MaxWidth(Bitree T, int depth, int index){
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q,T);
    int max = 0;
    while(Q.front != Q.rear){
        int Length = Q.rear - Q.front;
        if(max < Length) max = Length;
        for(int i = 0;i<Length ;++i){
            BiTNode *tt = Q.base[Q.front++];
            if(tt->lchild) {
                EnQueue(Q,tt->lchild);
            }
            if(tt->rchild) {
                EnQueue(Q,tt->rchild); 
            }           
        }
    }
    return max;
}
