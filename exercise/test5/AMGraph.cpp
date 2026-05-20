#include<iostream>
using namespace std;
#define MAXInt 32567
#define MVNum 100
typedef struct {
    int vexs[MVNum];
    int arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AMGraph;   

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

void CreateUDN(AMGraph &G){
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;++i)
        G.vexs[i] = i;
    for(int i=0;i<G.vexnum;++i)
        for(int j=0;j<G.vexnum;++j)
            G.arcs[i][j] = 0;
    int u,v;
    for(int i=0;i<G.arcnum;i++){
        cin>>u>>v;
        G.arcs[u][v] = 1;
        G.arcs[v][u] = 1;
    }
}

bool visited[MVNum];
void DFS_AM(AMGraph G,int v){
    cout<<" "<<v;
    visited[v] = true;
    for(int u = 0;u<G.vexnum;u++){
        if(G.arcs[v][u] == 1 && visited[u] == false) DFS_AM(G,u);
    }
}

void BFS_AM(AMGraph G, int v){
    cout<<v;
    visited[v] = true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q,v);
    int u,w;
    while(Q.front != Q.rear) {
        DeQueue(Q,u);
        for(w = 0;w<G.vexnum;++w)       
            if(visited[w] == false && G.arcs[u][w] == 1){
                cout<<' '<<w;
                visited[w] = true;
                EnQueue(Q,w);
            }
    }
}

//  for(int w = 0; w < G.vexnum; ++w) {
// // 如果顶点w与当前顶点相邻且未被访问[5](@ref)
// if(G.arcs[current][w] == 1 && !visited[w]) {
//     cout << w << " ";
//     visited[w] = true;
//     Q.push(w); // 将未访问的邻接点入队[4](@ref)
int main(){
    AMGraph G;
    CreateUDN(G);
    int n;
    cin>>n;
    cout<<"Adjacency Matrix:"<<endl;
    for(int i=0;i<G.vexnum;++i){
        for(int j=0;j<G.vexnum-1;++j)
            cout<<G.arcs[i][j]<<" ";
        cout<<G.arcs[i][G.vexnum-1];
        cout<<endl;        
    }
    cout<<"DFS Traversal:";
    DFS_AM(G,n);
    for(int i =0;i<G.vexnum;++i)
        visited[i] = false;
    cout<<endl;
    cout<<"BFS Traversal: ";
    BFS_AM(G,n);
    return 0;
}