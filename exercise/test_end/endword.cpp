#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
#include<math.h>
#include <iomanip>
#include <fstream>
using namespace std;
string tag = "uses";
// 单词规范化函数（保持不变）
int Normalize(const char *token, int &pos, char *word) {
    while (token[pos] && !isalpha(token[pos]))
        pos++;

    if (!token[pos])
        return 0;

    int len = 0;
    while (token[pos] && isalpha(token[pos])) {
        word[len++] = tolower(token[pos++]);
    }
    word[len] = '\0';
    return 1;
}

//——————————————————————————————————//
// 策略1 - 主要修复内存管理问题
#define MAXSIZE 100000

typedef struct {
    string *word;
    int length;
    bool *isDup;  // 改为动态分配
}SqList;

void InitSqList(SqList &L){
    L.word = new string[MAXSIZE + 1];
    L.isDup = new bool[MAXSIZE + 1]();  // 动态分配并初始化为false
    L.length = 0;
}

// 释放SqList内存
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


void ListDelete(SqList &L) {
    int newLength = 0;
    for (int i = 1; i <= L.length; ++i) {
        if (!L.isDup[i]) {
            newLength++;
            L.word[newLength] = L.word[i];
            L.isDup[newLength] = false;
        }
    }
    L.length = newLength; 
    for (int i = newLength + 1; i <= L.length; ++i) {
        L.word[i].clear(); 
        L.isDup[i] = false;
    }
}

// int Search_Sep(SqList &L, string key) {
//     int count = 0;
//     for (int i = L.length; i >= 1; --i) {
//         count++;
//         if (L.word[i] == key) break;
//     }
//     return count;
// }

// 改进后的顺序查找函数
// 返回值: 查找成功返回元素位置(>=0)，失败返回-1
// count参数: 返回实际的比较次数
int Search_Sep(SqList &L, string key, int &count) {
    count = 0; // 初始化比较次数
    
    // 从最后一个元素遍历到第一个元素(假设数据从索引0到L.length-1存储)
    for (int i = L.length - 1; i >= 0; --i) {
        count++; // 记录比较次数
        if (L.word[i] == key) {
            return i; // 查找成功，返回位置
        }
    }
    
    return -1; // 查找失败
}

void DeDuplicates(SqList &L) {
    for (int i = 1; i <= L.length; ++i) {
        for (int j = i + 1; j <= L.length; ++j) {
            if (L.word[i] == L.word[j]) L.isDup[j] = true;
        }
    }
    ListDelete(L);
}

void path1_2_prepare(string token, SqList &L) {
    int pos = 0;
    while (token[pos] && L.length < MAXSIZE) {  // 添加长度检查
        char temp[100];  // 使用固定大小缓冲区
        if (Normalize(token.c_str(), pos, temp)) {
            L.length++;
            L.word[L.length] = string(temp);  // 直接赋值，避免resize
        }
    }
}

double ASL_1(SqList L) {
    return double(L.length + 1) / 2;
}

void path1(string token) {
    SqList L;
    InitSqList(L);
    path1_2_prepare(token, L);
    cout << "Total Words: " << L.length << endl;
    DeDuplicates(L);
    cout << "Unique Words: " << L.length << endl;
    cout << "ASL: " << fixed << setprecision(2) << ASL_1(L)<<endl;
    // int count = 0;
    // Search_Sep(L,tag,count);
    // cout<<count;
    DestroySqList(L);  // 释放内存
}

//___________________________________________________________//
// 策略2 - 修复内存泄漏
int Partition(SqList &L, int low, int high) {
    string pivotkey = L.word[low];
    while (low < high) {
        while (low < high && L.word[high] >= pivotkey) --high;
        L.word[low] = L.word[high];
        while (low < high && L.word[low] <= pivotkey) ++low;
        L.word[high] = L.word[low];
    }
    L.word[low] = pivotkey;
    return low;
}

