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

void print(AMGraph G,int i,int path[]){
    if(i == 0 ) {
        return ;
    }
    print(G,path[i],path);
    cout<<"-->"<<G.vex[i];
}
void ShortestPath_DIJ(AMGraph G,int v0){
    int n = G.vexsnum;
    bool S[n];
    int path[n],D[n];
    int v;
    for(v = 0;v<n;++v){
        S[v] = false;
        D[v] = G.arcs[v0][v];
        if(D[v]<MAXInt) path[v] = v0;
        else path[v] = -1;
    }
    S[v0] = true;
    D[v0] = 0;
    for(int i= 1 ;i<n;++i){
        int min = MAXInt;
        for(int w = 0 ; w<n;++w){
            if(S[w]==0 && D[w]<min){
                v = w;
                min = D[w];                
            }
        }
        S[v] = true;
        for(int w = 0;w<n;++w){
            if(S[w] == 0 && ((D[v]+G.arcs[v][w])<D[w])){
                D[w] = D[v]+ G.arcs[v][w];
                path[w] = v;
            }
        }   
    }
    for(int i=0;i<n;++i){
        cout<<G.vex[i]<<": "<<D[i]<<" "<<G.vex[v0];
        print(G,i,path);
        cout<<endl;
    }
}

int main(){
    AMGraph G;
    createUDN(G);
    char start;
    cin>>start;
    ShortestPath_DIJ(G,LocateVex(G,start));
    return 0;
}