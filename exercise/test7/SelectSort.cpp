#include<iostream>
using namespace std;

#define MAXSIZE 20

typedef int KeyType;
typedef struct{
    KeyType key;
}Redtype;
typedef struct{
    Redtype r[MAXSIZE+1];
    int length;
}SqList;

void InitList(SqList &L){
    cin>>L.length;
    for(int i = 0;i<L.length;++i){
        cin>>L.r[i+1].key;
    }
}

void SelectSort(SqList &L){
    int i,j,k;
    for(i=1;i<L.length;++i){
        k=i;
        for(j=i+1;j<=L.length;++j)
            if(L.r[j].key<L.r[k].key) k=j;
        if(k!=i){
            L.r[0] = L.r[i];
            L.r[i] = L.r[k];
            L.r[k] = L.r[0];
        }
    }
}

int main(){
    SqList L,L1;
    InitList(L);
    L1 = L;
    SelectSort(L);
    for(int i=0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<' ';
    cout<<L.r[L.length].key<<endl;
    int i=1,j,k=1;
    for(j=i+1;j<=L.length;++j)
        if(L1.r[j].key<L1.r[k].key) k=j;
    if(k!=i){
        L1.r[0] = L1.r[i];
        L1.r[i] = L1.r[k];
        L1.r[k] = L1.r[0];
    }
    for(int i=0;i<L.length-1;++i)
        cout<<L1.r[i+1].key<<' ';
    cout<<L1.r[L.length].key<<endl;
}