void QSort(SqList &L, int low, int high) {
    if (low < high) {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}

void QuickSort(SqList &L) {
    QSort(L, 1, L.length);
}

int count_Search_Bin(SqList L, string key) {
    int low = 1;
    int high = L.length;
    int count = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        count++;
        if (key == L.word[mid]) return count;
        else if (key < L.word[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return count;
}

double ASL_2(SqList L) {
    QuickSort(L);
    int count = 0;
    for (int i = 1; i <= L.length; ++i) {
        count += count_Search_Bin(L, L.word[i]);
    }
    return (L.length == 0) ? 0.0 : double(count) / L.length;
}

void path2(string token) {
    SqList L;
    InitSqList(L);
    path1_2_prepare(token, L);
    cout << "Total Words: " << L.length << endl;
    DeDuplicates(L);
    cout << "Unique Words: " << L.length << endl;
    cout << "ASL: " << fixed << setprecision(2) << ASL_2(L)<<endl;
    // cout<<count_Search_Bin(L,tag);
    DestroySqList(L);  // 释放内存
}

// 策略3 - 优化内存使用
const unsigned int HASH_SIZE = 1009;

struct HashNode {
    char word[50];
    int count = 0;
    HashNode* next;
};

struct HashTable {
    HashNode* buckets[HASH_SIZE];
    int unique_count = 0;
    int total_count = 0;
};

unsigned int Tran_Hash(const char *str) {
    unsigned int h = 0;
    while (*str) {
        h = (h << 5) + h + *str;
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

void buildHash(HashTable &H, const string& token) {
    InitHashTable(H);
    
    int pos = 0;
    char temp[50];
    
    while (token[pos]) {
        if (Normalize(token.c_str(), pos, temp)) {
            H.total_count++;
            unsigned int i = Tran_Hash(temp);
            HashNode *pNode = H.buckets[i];
            bool found = false;
            
            while (pNode != NULL) {
                if (strcmp(pNode->word, temp) == 0) {
                    pNode->count++;
                    found = true;
                    break;
                }
                pNode = pNode->next;
            }
            
            if (!found) {
                HashNode* newNode = new HashNode();
                strcpy(newNode->word, temp);
                newNode->count = 1;
                newNode->next = H.buckets[i];
                H.buckets[i] = newNode;
                H.unique_count++;
            }
        }
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

double ASL_3(const HashTable &H) {
    if (H.unique_count == 0) return 0.0;
    
    int total_search_count = 0;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = H.buckets[i];
        while (node) {
            total_search_count += Hash_Search(H, node->word);
            node = node->next;
        }
    }
    
    return double(total_search_count) / H.unique_count;
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


void findTopKFrequentWords(const HashTable &H, int k) {
    if (k <= 0) return;
    
    // 创建临时数组存储所有单词和频率
    HashNode** allWords = new HashNode*[H.unique_count];
    int index = 0;
    
    // 收集所有单词
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* currentNode = H.buckets[i];
        while (currentNode != NULL) {
            allWords[index++] = currentNode;
            currentNode = currentNode->next;
        }
    }
    
    // 使用简单排序按频率降序排列[3](@ref)
    for (int i = 0; i < H.unique_count - 1; i++) {
        for (int j = i + 1; j < H.unique_count; j++) {
            if (allWords[j]->count > allWords[i]->count || 
                (allWords[j]->count == allWords[i]->count && 
                 strcmp(allWords[j]->word, allWords[i]->word) < 0)) {
                HashNode* temp = allWords[i];
                allWords[i] = allWords[j];
                allWords[j] = temp;
            }
        }
    }
    
    // 输出前K个单词
    cout << "Top " << k << " most frequent words:" << endl;
    for (int i = 0; i < k && i < H.unique_count; i++) {
        cout << i + 1 << ". " << allWords[i]->word << " (" << allWords[i]->count << " times)" << endl;
    }
    
    delete[] allWords;
}

void path3(string token) {
    HashTable H;
    buildHash(H, token);
    cout << "Total Words: " << H.total_count << endl;
    cout << "Unique Words: " << H.unique_count << endl;
    cout << "ASL: " << fixed << setprecision(2) << ASL_3(H) << endl;
    // findTopKFrequentWords(H,5);
    // cout<<Hash_Search(H,tag);
    DestroyHashTable(H);
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
    getline(cin,token,'#');
    // token = readFileToString3("D:\\cxdownload\\a.txt");
    // cout<<token.length();
    // path1(token);
    // cout<<endl;
    // path2(token);
    // cout<<endl;
    // path3(token);
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
