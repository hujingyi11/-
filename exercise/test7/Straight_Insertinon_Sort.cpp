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

void InsertSort(SqList &L){
    int i,j;
    for( i= 2;i<=L.length;++i)
        if(L.r[i].key < L.r[i-1].key){
            L.r[0] = L.r[i];
            L.r[i] = L.r[i-1];
            for( j = i-2;L.r[0].key<L.r[j].key;--j)
                L.r[j+1] = L.r[j];
            L.r[j+1] = L.r[0];
        }
}

int main(){
    SqList L,L1;
    InitList(L);
    L1 = L;
    InsertSort(L);
    for(int i = 0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<" ";
    cout<<L.r[L.length].key;
    if(L1.r[2].key<L1.r[1].key){
        L1.r[0] = L1.r[2];
        L1.r[2] = L1.r[1];
        L1.r[1] = L1.r[0];
    }
    cout<<endl;
    for(int i= 0 ;i<L1.length-1;++i){
        cout<<L1.r[i+1].key<<" ";
    }
    cout<<L1.r[L.length].key;
    return 0;
}