#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define Max 10
#define MX 99999

typedef struct Ver {
    char num[5];
} Ver;

typedef struct {
    Ver vex[Max];
    int arcs[Max][Max];
    int vnum, arcnum;
    bool visited[Max]; // 将visited数组提到结构体中
} AMGragh;

void DFS(AMGragh *G, int v) {
    G->visited[v] = true; // 使用结构体中的visited数组
    for (int w = 0; w < G->vnum; w++) {
        if (G->arcs[v][w] != MX && !G->visited[w]) { // 修改判断条件
            DFS(G, w);
        }
    }
}

bool isArticul(AMGragh *G, int v) {
    int count = 0;
    memset(G->visited, false, sizeof(G->visited)); // 初始化visited数组
    G->visited[v] = true; // 标记当前节点已访问
    for (int i = 0; i < G->vnum; i++) {
        if (!G->visited[i]) {
            count++;
            DFS(G, i);
        }
    }
    // 割点满足整个图连通的条件是连通分量个数大于1
    return count > 1;
}

void findArticul(AMGragh *G) {
    printf("The articulation points of AMGragh are:\n");
    for (int v = 0; v < G->vnum; v++) {
        if (isArticul(G, v)) {
            printf("%s ", G->vex[v].num);
        }
    }
    printf("\n");
}

void CreateUDG(AMGragh *G) {
    G->vnum = 7;
    strcpy(G->vex[0].num, "01");
    strcpy(G->vex[1].num, "02");
    strcpy(G->vex[2].num, "03");
    strcpy(G->vex[3].num, "04");
    strcpy(G->vex[4].num, "05");
    strcpy(G->vex[5].num, "06");
    strcpy(G->vex[6].num, "07");
    memset(G->arcs, MX, sizeof(G->arcs)); // 初始化arcs数组
    G->arcs[0][1] = G->arcs[1][0] = 1;
    G->arcs[0][2] = G->arcs[2][0] = 1;
    G->arcs[1][3] = G->arcs[3][1] = 1;
    G->arcs[2][3] = G->arcs[3][2] = 1;
    G->arcs[3][4] = G->arcs[4][3] = 1;
    G->arcs[3][5] = G->arcs[5][3] = 1;
    G->arcs[5][6] = G->arcs[6][5] = 1;
    
    for (int i = 0; i < G->vnum; i++) {
        G->arcs[i][i] = 0; // 修改对角线元素为0
    }
    
    G->arcnum = 7;
}

int main() {
    AMGragh G;
    CreateUDG(&G);
    findArticul(&G);
    return 0;
}