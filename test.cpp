#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<string.h>
#include<algorithm>
using namespace std;
#define Max 50
#define MX 999999
//bool visited[Max];
int D[Max][Max];
int path[Max][Max];
typedef struct Ver{//顶点信息
    char num[5];
    char name[51];
    char instruct[101];
}Ver;
typedef struct{//邻接矩阵
    Ver vex[Max];//顶点表
    int arcs[Max][Max];
    int vnum,arcnum;
    bool edge[Max][Max];
}AMGragh;

void menu(){
    cout<<"************欢迎来到商专************"<<endl;
    cout<<"        1、查看所有景点           "<<endl;
    cout<<"        2、景点查询               "<<endl;
    cout<<"        3、问路                   "<<endl;
    cout<<"        4、修改景点基本信息       "<<endl;
    cout<<"        5、展示简易地图             "<<endl;
    cout<<"        6、修改景点间路径                   "<<endl;
    cout<<"        7、查询关节点                   "<<endl;
    cout<<"        8、退出                   "<<endl;
    cout<<"**********************************"<<endl;
    cout<<"请选择..."<<endl;
}

void Allprint(AMGragh G){//输出所有景点信息
    cout<<"---------------校园景点总览---------------"<<endl;
    cout<<"景点名称   "<<"  "<<"代号"<<"     "<<"    简介"<<endl;
    for(int i=0;i<G.vnum;i++){//总是输出不整齐
        cout<<std::left<<setw(15)<<G.vex[i].name<<" "<<std::left<<setw(5)<<G.vex[i].num<<" "<<std::left<<setw(50)<<G.vex[i].instruct<<endl;
        //printf("%-20s%-10s%-50s\n",G.vex[i].name,G.vex[i].num,G.vex[i].instruct);
    }
    cout<<endl;
}

