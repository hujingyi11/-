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

int Partition(SqList &L,int low,int high){
    L.r[0] = L.r[low];
    int pivotkey = L.r[low].key;
    while(low<high){
        while(low<high&&L.r[high].key>=pivotkey) --high;
        L.r[low] = L.r[high];
        while(low<high&&L.r[low].key<=pivotkey) ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void QSort(SqList &L,int low,int high){
    if(low<high){
        int pivotloc = Partition(L,low,high);
        QSort(L,low,pivotloc-1);
        QSort(L,pivotloc+1,high);
    }
}

void QuickSort(SqList &L){
    QSort(L,1,L.length);
}

void QSort1(SqList &L,int low,int high){
    if(low<high){
        int pivotloc = Partition(L,low,high);
    }
}

int main(){
        SqList L,L1;
    InitList(L);
    L1 = L;
    QuickSort(L);
    for(int i = 0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<" ";
    cout<<L.r[L.length].key<<endl;
    QSort1(L1,1,L1.length);
    for(int i= 0 ;i<L1.length-1;++i){
        cout<<L1.r[i+1].key<<" ";
    }
    cout<<L1.r[L.length].key;
}