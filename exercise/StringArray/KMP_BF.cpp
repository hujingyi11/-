#include<iostream>
using namespace std;
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN+1];
    int length;
}SString;
int Index_KMP(SString S,SString T,int pos);  //模式匹配算法——KMP算法
int Index_BF(SString S,SString T,int pos); //模式匹配算法——BF（Brute Force）算法
int main()
{
    while(1)
    {
        SString S,T;
        int a,b,i,j,pos;
        cin>>S.ch>>T.ch;
        for(i=0;S.ch[i]!='\0';i++);
        S.length = i;
        for(j=0;T.ch[j]!='\0';j++);
        T.length = j;
        if((i==1&&S.ch[0]=='0')&&(j==1&&T.ch[0]=='0'))
        {
            break;
        }
        pos=1;
        a=Index_KMP(S,T,pos);
        cout<<"KMP算法："<<(a-1)<<endl;
        b=Index_BF(S,T,pos);
        cout<<"BF算法："<<(b-1)<<endl;
    }
    return 0;
}

/* 请在这里填写答案 */
void get_next(SString T, int next[]){ //KMP算法中求next数组
    int j=0,i=1;
    next[1] = 0;
    while(i<=T.length){
        if(j==0 || T.ch[i-1]==T.ch[j-1]){
            ++i;
            ++j;
            next[i] = j;
        }
        else j = next[j];
    }
}

int Index_KMP(SString S,SString T,int pos){
    int i = pos,j = 1;
    int next[MAXLEN+1];
    get_next(T,next);
    while(i<=S.length && j<=T.length){
        if(j==0||S.ch[i-1] == T.ch[j-1]){i++; j++;}
        else j=next[j];
    }
    if(j > T.length) return i-T.length;
    return 0;
}

int Index_BF(SString S,SString T,int pos){
    int i = pos,j = 1;
    while(i<=S.length && j<=T.length){
        if(S.ch[i-1] == T.ch[j-1]){i++; j++;}
        else{i = i-j+2;j=1;}
    }
    if(j > T.length) return i-T.length;
    return 0;
}