void CreateUDG(AMGragh &G){//建图
    G.vnum=20;
    strcpy(G.vex[0].num,"01");
    strcpy(G.vex[1].num,"02");
    strcpy(G.vex[2].num,"03");
    strcpy(G.vex[3].num,"04");
    strcpy(G.vex[4].num,"05");
    strcpy(G.vex[5].num,"06");
    strcpy(G.vex[6].num,"07");
    strcpy(G.vex[7].num,"08");
    strcpy(G.vex[8].num,"09");
    strcpy(G.vex[9].num,"10");
    strcpy(G.vex[10].num,"11");
    strcpy(G.vex[11].num,"12");
    strcpy(G.vex[12].num,"13");
    strcpy(G.vex[13].num,"14");
    strcpy(G.vex[14].num,"15");
    strcpy(G.vex[15].num,"16");
    strcpy(G.vex[16].num,"17");
    strcpy(G.vex[17].num,"18");
    strcpy(G.vex[18].num,"19");
    strcpy(G.vex[19].num,"20");
    strcpy(G.vex[0].name,"萃雅1、2栋");
    strcpy(G.vex[1].name,"田径场");
    strcpy(G.vex[2].name,"体育馆");
    strcpy(G.vex[3].name,"萃雅食堂");
    strcpy(G.vex[4].name,"萃雅公寓（3~6）");
    strcpy(G.vex[5].name,"国际商学院");
    strcpy(G.vex[6].name,"科技楼");
    strcpy(G.vex[7].name,"日新楼");
    strcpy(G.vex[8].name,"图书馆");
    strcpy(G.vex[9].name,"至诚楼");
    strcpy(G.vex[10].name,"经管大楼");
    strcpy(G.vex[11].name,"贤德园区");
    strcpy(G.vex[12].name,"楚风轩");
    strcpy(G.vex[13].name,"第二办公楼");
    strcpy(G.vex[14].name,"北门");
    strcpy(G.vex[15].name,"医务室");
    strcpy(G.vex[16].name,"乐知楼");
    strcpy(G.vex[17].name,"咸嘉园区");
    strcpy(G.vex[18].name,"岭南校区");
    strcpy(G.vex[19].name,"西门");
    strcpy(G.vex[0].instruct,"萃雅1为女寝、2为男寝，均为六人寝");
    strcpy(G.vex[1].instruct,"足球场、400m环形跑道、风雨跑道、观众台");
    strcpy(G.vex[2].instruct,"室内篮球场、羽毛球场、观众席");
    strcpy(G.vex[3].instruct,"种类最为丰富的食堂");
    strcpy(G.vex[4].instruct,"均为女寝");
    strcpy(G.vex[5].instruct,"国商✌的地盘");
    strcpy(G.vex[6].instruct,"校外领导最爱来这，实验室什么的一般都在这");
    strcpy(G.vex[7].instruct,"二教");
    strcpy(G.vex[8].instruct,"进入图书馆、借书都需要刷学生卡");
    strcpy(G.vex[9].instruct,"一教");
    strcpy(G.vex[10].instruct,"商专最高楼，见到领导记得问好（不然有你好果汁吃😃");
    strcpy(G.vex[11].instruct,"好几栋宿舍楼，还有个食堂");
    strcpy(G.vex[12].instruct,"教师食堂，中午别去");
    strcpy(G.vex[13].instruct,"二办");
    strcpy(G.vex[14].instruct,"位于桐梓坡路，出去有公交站、地铁站");
    strcpy(G.vex[15].instruct,"医务室，可以报销医保");
    strcpy(G.vex[16].instruct,"三教");
    strcpy(G.vex[17].instruct,"商专为数不多的四人寝");
    strcpy(G.vex[18].instruct,"没怎么去过，细节不清楚");
    strcpy(G.vex[19].instruct,"出门就是西二环");
    G.arcs[1][0]=G.arcs[0][1]=200;
    G.arcs[0][2]=G.arcs[2][0]=150;
    G.arcs[0][3]=G.arcs[3][0]=300;
    G.arcs[1][2]=G.arcs[2][1]=20;
    G.arcs[2][4]=G.arcs[4][2]=100;
    G.arcs[2][7]=G.arcs[7][2]=200;
    G.arcs[3][4]=G.arcs[4][3]=20;
    G.arcs[3][5]=G.arcs[5][3]=30;
    G.arcs[4][7]=G.arcs[7][4]=30;
    G.arcs[5][6]=G.arcs[6][5]=20;
    G.arcs[6][7]=G.arcs[7][6]=120;
    G.arcs[6][19]=G.arcs[19][6]=20;
    G.arcs[7][8]=G.arcs[8][7]=20;
    G.arcs[7][11]=G.arcs[11][7]=200;
    G.arcs[8][9]=G.arcs[9][8]=20;
    G.arcs[8][19]=G.arcs[19][8]=139;
    G.arcs[9][11]=G.arcs[11][9]=250;
    G.arcs[9][10]=G.arcs[10][9]=100;
    G.arcs[9][12]=G.arcs[12][9]=30;
    G.arcs[9][13]=G.arcs[13][9]=40;
    G.arcs[12][13]=G.arcs[13][12]=30;
    G.arcs[12][15]=G.arcs[15][12]=30;
    G.arcs[12][18]=G.arcs[18][12]=250;
    G.arcs[13][14]=G.arcs[14][13]=30;
    G.arcs[14][16]=G.arcs[16][14]=20;
    G.arcs[16][17]=G.arcs[17][16]=30;
    G.arcs[17][18]=G.arcs[18][17]=150;
    for (int i = 0; i < G.vnum; i++){
        for (int j = 0; j < G.vnum; j++){
            G.edge[i][j] = true;
        }
    }
    for(int i=0;i<G.vnum;i++)//初始化路径长度
        for(int j=0;j<G.vnum;j++){
            if(G.arcs[i][j]==0&&i!=j){
                G.arcs[i][j]=MX;
                G.edge[i][j]=false;
            }
        }
    G.arcnum=27;
}

