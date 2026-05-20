#include<iostream>
using namespace std;

#define MAXSIZE 10000

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

void BubbleSort(SqList &L){
    int m,flag,j;
    Redtype t;
    m=L.length-1;
    flag = 1;
    while((m>0)&&(flag == 1)){
        flag = 0;
        for(j=1;j<=m;++j)
            if(L.r[j].key>L.r[j+1].key){
                flag = 1;
                t = L.r[j];
                L.r[j] = L.r[j+1];
                L.r[j+1] = t;
            }
        --m;
    }
}

int main(){
    SqList L,L1;
    InitList(L);
    L1 = L;
    BubbleSort(L);
    for(int i = 0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<" ";
    cout<<L.r[L.length].key;
    int j,m = L1.length-1;
    for(j=1;j<=m;++j)
        if(L1.r[j].key>L1.r[j+1].key){
            Redtype t = L1.r[j];
            L1.r[j] = L1.r[j+1];
            L1.r[j+1] = t;
    }
    cout<<endl;
    for(int i= 0 ;i<L1.length-1;++i){
        cout<<L1.r[i+1].key<<" ";
    }
    cout<<L1.r[L.length].key;
    return 0;
}