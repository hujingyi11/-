#include <iostream>
using namespace std;
typedef char TElemType;
struct BiTNode{
    TElemType data;
    struct BiTNode *lchild, *rchild;
};
typedef struct BiTNode *BiTree;

void CreatBiTree(BiTree &BT); 
int GetHeight( BiTree BT );

int main()
{
    BiTree BT;
    CreatBiTree(BT);
    cout<<GetHeight(BT)<<endl;
    return 0;
}
void CreatBiTree(BiTree &BT)
{
    char ch;
    cin>>ch;
    if(ch=='#')
    {
        BT=NULL;
    }
    else
    {
        BT=new BiTNode;
        BT->data=ch;
        CreatBiTree(BT->lchild);
        CreatBiTree(BT->rchild);
    }
}

/* 请在这里填写答案 */

int GetHeight( BiTree BT ){
    if(BT == NULL){
        return 0;
    }
    int m = GetHeight(BT->lchild);
    int n = GetHeight(BT->rchild);
    if(m>n) return m+1;
    else return n+1;
}