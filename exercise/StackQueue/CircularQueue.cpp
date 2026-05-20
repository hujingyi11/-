#include <iostream>
using namespace std;

// 定义循环队列的最大容量
#define MAXSIZE 100

// 循环队列结构体定义
typedef struct {
    int *Q;          // 动态分配的数组，存储队列元素
    int front;       // 队头指针
    int rear;        // 队尾指针
    int tag;         // 标志位：0表示队空，1表示队满（当front==rear时）
    int maxSize;     // 队列的最大容量
} CircularQueue;

// 初始化循环队列
// 参数：queue - 队列指针，m - 队列容量
void initQueue(CircularQueue *queue, int m);
// 判断队列是否为空
// 返回值：1表示空，0表示非空
int isEmpty(CircularQueue *queue);
// 判断队列是否为满
// 返回值：1表示满，0表示非满
int isFull(CircularQueue *queue);
// 入队操作（插入元素）
// 参数：queue - 队列指针，element - 要插入的元素
// 返回值：1表示插入成功，0表示插入失败（队列已满）
int enqueue(CircularQueue *queue, int element);
// 出队操作（删除元素）
// 参数：queue - 队列指针，element - 指向保存删除元素的指针
// 返回值：1表示删除成功，0表示删除失败（队列为空）
int dequeue(CircularQueue *queue, int *element);
// 获取队列中的元素个数
int getSize(CircularQueue *queue);
// 显示队列中的所有元素（用于测试）
void displayQueue(CircularQueue *queue);
// 销毁队列，释放内存
void destroyQueue(CircularQueue *queue);
int main()
{
    while(1)
    {
        int p, n, i, a[100];
        CircularQueue q;  // 定义循环队列实例
        // 初始化队列，指定容量为MAXSIZE
        initQueue(&q, MAXSIZE);
        cin >> n;
        if(n == 0)  // 输入n=0时结束循环
        {
            break;
        }
        // 读取n个元素并依次入队
        for(i = 0; i < n; i++)
        {
            cin >> a[i];
            enqueue(&q, a[i]);  // 传入队列指针和元素
        }
        // 依次出队并输出，前n-1个元素后加空格
        for(i = 0; i < n - 1; i++)
        {
            dequeue(&q, &p);  // 传入队列指针和保存结果的指针
            cout << p << " ";
        }
        // 输出最后一个元素
        dequeue(&q, &p);
        cout << p << endl;
        // 销毁队列，释放内存
        destroyQueue(&q);
    }
    return 0;
}
// 初始化循环队列
// 参数：queue - 队列指针，m - 队列容量
void initQueue(CircularQueue *queue, int m) {
    queue->Q = new int[m];      // 动态分配数组空间
    queue->front = 0;            // 队头指针初始化为0
    queue->rear = 0;             // 队尾指针初始化为0
    queue->tag = 0;              // 标志位初始化为0，表示队列为空
    queue->maxSize = m;          // 设置队列最大容量
}

// 判断队列是否为空
// 返回值：1表示空，0表示非空
int isEmpty(CircularQueue *queue) {
    // 当front==rear且tag==0时，队列为空
    return (queue->front == queue->rear && queue->tag == 0);
}

// 判断队列是否为满
// 返回值：1表示满，0表示非满
int isFull(CircularQueue *queue) {
    // 当front==rear且tag==1时，队列为满
    return (queue->front == queue->rear && queue->tag == 1);
}


// 获取队列中的元素个数
int getSize(CircularQueue *queue) {
    if (queue->tag == 1 && queue->front == queue->rear) {
        // 队列满
        return queue->maxSize;
    } else if (queue->tag == 0 && queue->front == queue->rear) {
        // 队列空
        return 0;
    } else {
        // 一般情况
        return (queue->rear - queue->front + queue->maxSize) % queue->maxSize;
    }
}

// 显示队列中的所有元素（用于测试）
void displayQueue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        cout << "队列为空" << endl;
        return;
    }
    
    cout << "队列元素: ";
    int i = queue->front;
    int count = getSize(queue);
    
    for (int j = 0; j < count; j++) {
        cout << queue->Q[i] << " ";
        i = (i + 1) % queue->maxSize;
    }
    cout << endl;
}


/* 请在这里填写答案 */

// 入队操作（插入元素）
// 参数：queue - 队列指针，element - 要插入的元素
// 返回值：1表示插入成功，0表示插入失败（队列已满）
int enqueue(CircularQueue *queue, int element){
    if(isFull(queue) == 1) return 0;
    queue->Q[queue->rear] = element;
    queue->rear = (queue->rear+1)%MAXSIZE;
    if(queue->rear == queue->front) queue->tag = 1;
    return 1;
}

// 出队操作（删除元素）
// 参数：queue - 队列指针，element - 指向保存删除元素的指针
// 返回值：1表示删除成功，0表示删除失败（队列为空）
int dequeue(CircularQueue *queue, int *element){
    if(isEmpty(queue) == 1) return 0;
    *element = queue->Q[queue->front];   
    queue->front = (queue->front + 1) % MAXSIZE;
    if(queue->front == queue->rear) queue->tag = 0;
    return 1;
}

// 销毁队列，释放内存
void destroyQueue(CircularQueue *queue){
    delete[] queue->Q;
}