void changeVer(AMGragh &G){//修改信息
    Allprint(G);
    cout<<"请输入要修改信息的代号：";
    char c[5];
    cin>>c;
    for(int i=0;i<G.vnum;i++){
        if(strcmp(c,G.vex[i].num)==0){//字符串比较的方法进行查找
            memset(G.vex[i].name,0,sizeof(G.vex[i].name));
            memset(G.vex[i].num,0,sizeof(G.vex[i].num));
            memset(G.vex[i].instruct,0,sizeof(G.vex[i].instruct));
            char num1[5];
            char name1[51];
            char instruct1[101];
            cout<<"请输入修改后的景点信息："<<endl;
            cout<<"景点名称：";
            scanf("%s",name1);
            cout<<"代号：";
            scanf("%s",num1);
            cout<<"简介：";
            scanf("%s",instruct1);
            strcpy(G.vex[i].name,name1);
            strcpy(G.vex[i].num,num1);
            strcpy(G.vex[i].instruct,instruct1);
            cout<<"修改成功！"<<endl;
            break;
        }
    }
}

void Query(AMGragh G){//查询景点
    cout<<"请输入查询景点的代号：";
    char c[5];
    cin>>c;
    int i;
    for(i=0;i<G.vnum;i++){
        if(strcmp(c,G.vex[i].num)==0){
            cout<<"景点名称："<<G.vex[i].name<<"   ";
            cout<<"代号："<<G.vex[i].num<<"   ";
            cout<<"简介："<<G.vex[i].instruct<<endl;
            break;
        }
    }
    if(i==G.vnum){
        cout<<"该代号不存在!"<<endl;
    }
}

void Floyd(AMGragh G){//弗洛伊德算法，获得最短路径
    int i,j,k;
    for(i=0;i<G.vnum;i++){
        for(j=0;j<G.vnum;j++){
            D[i][j]=G.arcs[i][j];
            if(D[i][j]<MX&&i!=j){
                path[i][j]=i;
            }
            else{
                path[i][j]=-1;
            }
        }
    }
    for(k=0;k<G.vnum;k++){
        for(i=0;i<G.vnum;i++){
            for(j=0;j<G.vnum;j++){
                if(D[i][k]+D[k][j]<D[i][j]){
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=path[k][j];
                }
            }
        }
    }
}

void Path(AMGragh G,int a,int b){//获得具体路径
   int p[Max];
   p[0]=b;
   int i=1;
   while(a!=b){
    b=path[a][b];
    p[i]=b;
    ++i;
   }
   cout<<"路径:"<<G.vex[a].name;
   i=i-2;
   while(i>=0){
    cout<<"--->"<<G.vex[p[i]].name;
    --i;
   }
}

void askDirect(AMGragh G){//问路
    Allprint(G);
    cout<<"请输入起点和目的地(1~"<<G.vnum<<"，即第几个景点,中间用空格隔开):";
    int a,b;
    cin>>a>>b;
    Floyd(G);
    cout<<endl<<endl<<"从"<<G.vex[a-1].name<<"到"<<G.vex[b-1].name<<":"<<endl<<endl<<"最短路径长度："<<D[a-1][b-1]<<"米"<<endl;
    Path(G,a-1,b-1);
    cout<<endl;
}

void askTransit(AMGragh G){//简单粗暴地拆分问题，复用Floyd算法
    cout<<"请输入起点和目的地(1~"<<G.vnum<<"，即第几个景点,中间用空格隔开):";
    int a,b,c;
    cin>>a>>b;
    cout<<"请输入途径景点编号";
    cin>>c;
    Floyd(G);
    cout<<"从"<<G.vex[a-1].name<<"途径"<<G.vex[c-1].name<<"到"<<G.vex[b-1].name<<":"<<endl<<"最短路径长度："<<D[a-1][c-1]+D[c-1][b-1]<<"米"<<endl;
    Path(G,a-1,c-1);
    cout<<endl;
    Path(G,c-1,b-1);
    cout<<endl;
}

