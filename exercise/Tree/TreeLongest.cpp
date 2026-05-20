#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 10000
#define MAX(a,b) ((a)>(b)?(a):(b))
typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*Bitree;
void CreateTree(Bitree &T); //创建二叉树
int pathlongest(Bitree T); //求任意二叉树中第一条最长路径的长度
void longest(Bitree T); //输出此路径上各结点的值
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
        int c;
       c = pathlongest(T);
      cout << c << endl;
        longest(T);
        cout<<endl;
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

/* 请在这里填写答案 */

int GetHeight( Bitree BT ){
    if(BT == NULL){
        return 0;
    }
    int m = GetHeight(BT->lchild);
    int n = GetHeight(BT->rchild);
    if(m>n) return m+1;
    else return n+1;
}

int finallength = 0;
int pathlongest(Bitree T){
    if(T == NULL) return 0;
    return GetHeight(T);
}
char longestpath[MAXSIZE];
char path [MAXSIZE];
int len = 0; 
void outpath(Bitree T, char path[], int len){
       if (T == NULL) {
        return;
    }
    path[len] = T->data;
    len++;
    if(T->lchild == NULL && T->rchild == NULL){
        if(len>finallength){
            finallength = len;
            for(int i = 0;i<len+1;++i){
                longestpath[i] = path[i];
            }            
        }

    }else{
        outpath(T->lchild,path,len);
        outpath(T->rchild,path,len);
    }
    len--;
}

void longest(Bitree T) {
    if (T == NULL) return;
    
    char currentPath[MAXSIZE]; // 用于记录DFS遍历过程中的当前路径
    finallength = 0; // 重置最终路径长度
    
    outpath(T, currentPath, 0);
    
    // 输出找到的最长路径
    for (int i = 0; i < finallength; i++) {
        cout << longestpath[i];
    }
}