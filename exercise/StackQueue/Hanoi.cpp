#include<iostream>
using namespace std;
void Hanoi(int n,char A,char B,char C);
void move(char A, char B);
int main()
{
    int n;
    cin>>n;
    Hanoi(n, 'a', 'b', 'c');
    return 0;
}
void move(char A, char B)
{
    cout<<A<<"->"<<B<<endl;
}

/* 璇峰湪杩欓噷濉啓绛旀 */
void Hanoi(int n,char A,char B,char C){
    if(n==1) move(A,C);
    else{
        Hanoi(n-1,A,C,B);
        move(A,C);
        Hanoi(n-1,B,A,C);
    }
}