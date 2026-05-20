#include<iostream>
using namespace std;
typedef char ElemType;
typedef struct BiTNode{
    ElemType data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int Node_Num = 0;
int leafNode_Num = 0;

void createTree(BiTree &T){
    ElemType ch;
    cin>>ch;
    if(ch == '#'){
        T = NULL;
    }else{
        T = new BiTNode;
        T->data = ch;  
        ++Node_Num;      
        createTree(T->lchild);
        createTree(T->rchild);
    }
}

void InoderTraversal(BiTree T){
    if(T){
        InoderTraversal(T->lchild);
        cout<<T->data<<" ";
        InoderTraversal(T->rchild);
        if(T->lchild == NULL && T->rchild == NULL){
            leafNode_Num++;
        }        
    }

}

void preorderTraversal(BiTree T){
    if(T){
        cout<<T->data<<" ";
        preorderTraversal(T->lchild);
        preorderTraversal(T->rchild);        
    }

}

void postorderTraversal(BiTree T){
    if(T){
        postorderTraversal(T->lchild);
        postorderTraversal(T->rchild);
        cout<<T->data<<" ";        
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

int GetHeight( BiTree BT ){
    if(BT == NULL){
        return 0;
    }
    int m = GetHeight(BT->lchild);
    int n = GetHeight(BT->rchild);
    if(m>n) return m+1;
    else return n+1;
}

int main(){
    BiTree T;
    createTree(T);
    preorderTraversal(T);
    cout<<endl;
    InoderTraversal(T);
    cout<<endl;    
    postorderTraversal(T);
    cout<<endl;
    LevelorderTraversal(T);
    cout<<endl;
    int height = GetHeight(T);
    cout<<height<<endl;
    cout<<Node_Num<<'\n'<<leafNode_Num;
    return 0;
}
