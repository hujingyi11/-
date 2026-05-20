#include<iostream>
#include<string>
#include<map>
#include <cstring>
#include <iomanip>
using namespace std;

typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HUffmanTree;//哈夫曼树

typedef char **HUffmanCode;//哈夫曼编码

// void Select(HUffmanTree &HT,int n,int &s1,int &s2){
//     int i;
//     for( i = 1;i<=n;++i){
//         if(HT[i].parent == 0) {
//             s1 = i;
//             break;
//         }        
//     }//找第一个双亲为零的结点；
//     for(;i<=n;i++){
//         if(HT[i].parent == 0&& HT[i].weight < HT[s1].weight){
//             s1 = i;
//         }
//     }
//     for(i=1;i<=n;i++){
//         if(HT[i].parent == 0 && (i != s1)){
//             s2 = i;
//             break;
//         }
//     }//找第一个双亲为零的结点；且不等于s1；
//     for(;i<=n;++i){
//         if(HT[i].parent == 0 && HT[i].weight<HT[s2].weight){
//             s2 = i;
//         }
//     }
// }

void Select(HUffmanTree &HT, int n, int &s1, int &s2){
    s1 = s2 = 0;
    for(int i = 1; i <= n; i++){
        if(HT[i].parent == 0){
            if(s1 == 0 || HT[i].weight < HT[s1].weight){
                s1 = i;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(HT[i].parent == 0 && i != s1){
            if(s2 == 0 || HT[i].weight < HT[s2].weight){
                s2 = i;
            }
        }
    }
}

void CreateHuffmanTree(HUffmanTree &HT,int weight[],int n){
    if(n<=1) return ;
    int m = 2*n - 1;
    HT = new HTNode[m+1];
    for(int i=1;i<=m;++i){
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(int i=1;i<=n;++i){
        HT[i].weight = weight[i];
    }
    //----------
    //创建哈夫曼树
    int s1,s2;
    for(int i = n+1;i<=m;++i){
        Select(HT,i-1,s1,s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        if(s1>s2) swap(s1,s2);
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    // for(int i=1;i<=m;++i){
    //     cout<<HT[i].weight<<" ";
    // }
    // cout<<endl;
}

void CreateHuffmanCode(HUffmanTree HT,HUffmanCode &HC,int n,int &length){
    HC = new char*[n+1];
    char *cd;
    cd = new char[n];
    cd[n-1] = '\0';
    for(int i = 1; i<=n;++i){
        int start = n-1;
        int c=i,f = HT[i].parent;
        while(f!=0){
            --start;
            if(HT[f].lchild == c) cd[start] = '0';
            else cd[start] = '1';
            c=f;f = HT[f].parent;
        }
        HC[i] = new char[n-start];
        length += (n-start-1)*HT[i].weight;
        strcpy(HC[i],&cd[start]);
    } 
    delete cd;
}

int main(){
    string str;
    getline(cin,str);
    map<char, int> charMap;
    for(char c:str){
        charMap[c]++;
    } 
    int n = charMap.size();    
    int weight[n+1];
    char ch[n+1];
    int i=1;   
    int length = 0;
    for(const auto& pair:charMap){
        weight[i] = pair.second;
        ch[i] = pair.first;
        ++i;
    }
    HUffmanTree HT;
    CreateHuffmanTree(HT,weight,n);
    HUffmanCode HC;
    CreateHuffmanCode(HT,HC,n,length);
    // cout<<n;
    cout<<"--- 哈夫曼编码表 ---"<<endl;
    for(int i = 1;i<=n;++i){
        if(ch[i] == ' ') cout<<"(空格): ";
        else cout<<ch[i]<<": ";
        cout<<HC[i]<<endl;
    }
    cout<<"--- 压缩性能 ---"<<endl;
    cout<<"原始大小: "<<str.size()*8<<" bits ("<<str.size()<<" chars * 8)"<<endl;
    cout<<"压缩大小: "<<length<<" bits"<<endl;
    double percent = (1 - double(length)/double(str.size()*8))*100;
    cout<<fixed<<setprecision(2)<<"压缩率: "<<percent<<"%"<<endl;
    cout<<"--- 编码结果 (二进制流) ---"<<endl;
    for(int i=0;i<str.size();++i){
        int j =1;
        for(const auto &pair : charMap){
            if(str[i] == pair.first) {
                cout<<HC[j];
            }else ++j;
        }
    }
    cout<<endl;
    cout<<"--- 译码验证 ---"<<endl;
    cout<<str;
 }