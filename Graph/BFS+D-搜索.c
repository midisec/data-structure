#include<stdio.h>
#include<stdlib.h>


#define M 100
#define true 1
#define false 0

// bfs + D 搜索 
// -------------------------------------------
// BFS中用到的队列 
typedef int Elemtype;
typedef struct QNode{
    Elemtype data;
    struct QNode *next;
}QNode, *QueuePrt;

typedef struct {
    QueuePrt front, rear;
}LinkQueue;
//初始化
void initQueue(LinkQueue *q){
    q->front = q->rear = (QueuePrt)malloc(sizeof(QNode));
    if(!q->front)
        exit(0);
    q->front->next = NULL;
}
//插入一个节点
void InsertQueue(LinkQueue *q, Elemtype e){
    QueuePrt p;
    p = (QueuePrt)malloc(sizeof(QNode));
    if(p == NULL)
        exit(0);
    p->data = e;
    p->next = NULL;
    
    //插进去
    q->rear->next = p;
    q->rear = p;
}
//出队列
void DeleteQueue(LinkQueue *q, Elemtype *e){
    QueuePrt p;
    if( q->front == q->rear ){
        return;
    }
    
    p = q->front->next;
    *e = p->data;
    
    q->front->next = p->next;
    if(q->rear == p)
        q->rear = q->front;
    free(p);
}
//销毁一个队列
void DestroyQueue(LinkQueue *q){
    while (q->front) {
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
}
//队列是否为空
int isEmpty(LinkQueue* a)
{
    if(a->front == a->rear)
        return 1;
    return 0;
}

// ------------------------------------------- 


typedef char Element;
typedef int BOOL;
//邻接表的节点
typedef struct Node{
    int adj_vex_index;  //弧头的下标，也就是被指向的下标
    Element data;       //权重值
    struct Node * next; //边指针
}EdgeNode;

//顶点节点表
typedef struct vNode{
    Element date;          //顶点的权值
    EdgeNode * firstedge;  //顶点下一个是谁？
}VertexNode, Adjlist[M];

//总图的一些信息
typedef struct Graph{
    Adjlist adjlist;       //顶点表
    int arc_num;           //边的个数
    int node_num;          //节点个数
    BOOL is_directed;      //是不是有向图
}Graph, *GraphLink;

void creatGraph(GraphLink *g){
    int i, j, k;
    EdgeNode *p;
    EdgeNode *tem;
    printf("输入顶点数目,边数和是否有向？：\n");
    scanf("%d %d %d", &(*g)->node_num, &(*g)->arc_num, &(*g)->is_directed);
    
    printf("输入顶点信息：\n");
    for (i = 0; i < (*g)->node_num; i++) {
        getchar();
        scanf("%c", &(*g)->adjlist[i].date);
        (*g)->adjlist[i].firstedge = NULL;
    }
    printf("输入边信息：\n");

    for (k = 0; k < (*g)->arc_num; k++){

        getchar();
        scanf("%d %d", &i, &j);
        
        //新建一个节点是必须的
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        //弧头的下标
        p->adj_vex_index = j;
        
        p->next = NULL;
        
        // 尾插法 先找到最后一个结点
        tem = (*g)->adjlist[i].firstedge;
        if((*g)->adjlist[i].firstedge == NULL) {
        	(*g)->adjlist[i].firstedge = p;
		} else {
			
			while(tem->next!=NULL) {
				tem = tem->next;
			}
			tem->next = p;
		}
		

        //无向图 
        if(!(*g)->is_directed)
        {
            // j -----> i
            p = (EdgeNode *)malloc(sizeof(EdgeNode));
            p->adj_vex_index = i;
            p->next = (*g)->adjlist[j].firstedge;
            (*g)->adjlist[j].firstedge = p;
        }
    }
}


//输出邻接表 
void putGragh(GraphLink g){
    int i;
    printf("------------邻接表----------------\n"); 
    for (i = 0; i < g->node_num; i++) {
        EdgeNode * p = g->adjlist[i].firstedge;
        while (p) {
            printf("%c->%c ", g->adjlist[i].date, g->adjlist[p->adj_vex_index].date);
            p = p->next;
        }
        printf("\n");
    }
	printf("---------------------------------\n"); 
}


// BFS广度优先搜索 
int visited[M];
void BFSTraverse(Graph *g)
{
    int i;
    int tmp;
    EdgeNode *p;
    //初始化队列
    LinkQueue q;
    initQueue(&q);
    
    for (i = 0; i < g->node_num; i++) {
        if(!visited[i]){
            visited[i] = true;
            printf("%c ",g->adjlist[i].date);
            
            //队列插进来一个节点
            InsertQueue(&q, i);
            //队列不是空的时候就从队列里面操作
            while (!isEmpty(&q)) {
                //从队列取一个就得把和他连着的点都填进去
                DeleteQueue(&q, &tmp);
                //添加和他连着的所有未点亮的点
                p = g->adjlist[tmp].firstedge;
                while (p) {
                    if (!visited[p->adj_vex_index]) {
                        visited[p->adj_vex_index] = true;
                        printf("%c ",g->adjlist[p->adj_vex_index].date);
                        InsertQueue(&q, p->adj_vex_index);
                    }
                    p = p->next;
                }
            }
        }
    }

}


void D_Traverse(Graph *g) {
	int i;
    int tmp;
    EdgeNode *p;
    //初始化stack
	int stack[M];
	int stackPoint = -1;
    
    
    for (i = 0; i < g->node_num; i++) {
        if(!visited[i]){
            visited[i] = true;
            printf("%c ",g->adjlist[i].date);
            
            //栈中插进来一个节点
            stack[++stackPoint] = i;
            //栈中不是空的时候就从stack里面操作
            while (stackPoint != -1) {
                //从栈中取一个，把他孩子结点依次加到栈中(没访问过的) 
  
                tmp = stack[stackPoint--];
//                printf("\n:当前出栈的是:%d\n",tmp);

                p = g->adjlist[tmp].firstedge;
                while (p) {
                    if (!visited[p->adj_vex_index]) {
                        visited[p->adj_vex_index] = true;
                        printf("%c ",g->adjlist[p->adj_vex_index].date);
                        stack[++stackPoint] = p->adj_vex_index;
//                        printf("\n当前入栈的是:%d\n",p->adj_vex_index);
                    }
                    p = p->next;
                }
            }
        }
    }
}

int main() {
	
	int id;
	
	GraphLink g = (Graph *)malloc(sizeof(Graph));
	creatGraph(&g);
	putGragh(g);

	while(1) {
		

		printf("---------------------------------\n");
		printf("---------------------------------\n");
		printf("1.BFS\n");
		printf("2.D-搜索\n");
		printf("3.退出\n"); 
		printf("---------------------------------\n");
		printf("---------------------------------\n");
		printf("请输入搜索方式:\n");
		scanf("%d",&id);
		int i;
		for(i=0;i<M;i++) {
			visited[i]=false;
		} 
		switch(id) {
			case 1:printf("BFS搜索结果为:\n");BFSTraverse(g);printf("\n");break;
			case 2:printf("D-搜索结果为:\n");D_Traverse(g);printf("\n");break;
			case 3:printf("\n886\n");exit(0);
			default:printf("您的输入有误！\n");
		}	
	}
	return 0;
} 

/*
实验例题输入示例:
 输入顶点数目,边数和是否有向？：
7 11 0
输入顶点信息：
1 2 3 4 5 6 7
输入边信息：
0 1
0 2
0 3
1 4
2 4
2 5
3 5
3 6
4 5
4 6
5 6

 输入顶点数目,边数和是否有向？：
8 7 0
输入顶点信息：
1 2 3 4 5 6 7 8 
输入边信息：
0 1
0 2
1 3
1 4
2 5
2 6
4 7


*/ 
