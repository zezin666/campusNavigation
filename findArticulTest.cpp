#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<string.h>
#include<algorithm>
using namespace std;
#define Max 50
#define MX 999999
typedef struct Ver{
    char num[5];
}Ver;
typedef struct{
    Ver vex[Max];
    int arcs[Max][Max];
    int vnum,arcnum;
    bool edge[Max][Max];
}AMGragh;
void DFS(AMGragh G, int v, bool visited[], int &time, int dfn[], int low[], int parent[], bool isCut[]){
    visited[v] = true; // 标记v已访问
    time++; // 访问时间加一
    dfn[v] = low[v] = time; // 初始化v的访问顺序和最早能到达的顶点为time
    int children = 0; // 记录v的子树个数
    for(int w = 0; w < G.vnum; w++){ 
        if(G.edge[v][w]){ // 如果v和w有边相连
            if(!visited[w]){ // 如果w没有被访问过
                children++; // 子树个数加一
                parent[w] = v; // 记录w的父节点为v
                DFS(G, w, visited, time, dfn, low, parent, isCut); // 递归访问w
                low[v] = min(low[v], low[w]); // 更新v能到达的最早顶点
                if(parent[v] == -1 && children > 1){ // 如果v是根节点且有多于一个子树，那么v是割点
                    isCut[v] = true;
                }
                if(parent[v] != -1 && low[w] >= dfn[v]){ // 如果v不是根节点且w不能到达比v更早的顶点，那么v是割点
                    isCut[v] = true;
                }
            }
            else if(w != parent[v]){ // 如果w已经被访问过且不是v的父节点，那么说明存在回边
                low[v] = min(low[v], dfn[w]); // 更新v能到达的最早顶点
            }
        }
    }
}
bool isArticul(AMGragh G, int v){
    bool visited[Max]; 
    int time = 0; // 记录访问时间
    int dfn[Max]; // 记录每个顶点的访问顺序
    int low[Max]; // 记录每个顶点能到达的最早顶点
    int parent[Max]; // 记录每个顶点的父节点
    bool isCut[Max]; // 记录每个顶点是否是割点
    for(int i = 0; i < G.vnum; i++){
        visited[i] = false; // 初始化所有顶点为未访问
        parent[i] = -1; // 初始化所有顶点的父节点为-1
        isCut[i] = false; // 初始化所有顶点不是割点
    }
    DFS(G, v, visited, time, dfn, low, parent, isCut); // 从v开始深度优先搜索
    return isCut[v]; // 返回v是否是割点
}

void findArticul(AMGragh G){
    printf("The articulation points of AMGragh are:\n");
    for(int v = 0; v < G.vnum; v++){
        if(isArticul(G, v)){ 
            cout<<v<<" ";
        }
    }
    printf("\n");
}
void CreateUDG(AMGragh &G){
    G.vnum=7;
    strcpy(G.vex[0].num,"01");
    strcpy(G.vex[1].num,"02");
    strcpy(G.vex[2].num,"03");
    strcpy(G.vex[3].num,"04");
    strcpy(G.vex[4].num,"05");
    strcpy(G.vex[5].num,"06");
    strcpy(G.vex[6].num,"07");
    G.arcs[1][0]=G.arcs[0][1]=1;
    G.arcs[0][2]=G.arcs[2][0]=1;
    G.arcs[1][3]=G.arcs[3][1]=1;
    G.arcs[2][3]=G.arcs[3][2]=1;
    G.arcs[3][4]=G.arcs[4][3]=1;
    G.arcs[3][5]=G.arcs[5][3]=1;
    G.arcs[5][6]=G.arcs[6][5]=1;
    for (int i = 0; i < G.vnum; i++){
        for (int j = 0; j < G.vnum; j++){
            G.edge[i][j] = true;
        }
    }
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++){
            if(G.arcs[i][j]==0&&i!=j){
                G.arcs[i][j]=MX;
                G.edge[i][j]=false;
            }
        }
    G.arcnum=7;
}
int main(){
    AMGragh G;
    memset(G.arcs,0,sizeof(G.arcs));
    CreateUDG(G);
    findArticul(G);
    //cout<<isArticul(G,0);
}
