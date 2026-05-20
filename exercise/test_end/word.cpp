#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
#include<math.h>
#include <iomanip>
#include <fstream>
using namespace std;

// 单词规范化函数（使用此标准实现）
// 功能：从token的pos位置开始提取下一个单词（仅字母，转小写）
// 参数：token-输入串，pos-当前位置（会被更新），word-输出单词
// 返回：1=成功提取单词，0=token处理完毕
int Normalize(const char *token, int &pos, char *word) {
    // 跳过非字母字符
    while (token[pos] && !isalpha(token[pos]))
        pos++;

    if (!token[pos])
        return 0; // token结束

    // 提取连续字母并转小写
    int len = 0;
    while (token[pos] && isalpha(token[pos])) {
        word[len++] = tolower(token[pos++]);
    }
    word[len] = '\0';
    return 1;
}
//——————————————————————————————————//
//策略1
#define MAXSIZE 10000
typedef struct {
    string *word;
    int length;
    bool *isDup; 
}SqList;

void InitSqList(SqList &L){
    L.word = new string [MAXSIZE+1];
    if(!L.word) return ;
    L.length = 0;
}

void DestroySqList(SqList &L) {
    if (L.word) {
        delete[] L.word;
        L.word = NULL;
    }
    if (L.isDup) {
        delete[] L.isDup;
        L.isDup = NULL;
    }
    L.length = 0;
}

void ListDelete(SqList &L,int i){
    for( ;i<=L.length;++i){
        if(L.isDup[i] == true) break;
        if(i==L.length-1&&L.isDup[i]==false) return ;
    }
    for(int j=i;j<=L.length-1;++j){
        L.word[j] = L.word[j+1];
        L.isDup[j] = L.isDup[j+1];
    }
    L.length--;
    if(i>L.length) return ;
    ListDelete(L,i);
}
int Search_Sep(SqList &L,string key){
    for(int i=L.length;i>=0;--i){
        if(L.word[i] == key) return i;
    }
    return -1;
}
void DeDuplicates(SqList &L){
    for(int i = 1;i<=L.length;++i){
        for(int j=i+1;j<=L.length;++j){
            if(L.word[i] == L.word[j]) L.isDup[j] = true;
        }
    }
    ListDelete(L,1);
}

void path1_2_prepare(string token,SqList &L){
    int pos =0 ;
    while(token[pos]){
        L.word[L.length+1].resize(token.length());//预设长度；
        char *word = &L.word[L.length+1][0];//获取指向字符串内部缓冲区的可写指针
        Normalize(token.c_str(),pos,word);
        if(token[pos]) L.length++;
    }
}

double ASL_1(SqList L){
    return double(L.length+1)/2;
}
void path1(string token){
    SqList L;
    InitSqList(L);
    path1_2_prepare(token,L);
    // for(int i = 0;i<L.length;++i)
    //     cout<<i+1<<L.word[i]<<endl;
    cout<<"Total Words: "<<L.length<<endl;
    DeDuplicates(L);
    cout<<"Unique Words: "<<L.length<<endl;
    // for(int i = 0;i<L.length;++i)
    //     cout<<L.word[i]<<" ";
    cout<<"ASL: "<<fixed<<setprecision(2)<<ASL_1(L);
    DestroySqList(L);
}
//___________________________________________________________//
//策略2
int Partition(SqList &L,int low,int high){
    L.word[0] = L.word[low];
    string pivotkey = L.word[low];
    while(low<high){
        while(low<high&&L.word[high]>=pivotkey) --high;
        L.word[low] = L.word[high];
        while(low<high&&L.word[low]<=pivotkey) ++low;
        L.word[high] = L.word[low];
    }
    L.word[low] = L.word[0];
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

int count_Search_Bin(SqList L,string key){
    int low = 1;
    int high = L.length;
    int count = 0;
    while(low<=high) {
        int mid = (low + high) / 2;
        count++;
        if(key == L.word[mid]) return count;
        else if(key<L.word[mid]) high = mid -1;
        else low = mid +1; 
    }
    return 0;
}
double ASL_2(SqList L){
    QuickSort(L);
    int count = 0;
    for(int i=1;i<=L.length;++i){
        count += count_Search_Bin(L,L.word[i]);
    }
    double ASL = double(count) / L.length;
    return ASL;
}
void path2(string token){
    SqList L;
    InitSqList(L);
    path1_2_prepare(token,L);
    cout<<"Total Words: "<<L.length<<endl;
    DeDuplicates(L);
    cout<<"Unique Words: "<<L.length<<endl;
    cout<<"ASL: "<<fixed<<setprecision(2)<<ASL_2(L);
    DestroySqList(L);
}


//策略3
//——————————————————————————————————————————————————//
const unsigned int HASH_SIZE = 1009;

struct HashNode {
    char word[50];      // 单词
    int count = 0;      // 词频
    HashNode* next;     // 指向下一个节点（链表法）
};

struct HashTable {
    HashNode* buckets[HASH_SIZE];  // 哈希表大小固定为1009
    int unique_count = 0;          // 不同词数
    int total_count = 0;            // 总词数（包括重复）
};

// 将单词转化为数值
unsigned int Tran_Hash(const char *str) {
    unsigned int h = 0;
    while (*str) {
        h = (h << 5) + h + *str;  // h = h*33 + c
        str++;
    }
    return h % HASH_SIZE;
}

void InitHashTable(HashTable &H) {
    H.unique_count = 0;
    H.total_count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        H.buckets[i] = NULL;
    }
}

