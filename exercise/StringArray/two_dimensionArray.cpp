#include<iostream>
using namespace std;
//行数m和列数n
int main(){        
    while(1){
        start:
        int m,n;
        cin>>m>>n;
        if(m==0&&n==0) return 0;
        int a[m*n];
        for(int i=0;i<m*n;++i){
            cin>>a[i];
        }
        for(int i=0;i<m*n;++i){
            for(int j=i+1;j<m*n;++j){
                if(a[i]==a[j]) {
                    cout<<"YES"<<endl;
                    goto start;
                }
            }
        }
        cout<<"NO";
    }
    return 0;
}
