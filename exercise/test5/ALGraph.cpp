#include<iostream>
using namespace std; 
#define MVNum 100
#define MAXInt 32567
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
    int data;
    ArcNode *firstarc;
}VNode,AdjList[MVNum];
typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

int LocateVex(ALGraph G,int n){
    for(int i =0;i<G.vexnum;i++)
        if(G.vertices[i].data == n) 
            return i;
    return -1;
}

void CreateUDG(ALGraph &G){
    int v1,v2;
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;++i){
        G.vertices[i].data = i;
        G.vertices[i].firstarc = NULL;
    }
    for(int k = 0; k<G.arcnum;k++){
        cin>>v1>>v2;
        int i = LocateVex(G,v1);
        int j = LocateVex(G,v2);
        ArcNode *p1;
        p1 =new ArcNode;
        p1->adjvex = j;
        p1->nextarc = NULL;
        if(!G.vertices[i].firstarc)
            G.vertices[i].firstarc = p1;
        else{
            ArcNode *rear = G.vertices[i].firstarc;
            while(rear->nextarc){
                rear = rear->nextarc;
            }
            rear->nextarc = p1;
        }
    }
}

void output(ALGraph G){
    for(int i = 0;i<G.vexnum;++i){
        cout<<G.vertices[i].data;
        while(G.vertices[i].firstarc){
            cout<<" -> "<<G.vertices[i].firstarc->adjvex;
            G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;
        }
        cout<<endl;
    }
}

bool visited[MVNum];
void setup(){
    for(int i = 0;i<MVNum;++i)
        visited[i] = 0;
}
void DFS_AL(ALGraph G,int v){
    cout<<" "<<v;
    visited[v] = 1;
    ArcNode *p = G.vertices[v].firstarc;
    while(p){
        int w = p->adjvex;
        if(visited[w] == 0) DFS_AL(G,w);
        p=p->nextarc;
    }

}

typedef struct {
    int *base; //初始化时动态分配存储空间
    int front;       //头指针
    int rear;        //尾指针
} SqQueue;

void InitQueue(SqQueue &Q){
    Q.base = new int [MAXInt];
    if(!Q.base) exit(0);
    Q.front = Q.rear =0;
}

void EnQueue(SqQueue &Q,int e){
    if((Q.rear + 1) % MAXInt == Q.front)
        cout<<"FULL"<<endl;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear +1) % MAXInt;
}


void DeQueue(SqQueue & Q,int  &e){
    if(Q.front == Q.rear) exit(0);
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXInt;
}

// int FirstAdjVex(ALGraph G,int u){
//     for(int i= 0 ;i<G.vexnum;++i){
//         if(G.vertices[i].data == u) 
//             return i;
//     }
//     return -1;
// }

// int NextAdjVex(ALGraph G,int u,int w){
//     for(int i= 0 ;i<G.vexnum;++i){
//         if(G.vertices[i].data == u) 
//             return G.vertices[i].firstarc->adjvex;
//     }
//     return -1;
// }
// void BFS(ALGraph G,int v){
//     cout<<" "<<v;
//     visited[v] = 1;
//     SqQueue Q;
//     InitQueue(Q);
//     EnQueue(Q,v);
//     int u,w;
//     while(Q.front != Q.rear){
//         DeQueue(Q,u);
//         for(w = FirstAdjVex(G,u);w>=0;w= NextAdjVex(G,u,w))
//             if(visited[w] == 0){
//                 cout<<" "<<w;
//                 visited[w] = 1;
//                 EnQueue(Q,w);
//             }
//     }
// }

void BFS(ALGraph G, int v) {
    cout << " " << v;
    visited[v] = 1;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    int u;
    while (Q.front != Q.rear) { // 队列非空时循环
        DeQueue(Q, u);
        // 直接遍历顶点 u 的邻接表
        ArcNode* p = G.vertices[u].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            if (visited[w] == 0) {
                cout << " " << w;
                visited[w] = 1; // 标记已访问并入队
                EnQueue(Q, w);
            }
            p = p->nextarc; // 移动到下一个邻接点
        }
    }
}

int main(){
    ALGraph G;
    CreateUDG(G);
    cout<<"Adjacency List:"<<endl;
    output(G);
    int v;
    cin>>v;
    cout<<"DFS Traversal:";
    DFS_AL(G,v);
    cout<<endl;
    cout<<"BFS Traversal:";
    setup();
    BFS(G,v);
    return 0;
}

