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

void BInsertSort(SqList &L){
    int i,j,low,high,mid;
    for(i=2;i<=L.length;++i){
        L.r[0] = L.r[i];
        low=1;high = i-1;
        while(low<=high){
            mid = (low+high)/2;
            if(L.r[0].key<L.r[mid].key) high = mid-1;
            else low = mid +1;
        }
        for(j=i-1;j>=high+1;--j) L.r[j+1] = L.r[j];
        L.r[high+1] = L.r[0];
    }
}

int main(){
    SqList L,L1;
    InitList(L);
    L1 = L;
    BInsertSort(L);
    for(int i = 0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<" ";
    cout<<L.r[L.length].key<<endl;
    L1.r[0] = L1.r[2];
    int low=1; int high = 1;
    while(low<=high){
        int mid = (low+high)/2;
        if(L1.r[0].key<L1.r[mid].key) high = mid-1;
        else low = mid +1;
    }
    for(int j=1;j>=high+1;--j) L1.r[j+1] = L1.r[j];
    L1.r[high+1] = L1.r[0];
        for(int i= 0 ;i<L1.length-1;++i){
        cout<<L1.r[i+1].key<<" ";
    }
    cout<<L1.r[L1.length].key;
    return 0;
}