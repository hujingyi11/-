#include<iostream>
using namespace std;
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN + 1];
    int length;
}SString;
void get_next(SString T, int next[]); //KMP绠楁硶涓眰next鏁扮粍
void get_nextval(SString T, int nextval[]); //KMP绠楁硶涓眰nextval鏁扮粍
int main()
{
    int count = 0;
    while (1)
    {
        SString T;
        int next[MAXLEN], nextval[MAXLEN];
        int i;
        cin >> T.ch;
        for (i = 0;T.ch[i] != '\0';i++);
        T.length = i;
        if (i == 1 && T.ch[0] == '0')
        {
            break;
        }
        count++;
        cout << count << ":" << T.ch << " next:" << endl;
        get_next(T, next);
        cout << count << ":" << T.ch << "nextval:" << endl;
        get_nextval(T, nextval);
        cout << endl;
    }
    return 0;
}

/* 璇峰湪杩欓噷濉啓绛旀 */

void get_next(SString T, int next[]){ //KMP绠楁硶涓眰next鏁扮粍
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
    for(int k=1;k<=T.length;k++) cout<<T.ch[k-1]<<":"<<next[k]<<endl;
    cout<<endl;
}
void get_nextval(SString T, int nextval[]){//KMP绠楁硶涓眰nextval鏁扮粍
    int j=0,i=1;
    nextval[1] = 0;
    while(i<=T.length){
        if(j==0 || T.ch[i-1]==T.ch[j-1]){
            ++i;
            ++j;
            if(T.ch[i-1]!=T.ch[j-1]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }else {
            j = nextval[j];
        }
    }
    for(int k=1;k<=T.length;k++) cout<<T.ch[k-1]<<":"<<nextval[k]<<endl;
    cout<<endl;
}