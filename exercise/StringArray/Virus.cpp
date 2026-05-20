#include<iostream>
#include<string.h>
using namespace std;

typedef struct{   
   char ch[600];                //若是非空串，则按串长分配存储区，否则ch为NULL   
   int len;                //串长度   
}HString; 


int Index_BF(HString S,HString T,int pos)
{//返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0
 //其中，T非空，1≤pos≤StrLength(S)
    int i,j;
   i=pos; j=1;
   while(i<=S.len&&j<=T.len)
   {
      if(S.ch[i]==T.ch[j]){++i;++j;}    //继续比较后继字符
      else{i=i-j+2;j=1;}    //指针后退重新开始匹配
   }
   if(j>T.len) return i-T.len;
   else return 0;
}

void DoubleCircularSequence(HString &str);//将环状序列倍增，便于线性处理所有旋转情况
int MatchCircularPattern(HString main, HString doubled_pattern);//在主串中查找环状模式串的所有可能旋转

void Virus_detection()
{
   int flag;
   char Vir[600];
   char temp1[600], temp2[600];  // 临时数组用于接收输入
   HString Virus,Tree;
   while(cin>>temp1>>temp2) //依次检测每对病毒DNA和树木DNA是否匹配
   {
      //判断终止条件
      if(strcmp(temp1,"0")==0 && strcmp(temp2,"0")==0) break;

      //将临时数组内容复制到HString结构（从索引1开始）
      strcpy(Virus.ch+1, temp1);
      strcpy(Tree.ch+1, temp2);
      strcpy(Vir,Virus.ch);
      Virus.len=strlen(Virus.ch)-1;
      Tree.len=strlen(Tree.ch)-1;

      //环状序列匹配处理
      DoubleCircularSequence(Virus);      //倍增处理
      flag=MatchCircularPattern(Tree,Virus); //环状序列匹配
      if(flag)
         cout<<"YES"<<endl;
      else
         cout<<"NO"<<endl;
   }//while
}

int main()
{
    Virus_detection();
    return 0;
}

/* 请在这里填写答案 */

void DoubleCircularSequence(HString &str){
    //将环状序列倍增，便于线性处理所有旋转情况
    int i;
    for(i=1;str.ch[i]!='\0';++i);
    str.len = i-1;
    for(int j = 1; j <= str.len ;  ++j ){
        str.ch[str.len+j] = str.ch[j];
    }
    str.len *= 2;
}
int MatchCircularPattern(HString main, HString doubled_pattern){
    //在主串中查找环状模式串的所有可能旋转
    int n=0;
    HString possible_pattern;
    possible_pattern.len = doubled_pattern.len/2;
    while (n<=doubled_pattern.len/2)
    {
        for(int i=1;i<=doubled_pattern.len/2;++i){
            possible_pattern.ch[i] = doubled_pattern.ch[n+i];
        }
        ++n;
        int m = Index_BF(main,possible_pattern,1);
        if(m!=0) return 1;
    }
    return 0;
}
