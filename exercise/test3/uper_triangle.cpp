#include<iostream>
using namespace std;

int main(){
    int n,c;
    cin>>n>>c;
    int a[n*n];
    for(int i =0 ;i<n*n;++i){
        cin>>a[i];
    }
    int q,i,j;
    
    for(int i= 0;i<n;++i){
        for(int j=i;j<n;++j){
                cout<<a[i*n+j]<<" ";
        }
    }
    cout<<c<<endl;
    cin>>q;
    cout<<"Processing "<<q<<" queries:"<<endl;
    while(q!=0){
        cin>>i>>j;
        if(i<=j){
            cout<<"Index for ("<<i<<", "<<j<<"): "<<((i)*(2*n-i+1)/2+j-i)<<endl;
        }else{
            cout<<"Index for ("<<i<<", "<<j<<"): Lower Triangular ("<<c<<")"<<endl;
        }
        --q;
    }
    
}