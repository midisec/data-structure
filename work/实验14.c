//实验14.c 
//by midi

#include "stdlib.h"
#include "stdio.h"
#define vertexnum 9   //定义顶点数
struct node{    //图顶点结构：用邻接表存储
	int vertex; //邻接顶点数据
	struct node *next; //下一个邻接顶点
};
typedef struct node *graph; //定义图结构
struct node head[vertexnum]; 
int visited[vertexnum]; //用于标记结点是否已访问

// ----队列结构 
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
// ----队列结构 ----end 

void bfs(int vertex) {
	graph pointer;
	
	int tem;
	visited[vertex]=1;
	printf(" [%d]==>",vertex);
    LinkQueue q;
    initQueue(&q);//初始化队列
    InsertQueue(&q,vertex);
    while(!isEmpty(&q)) {
    	DeleteQueue(&q,&tem);
    	pointer=head[tem].next;
    	while(pointer) {
    		if(!visited[pointer->vertex]) {
    			visited[pointer->vertex] = 1;
    			printf(" [%d]==>",pointer->vertex);
    			InsertQueue(&q,pointer->vertex);
			}
			pointer=pointer->next; //下一个邻接点
		}
	}
}

void dfs(int vertex){ //深度优先搜索法
	graph pointer;
	visited[vertex]=1; //标记此结点已访问
	printf(" [%d]==>",vertex);
	pointer=head[vertex].next;
	while(pointer!=NULL){
		if(visited[pointer->vertex]==0)
			dfs(pointer->vertex); //递归调用
		pointer=pointer->next; //下一个邻接点
	}
}
void create_graph(int vertex1,int vertex2){//建立邻接顶点到邻接表内
	graph pointer,new_p;
	new_p=(graph)malloc(sizeof(struct node));//配置内存
	if(new_p!=NULL){//成功
		new_p->vertex=vertex2; //邻近接点
		new_p->next=NULL;
		pointer=&(head[vertex1]); //设为顶点数组之首结点
		while(pointer->next!=NULL)
			pointer=pointer->next; //下一个结点
		pointer->next=new_p; //串在链尾
	}
}
void print_graph(struct node *head){ //输入出邻接表数据
	graph pointer;
	pointer=head->next; //指针指向首结点
	while(pointer!=NULL){
		printf("[%d]",pointer->vertex);
		pointer=pointer->next; //往下结点
	}
	printf("\n");
}
void main(){ //主程序
	int i;
	int vertex;	
	int node[20][2]={	{1,2},{2,1},{1,3},{3,1},
						{2,4},{4,2},{2,5},{5,2},
						{3,6},{6,3},{3,7},{7,3},
						{4,8},{8,4},{5,8},{8,5},
						{6,8},{8,6},{7,8},{8,7}		};
	//图G3的所有结点的邻接点的邻接表
	for (i=0;i<vertexnum;i++){ 
		head[i].vertex=i;
		head[i].next=NULL;
	} 
	for (i=0;i<vertexnum;i++)   //配置所有结点均未访问
		visited[i]=0;
	for (i=0;i<20;i++)
		create_graph(node[i][0],node[i][1]);//建立邻接表
	printf("graph\n");
	for (i=1;i<vertexnum;i++){
		printf("vertex[%d]: ",i);
		print_graph(&head[i]);
	}
	printf("\nPlease enter the start node:");
	scanf("%d",&vertex);
	printf("\nthe depth of the graph is (starting from node %d):\n",vertex);
	printf(" [开始]==>");
//	dfs(vertex);  //首先从结点1开始
	bfs(vertex);
	printf(" [结束] \n\n");
}
