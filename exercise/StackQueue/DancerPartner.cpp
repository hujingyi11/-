#include <iostream>
using namespace std;

// 跳舞者信息结构体
typedef struct {
    string name;  // 姓名
    char sex;       // 性别：'F'（女性） / 'M'（男性）
} Person;

// 队列相关定义与操作
#define MAXQSIZE 100  // 队列最大容量（可根据需求调整）

typedef struct {
    Person *base;   // 队列存储的基地址（动态数组）
    int front;      // 头指针（指向队头前一个位置）
    int rear;       // 尾指针（指向队尾元素）
} SqQueue;

// 全局队列：分别存放男士和女士
SqQueue Mdancers, Fdancers;

// 初始化队列
bool InitQueue(SqQueue &Q);
// 判断队列是否为空
bool QueueEmpty(SqQueue Q);
// 入队操作
bool EnQueue(SqQueue &Q, Person p);
// 取队头元素
Person GetHead(SqQueue Q);
// 出队操作
bool DeQueue(SqQueue &Q, Person &p);
// 销毁队列（释放内存）
void DestroyQueue(SqQueue &Q);
// 舞伴配对函数
void DancePartner(Person dancer[], int num);
int main() {
    while(1)
    {
        int num;
        cin >> num;
        if (num == 0)
        {
            break;
        }
    
        Person *dancers = new Person[num];  // 动态分配跳舞者数组
    
        for (int i = 0; i < num; i++) {
            cin >> dancers[i].name >> dancers[i].sex;
            // 验证性别输入合法性
            while (dancers[i].sex != 'F' && dancers[i].sex != 'M') {
                cout << "  性别输入错误，请重新输入（F表示女性，M表示男性）：";
                cin >> dancers[i].sex;
            }
        }
    
        DancePartner(dancers, num);
    
        delete[] dancers;  // 释放动态分配的跳舞者数组内存
    }
    return 0;
}
// 初始化队列
bool InitQueue(SqQueue &Q) {
    Q.base = new Person[MAXQSIZE];  // 为队列分配连续内存
    if (Q.base == nullptr) {
        cout << "队列内存分配失败！" << endl;
        return false;
    }
    Q.front = Q.rear = 0;  // 队空标志：front == rear
    return true;
}

// 判断队列是否为空
bool QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 入队操作
bool EnQueue(SqQueue &Q, Person p) {
    // 循环队列满的判定：(rear + 1) % 最大容量 == front
    if ((Q.rear + 1) % MAXQSIZE == Q.front) {
        cout << "队列已满，无法入队！" << endl;
        return false;
    }
    Q.base[Q.rear] = p;  // 将跳舞者信息复制到队尾
    Q.rear = (Q.rear + 1) % MAXQSIZE;  // 尾指针后移（循环处理）
    return true;
}

// 取队头元素
Person GetHead(SqQueue Q) {
    // 先判断队列是否为空
    if (QueueEmpty(Q)) {
        cout << "队列为空，无法获取队头元素！" << endl;
        // 返回一个“空”Person（姓名为空，性别为空格）
        Person emptyPerson;
        emptyPerson.name = "";
        emptyPerson.sex = ' ';
        return emptyPerson;
    }
    // 循环队列中，队头元素位于 front 位置
    return Q.base[Q.front];
}

// 出队操作
bool DeQueue(SqQueue &Q, Person &p) {
    if (QueueEmpty(Q)) {
        cout << "队列为空，无法出队！" << endl;
        return false;
    }
    p = Q.base[Q.front];  // 取出队头跳舞者信息
    Q.front = (Q.front + 1) % MAXQSIZE;  // 头指针后移（循环处理）
    return true;
}

// 销毁队列（释放内存）
void DestroyQueue(SqQueue &Q) {
    if (Q.base != nullptr) {
        delete[] Q.base;  // 释放动态分配的内存
        Q.base = nullptr;
        Q.front = Q.rear = 0;  // 重置指针为队空状态
    }
}


/* 请在这里填写答案 */

void DancePartner(Person dancer[], int num){
    InitQueue(Mdancers);
    InitQueue(Fdancers);
    for(int i = 0;i<num;++i){
        Person p = dancer[i];
         if(p.sex == 'F') EnQueue(Fdancers,p);
         else EnQueue(Mdancers,p);
    }
    Person p;
    cout<<"The dancing partners are:"<<endl;
    while(!QueueEmpty(Mdancers)&&!QueueEmpty(Fdancers)){
        DeQueue(Fdancers,p);
        cout<<p.name<<" ";
        DeQueue(Mdancers,p);
        cout<<p.name<<endl;        
    }
    if(!QueueEmpty(Mdancers)){
        Person p = GetHead(Mdancers);
        cout<<"队头男士的姓名："<<" "<<p.name<<endl;
    }
        if(!QueueEmpty(Fdancers)){
        Person p = GetHead(Fdancers);
        cout<<"队头女士的姓名："<<" "<<p.name<<endl;
    }
}
   