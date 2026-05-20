#include<iostream>
using namespace std;
#define MAXSIZE 10000
typedef struct
{
    char ch[MAXSIZE];
    int length;
}SString;

void getnext(SString st,int next[]){
    int j=0,i=1;
    next[1] = 0;
    while(i<=st.length){
        if(j==0||st.ch[j-1]==st.ch[i-1]){
            ++j;
            ++i;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

void output_next(SString st,int next[],int n){
    cout<<st.ch<<" next: [";
    for(int i = 1;i<n;++i){
        cout<<next[i]<<", ";
    }
    cout<<next[n]<<"]";
}

void getnextval(SString st,int nextval[]){
    int j=0,i=1;
    nextval[1] = 0;
    while(i<=st.length){
        if(j==0||st.ch[j-1]==st.ch[i-1]){
            ++j;
            ++i;
            if(st.ch[i-1] != st.ch[j-1]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }else{
            j = nextval[j];
        }
    }
}

void output_nextval(SString st,int nextval[],int n){
    cout<<st.ch<<" nextval: [";
    for(int i = 1;i<n;++i){
        cout<<nextval[i]<<", ";
    }
    cout<<nextval[n]<<"]";
}

int next_count = 0;
int kmp_next(SString S,SString T,int pos){
    int i = pos, j = 1;
    int next[MAXSIZE];
    getnext(T,next);
    while(i<=S.length && j<=T.length){
        if(j==0||S.ch[i-1] == T.ch[j-1]){    
            ++i;
            ++j;
        }else{
            j = next[j];
        }
        if(j!=0) next_count++;
    }
    // if(j>=T.length) {
    //     cout<<i-T.length-1<<endl;
    //     return i-T.length-1;
        
    // }
    if(j>=T.length) return i-T.length-1;
    return -1;
}

int nextval_count = 0;
int kmp_nextval(SString S,SString T,int pos){
    int i = pos, j = 1;
    int nextval[MAXSIZE];
    getnextval(T,nextval);
    while(i<=S.length && j<=T.length){
        if(j==0||S.ch[i-1] == T.ch[j-1]){        
            ++i;
            ++j;
        }else{           
            j = nextval[j];
        } 
        if(j!=0) nextval_count++;
    }
    if(j>=T.length) return i-T.length-1;
     return -1;
}

int noise_count = 0;
void NoiseFiltering(SString &signal,SString noise,int pos){
    int a1 = kmp_next(signal,noise,pos);
    int a2 = kmp_nextval(signal,noise,pos);
    if(a1 != -1) {
        noise_count++;
        signal.ch[a1] = '*';
        for(int i=0;i<signal.length-a1-noise.length;++i){
            signal.ch[i+1+a1] = signal.ch[i+a1+noise.length] ;
        }
        signal.length = signal.length - noise.length +1;
        // for(int i=0;i<signal.length;++i){
        //     cout<<signal.ch[i];
        // }
        // cout<<endl;
        NoiseFiltering(signal,noise,a1+1);
    }
}
// 10 3 10-3-1
void Synchronization(SString head,SString noise,SString &signal){
    int ad1 = kmp_next(signal,head,0);
    int ad2 = kmp_nextval(signal,head,0);
    for(int i=0;i<signal.length-ad1-head.length;++i){
        signal.ch[i] = signal.ch[i+ad1+head.length];
    }
    signal.length = signal.length - ad1-head.length;
    // for(int i=0;i<signal.length;++i){
    //     cout<<signal.ch[i];
    // }
    // cout<<endl;
    next_count=0;
    nextval_count=0;
    noise_count = 0;
    NoiseFiltering(signal,noise,0);
    if(ad1 == -1) {
        cout<<"No Sync"<<endl;
        return ;
    }else{
        cout<<"Noise Compare - next: "<<next_count-1-noise_count<<", nextval: "<<nextval_count-1-noise_count<<endl;
        cout<<"Start: "<<ad1+head.length<<", Noise Count: "<<noise_count<<", Cleaned: ";
        for(int i=0;i<signal.length;++i){
            cout<<signal.ch[i];
        }
        cout<<endl;
    }
}
int main(){
    int n,i;
    cin>>n;
    SString head,noise,signal;
    while(n != 0){
        cin>>head.ch>>noise.ch>>signal.ch;
        for(i=0;noise.ch[i] != '\0';++i);
        noise.length = i;
        for(i=0;head.ch[i] != '\0';++i);
        head.length = i;
        for(i=0;signal.ch[i] != '\0';++i);
        signal.length = i;
        int next[MAXSIZE],nextval[MAXSIZE];
        getnext(noise,next);
        getnextval(noise,nextval);
        output_next(noise,next,noise.length);
        cout<<endl;
        output_nextval(noise,nextval,noise.length);
        cout<<endl;
        Synchronization(head,noise,signal);
        --n;
    }
    return 0;
}
