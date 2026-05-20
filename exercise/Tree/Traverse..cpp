#include <iostream>
using namespace std;
typedef char TElemType;
struct BiTNode{
    TElemType data;
    struct BiTNode *lchild, *rchild;
};
typedef struct BiTNode *BiTree;

void CreatBiTree(BiTree &BT); 
void InorderTraversal( BiTree BT );
void PreorderTraversal( BiTree BT );
void PostorderTraversal( BiTree BT );
void LevelorderTraversal( BiTree BT );

int main()
{
    BiTree BT;
    CreatBiTree(BT);
    cout<<"Inorder:"; InorderTraversal(BT); cout<<endl;
    cout<<"Preorder:"; PreorderTraversal(BT); cout<<endl;
    cout<<"Postorder:"; PostorderTraversal(BT); cout<<endl;
    cout<<"Levelorder:"; LevelorderTraversal(BT); cout<<endl;
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

void InorderTraversal( BiTree BT ){
    if(BT){
        InorderTraversal(BT->lchild);
        cout<<BT->data<<" ";
        InorderTraversal(BT->rchild);
    }

}

void PreorderTraversal( BiTree BT ){
    if(BT){
        cout<<BT->data<<" ";
        PreorderTraversal(BT->lchild);
        PreorderTraversal(BT->rchild);        
    }

}

void PostorderTraversal( BiTree BT ){
    if(BT){
        PostorderTraversal(BT->lchild);
        PostorderTraversal(BT->rchild);
        cout<<BT->data<<" ";        
    }
}

typedef struct 
{
    BiTNode **base;
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.base = new BiTNode* [8];
    if(!Q.base) exit(0);
    Q.front = Q.rear = 0;
}

void EnQueue(SqQueue &Q,BiTNode* ch){
    if((Q.rear+1) % 8 == Q.front){
        exit(0);
    }
    Q.base[Q.rear] = ch;
    Q.rear = (Q.rear + 1) % 8;
}

void Pop(SqQueue &Q,BiTNode* &e){
    cout<<Q.base[Q.front]->data<<" ";
    e = Q.base[Q.front];
    Q.front = (Q.front+1) %8;
}

void LevelorderTraversal( BiTree BT ){
    SqQueue Q;
    InitQueue(Q);
    BiTNode *ttt;
    EnQueue(Q,BT);
    while(1){

        if(Q.front != Q.rear){       
            Pop(Q,ttt);
            if(ttt->lchild){
                EnQueue(Q,ttt->lchild);
            }
            if(ttt->rchild){
                EnQueue(Q,ttt->rchild);
            }        
        }else {
            break;
        }
    }
}