// 计算单词数量
int countWords(const char* token) {
    int count = 0;
    int pos = 0;
    char temp[50];
    
    while (token[pos]) {
        if (Normalize(token, pos, temp)) {
            count++;
        }
    }
    return count;
}

void prepare_3(const string& token, string* words) {
    int pos = 0;
    int n = 0;
    char temp[50];   
    while (token[pos]) {
        if (Normalize(token.c_str(), pos, temp)) {
            words[n] = string(temp);
            n++;
        }
    }
    // 设置结束标记
    words[n] = "";
}

void buildHash(HashTable &H, const string& token, string* words) {
    prepare_3(token, words);
    InitHashTable(H);
    
    int n = 0;
    while (words[n] != "") {
        H.total_count++;
        unsigned int i = Tran_Hash(words[n].c_str());
        HashNode *pNode = H.buckets[i];
        bool found = false;
        while (pNode != NULL) {
            if (strcmp(pNode->word, words[n].c_str()) == 0) {
                pNode->count++;
                found = true;
                break;
            }
            pNode = pNode->next;
        }
        if (!found) {
            HashNode* newNode = new HashNode();
            strcpy(newNode->word, words[n].c_str());
            newNode->count = 1;
            newNode->next = H.buckets[i];
            H.buckets[i] = newNode;
            H.unique_count++;
        }
        n++;
    }
}

int Hash_Search(const HashTable &H, const string& word) {
    int search_count = 0;
    unsigned int i = Tran_Hash(word.c_str());
    HashNode *pNode = H.buckets[i];
    
    while (pNode) {
        search_count++;
        if (strcmp(pNode->word, word.c_str()) == 0)
            break;
        pNode = pNode->next;
    }
    return search_count;
}

double ASL_3(const HashTable &H, string* words) {
    int total_search_count = 0;
    int n = 0;
    string* unique_words = new string[H.unique_count];
    int unique_index = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = H.buckets[i];
        while (node) {
            unique_words[unique_index++] = node->word;
            node = node->next;
        }
    }
    for (int i = 0; i < H.unique_count; i++) {
        total_search_count += Hash_Search(H, unique_words[i]);
    }
    delete[] unique_words;
    
    return (H.unique_count == 0) ? 0.0 : double(total_search_count) / H.unique_count;
}

void DestroyHashTable(HashTable &H) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = H.buckets[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
        H.buckets[i] = NULL;
    }
    H.unique_count = 0;
    H.total_count = 0;
}

void path3(string token) {
    int word_count = countWords(token.c_str());
    string* words = new string[word_count + 1]; 
    HashTable H;
    buildHash(H, token, words);    
    cout << "Total Words: " << H.total_count << endl;
    cout << "Unique Words: " << H.unique_count << endl;
    cout << "ASL: " << fixed << setprecision(2) << ASL_3(H, words) << endl;
    DestroyHashTable(H);
    delete[] words;
}

std::string readFileToString3(const std::string& filename) {
    std::ifstream file(filename);
    std::string content;
    std::string line;

    if (!file.is_open()) {
        return "";
    }

    while (std::getline(file, line)) {
        content += line + "\n"; // 需要手动添加换行符
    }
    file.close();
    return content;
}

int main(){
    int n;
    cin>>n;
    string token;
    // getline(cin,token,'#');
    token = readFileToString3("C:\\Users\\32489\\Downloads\\2.txt");
    // cout<<token.length();

    switch(n){
        case 1: path1(token);
                break;
        case 2: path2(token);
                break;
        case 3: path3(token);
                break;
    }
    return 0;
}

