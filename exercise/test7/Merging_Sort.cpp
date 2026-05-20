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

void Merge(Redtype R[],Redtype T[],int low,int mid,int high){
    int i,j,k;
    i=low;j=mid + 1;k=low;
    while(i<=mid&&j<=high){
        if(R[i].key<=R[j].key) T[k++] = R[i++];
        else T[k++] = R[j++];
    }
    while(i<=mid) T[k++] = R[i++];
    while(j<=high) T[k++] = R[j++];
}

void MSort(Redtype R[],Redtype T[],int low,int high){
    Redtype *S;
    if(high == low) T[low] = R[low];
    else{
        int mid = (low + high)/2;
        S = new Redtype[MAXSIZE];
        MSort(R,S,low,mid);
        MSort(R,S,mid+1,high);
        Merge(S,T,low,mid,high);
    }
}

void MergeSort(SqList &L){
    MSort(L.r,L.r,1,L.length);
}

int main(){
    SqList L,L1;
    InitList(L);
    L1 = L;
    MergeSort(L);
    for(int i = 0;i<L.length-1;++i)
        cout<<L.r[i+1].key<<" ";
    cout<<L.r[L.length].key<<endl;
    for(int i=1;i<=L1.length;i=i+2){
        if(i+1>L.length) break;
        if(L1.r[i].key>L1.r[i+1].key) {
            L1.r[0] = L1.r[i+1];
            L1.r[i+1] = L1.r[i];
            L1.r[i] = L1.r[0];
        }
    }
    for(int i=0;i<L1.length-1;++i){
        cout<<L1.r[i+1].key<<" ";
    }
    cout<<L1.r[L1.length].key;
    return 0;
}