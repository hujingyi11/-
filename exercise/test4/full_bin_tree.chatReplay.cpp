#include<iostream>
#include<queue>
using namespace std;
typedef char ELemType;
typedef struct BiTNode{
    ELemType data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int Node_num = 0;
void creatTree(BiTree &T){
    ELemType ch;
    cin>>ch;
    if(ch == '#'){
        T = NULL;
    }else{
        T = new BiTNode;
        T->data =ch;
        Node_num++;
        creatTree(T->lchild);
        creatTree(T->rchild);
    }
}

bool first_print = true;

void output(BiTNode* T){
    if(first_print){
        cout<<T->data;
        first_print = false;
    }else{
        cout<<" "<<T->data;
    }
}
void levelTraversal(BiTree T){
    if(T == NULL ) return ;
    queue<BiTNode*> Q;
    Q.push(T);
    BiTNode *tt;
    while(!Q.empty()){
        tt = Q.front();
        output(tt);
        Q.pop();
        if(tt->lchild){
            Q.push(tt->lchild); 
        }  
        if(tt->rchild){
            Q.push(tt->rchild);
        }
    }
}

int GetHeight(BiTree T){
    if(T == NULL) return 0;
    int m = GetHeight(T->lchild);
    int n = GetHeight(T->rchild);
    if(m>n) return m+1;
    else return n+1;
}

bool judge_full(BiTree T){
    if(T == NULL ) return 1;
    queue<BiTNode*> Q;
    Q.push(T);
    BiTNode *tt;
    bool encounterNULL = 0;
    while(!Q.empty()){
        tt = Q.front();
        Q.pop();
        if(tt == NULL) encounterNULL = 1 ;
        else{
            if(encounterNULL) return 0;
            Q.push(tt->lchild); 
            Q.push(tt->rchild);           
        }
    }
    return 1;
}

int main(){
    BiTree T;
    creatTree(T);
    levelTraversal(T);
    cout<<endl;
    cout<<GetHeight(T)<<' '<<Node_num<<endl;
    if(judge_full(T) == 1){
        cout<<"YES";
    }else cout<<"NO";
    return 0;
}


