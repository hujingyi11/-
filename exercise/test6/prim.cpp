#include<iostream>
using namespace std;

#define MVnum 20
#define MAXInt 100
typedef struct {
    char vexs[MVnum];
    int arcs[MVnum][MVnum];
    int vexsnum,arcsnum;
}AMGraph;

int LocateVex(AMGraph G,char v){
    for(int i=0;i<G.vexsnum;++i)
        if(G.vexs[i] == v) return i;
    return -1;
}
void createUDN(AMGraph &G){
    char u,v;
    int w;
    cin>>G.vexsnum>>G.arcsnum;
    for(int i=0;i<G.vexsnum;++i)
        cin>>G.vexs[i];
    for(int i=0;i<G.vexsnum;++i)
        for(int j=0;j<G.vexsnum;++j)
            G.arcs[i][j] = 0;
    for(int i=0;i<G.arcsnum;++i){
        cin>>u>>v>>w;
        int j=LocateVex(G,u);
        int k=LocateVex(G,v);
        G.arcs[j][k] = w;
        G.arcs[k][j] = w;
    }
}

struct array{
    char adjvex;
    int lowcost;
}closedge[MVnum];

int Min(array a[],int n){
    int min;
    int i;
    for(i = 0;i<n;++i){
        if(closedge[i].lowcost != 0){
            min = i;    break;         
        }
 
              
    }        
    for(i=0;i<n;++i)
        if(closedge[i].lowcost != 0){
            if(closedge[i].lowcost<closedge[min].lowcost){
                min = i;
            }            
        }
    return min;
}
void MiniSpanTree_Prim(AMGraph G,char u){
    int k=LocateVex(G,u);
    for(int j =0;j<G.vexsnum;++j)
        if(j != k) closedge[j] = {u,G.arcs[k][j]};
    closedge[k].lowcost = 0;
    for(int i = 1;i<G.vexsnum;++i){
        k=Min(closedge,G.vexsnum);
        char u0 = closedge[k].adjvex;
        char v0 = G.vexs[k];
        cout<<u0<<"--->"<<v0<<endl;
        closedge[k].lowcost = 0;
        for(int j=0;j<G.vexsnum;++j)
            if(closedge[j].lowcost != 0 &&G.arcs[k][j]<closedge[j].lowcost)
                closedge[j] = {G.vexs[k],G.arcs[k][j]};
    }
}

int main(){
    AMGraph G;
    createUDN(G);
    MiniSpanTree_Prim(G,G.vexs[0]);
    return 0;
}