void ask(AMGragh G){
    cout<<"************问路************"<<endl;
    cout<<"        1、两景点间直达路线           "<<endl;
    cout<<"        2、两景点间经过指定景点               "<<endl;
    cout<<"**********************************"<<endl;
    cout<<"请选择..."<<endl;
    int choice;
    cin>>choice;
    switch (choice){
    case 1:
        askDirect(G);
        break;
    case 2:
        askTransit(G);
        break;    
    default:
        cout<<"输入错误！"<<endl;
        break;
    }
}

void printMap(){
    cout<<"             _______________萃雅1、2 ----------       \n";
    cout<<"             |                 \\         田\n";
    cout<<"             |                   \\       径\n";
    cout<<"             |                     \\     场\n";
    cout<<"    萃雅食堂----萃雅公寓(3~6)------体育馆--\n";
    cout<<"   国际商学院-|          |       /\n";
    cout<<"     科技楼---/\\------|-日新楼 ------     贤     \n";
    cout<<"西门------------------|-图书馆/           德      \n";
    cout<<"    经管大楼----------|-至诚楼----------- 园区\n";
    cout<<"                     |    | \n";
    cout<<"                  楚风轩---第二办公楼--北门\n";
    cout<<"                     |--医务室          | \n";
    cout<<"                     |               乐子楼\n";
    cout<<"                     |                      \\  \n";
    cout<<"                     |                      咸嘉园区\n";
    cout<<"                      岭                   /\n";
    cout<<"                                        南\n";
    cout<<"                            校                 区\n";
    cout<<endl;
}

bool isEdge(AMGragh G,int i,int j){
    if(G.arcs[i][j]==MX)
        return false;
    else
        return true;
}

void updateArcs(AMGragh &G){
    int i,j;
    cout<<"请输入要修改的两个景点的代号：";
    cin>>i>>j;
    if(isEdge(G,i-1,j-1)){
        int temp=G.arcs[i-1][j-1];
        int k;
        cout<<"此路径长度为"<<temp<<"米\n"<<endl;
        cout<<"请输入更改后的数值"<<endl;
        cin>>k;
        G.arcs[i-1][j-1]=G.arcs[j-1][i-1]=k;
        cout<<G.vex[i-1].name<<"到"<<G.vex[j-1].name<<"的路径长度已由"<<temp<<"更改为"<<G.arcs[i-1][j-1]<<"米"<<endl;
        return;
    }else{
        cout<<"此路径不存在！"<<endl;
        return;
    }
}

void createArcs(AMGragh &G){
    int i,j;
    cout<<"请输入要增加的两个景点的代号：";
    cin>>i>>j;
    if(isEdge(G,i-1,j-1)){
        cout<<"此路径已存在！"<<endl;
        return;
    }
    else{
        int k;
        cout<<"请输入路径长度：";
        cin>>k;
        G.arcs[i-1][j-1]=G.arcs[j-1][i-1]=k;
        cout<<G.vex[i-1].name<<"到"<<G.vex[j-1].name<<"的路径长度为"<<G.arcs[i-1][j-1]<<"米"<<endl;
        G.edge[i-1][j-1]=G.edge[j-1][i-1]=true;
        return;
    }
}

void deleteArcs(AMGragh &G){
    int i,j;
    cout<<"请输入要删除的两个景点的代号：";
    cin>>i>>j;
    if(isEdge(G,i-1,j-1)){
        int temp=G.arcs[i-1][j-1];
        G.arcs[i-1][j-1]=G.arcs[j-1][i-1]=MX;
        cout<<G.vex[i-1].name<<"到"<<G.vex[j-1].name<<"的路径长度为"<<temp<<"米"<<endl;
        return;
    }else{
        cout<<"此路径不存在！"<<endl;
        return;
    }
}

