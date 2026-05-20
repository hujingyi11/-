#include<iostream>
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
void outpath(Bitree T, char path[], int len); //输出二叉树中从每个叶子结点到根结点的路径
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
        char path[MAXSIZE];
        outpath(T, path, 0);
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

void outpath(Bitree T, char path[], int len){
    if (T == NULL) {
        return;
    }
    path[len] = T->data;
    len++;
    if(T->lchild == NULL && T->rchild == NULL){
        for(int i = len -1;i>-1;--i){
            cout<<path[i];
        }
        cout<<endl;
    }else{
        outpath(T->lchild,path,len);
        outpath(T->rchild,path,len);
    }
    len--;
}
