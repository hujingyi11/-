#include<iostream>
using namespace std;

#define MAXInt 100
#define MVNum 20

typedef struct {
    char vex[MVNum];
    int arcs[MAXInt][MAXInt];
    int vexsnum,arcsnum;
}AMGraph;

int LocateVex(AMGraph G,char v){
    for(int i = 0; i<G.vexsnum; ++i){
        if(G.vex[i] == v) return i;
    }
    return -1;
}

void createUDN(AMGraph &G){
    cin>>G.vexsnum>>G.arcsnum;
    for(int i = 0;i<G.vexsnum;++i)
        cin>>G.vex[i];
    for(int i = 0;i<G.vexsnum;++i)
        for(int j=0;j<G.vexsnum;++j)
            G.arcs[i][j] = MAXInt;
    for(int i = 0;i<G.arcsnum;++i){
        char u,v;
        cin>>u>>v;
        int j = LocateVex(G,u);
        int k = LocateVex(G,v);
        cin>>G.arcs[j][k];
    }
}

void print(AMGraph G,int path[][MVNum], int start ,int end){
    if(start == end) {
        cout<<G.vex[start];
        return ;
    }
    if(path[start][end] == -1) {
        cout<<"无法从 "<<G.vex[start]<<" 到达 "<<G.vex[end];
    }
    print(G,path,start,path[start][end]);
    cout<<"-->"<<G.vex[end];
}

void ShortestPath_Floyd(AMGraph G,int start,int end){
    int D[MVNum][MVNum];
    int path[MVNum][MVNum];
    for(int i = 0 ;i<G.vexsnum;++i)
        for(int j = 0 ;j<G.vexsnum;++j){
            D[i][j] = G.arcs[i][j];
            if(D[i][j]<MAXInt && i!= j) path[i][j] = i;
            else path[i][j]=-1;
        }
    for(int k=0;k<G.vexsnum;++k)
        for(int i=0;i<G.vexsnum;++i)
            for(int j=0;j<G.vexsnum;++j)
                if(D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[k][j];
                }
    print(G,path,start,end);
    if(path[start][end] != -1){
        cout<<endl;
        cout<<"最短路径的长度为:"<<D[start][end];
    }
}

int main(){
    AMGraph G;
    createUDN(G);
    char v1,v2;
    cin>>v1>>v2;
    ShortestPath_Floyd(G,LocateVex(G,v1),LocateVex(G,v2));
    return 0;
}