void curdArcs(AMGragh &G){//
    cout<<"************路径修改************"<<endl;
    cout<<"        1、更新景点间路径长度           "<<endl;
    cout<<"        2、两景点间增加路径               "<<endl;
    cout<<"        3、删除两节点间路径            "<<endl;
    cout<<"**********************************"<<endl;
    cout<<"请选择..."<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        case 1:updateArcs(G);break;
        case 2:createArcs(G);break;
        case 3://deleteArcs(G);break;
        default:cout<<"输入错误！"<<endl;
    }
}

void addVer(AMGragh &G){
    cout<<"请输入要增加的景点名称";
    cin>>G.vex[G.vnum].name;
    cout<<"请输入景点简介";
    cin>>G.vex[G.vnum].instruct;
    //G.vex[G.vnum].num=G.vnum+1;
    /* std::string str=std::to_string(G.vnum+1);
    G.vex[G.vnum].num=str.c_str(); */
    itoa(G.vnum+1,G.vex[G.vnum].num,10);
    cout<<G.vex[G.vnum].num<<"编号景点"<<G.vex[G.vnum].name<<endl;
    for(int i=0;i<G.vnum;i++){//初始化路径长度
        G.arcs[i][G.vnum]=MX;
        G.arcs[G.vnum][i]=MX;
        G.edge[i][G.vnum]=false;
        G.edge[G.vnum][i]=false;
    }
    G.vnum++;
    cout<<"增加成功！"<<endl;
}

void updateVer(AMGragh &G){
    cout<<"************景点增加************"<<endl;
    cout<<"        1、增加景点           "<<endl;
    cout<<"        2、修改景点信息               "<<endl;
    cout<<"**********************************"<<endl;
    cout<<"请选择..."<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        case 1:
            addVer(G);
            break;
        case 2:
            changeVer(G);
            break;    
        default:cout<<"输入错误！"<<endl;
    }
}

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

//求AMGragh的关节点，并打印出来
void findArticul(AMGragh G){
    cout<<"关节点有：\n";
    for(int v = 0; v < G.vnum; v++){ //遍历所有顶点，判断是否是关节点
    //cout<<isArticul(G, v)<<endl;
        if(isArticul(G, v)){ //如果是关节点，打印出来
            cout<<v<<" ";
        }
    }
   cout<<"\n";
}

int main(){
    AMGragh G;
    memset(G.arcs,0,sizeof(G.arcs));
    CreateUDG(G);
    //cout<<G.arcs[0][11]<<endl;
    /* Floyd(G);//测试使用 输出Floyd算法二维数组
    Path(G,3,10);
    cout<<path[3][10]<<endl;
    printf("   ");
    for (int i = 0; i < 20; i++){
        printf("%3d ", i);
    }
    printf("\n");
    for(int v = 0; v < G.vnum; v++){
        printf("%2d  ", v);
        for(int w= 0; w < G.vnum; w++){
            printf("%03d ", D[v][w]);
        }
        printf("\n");
    }
    printf("-------------------------------------------\n");
    printf("    ");
    for (int i = 0; i < 20; i++){
        printf("%2d ", i);
    }
    printf("\n");
    for(int v = 0; v < G.vnum; v++){
        printf("%2d  ", v);
        for(int w = 0; w < G.vnum; w++){
            printf("%02d ", path[v][w]);
        }
        printf("\n");
    } */
    int m;
    while(m!=8){
        menu();
        cin>>m;
        switch(m){
        case 1:
            Allprint(G);
            break;
        case 2:
            Query(G);
            break;
        case 3:
            ask(G);
            break;
        case 4:
            updateVer(G);
            break;
        case 5:
            printMap();
            break;
        case 6:
            curdArcs(G);
            break;
        case 7:
            findArticul(G);
            break;
        case 8:
            cout<<"感谢您的使用！"<<endl;
            return 0;
        default:
            cout<<"没有该选项！"<<endl;
        }
        system("pause");
        system("cls");
    }
    //findArticul(G);//测试求关节点
    return 0;
}