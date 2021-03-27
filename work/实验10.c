//实验10.c 
//by midi

#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 16   



typedef char VexType;                     /*顶点的数据类型*/
typedef int AdjType;            /*邻接矩阵的数据元素的类型*/
typedef struct
{
	VexType vexs[MAXVEX];				//顶点
	AdjType arcs[MAXVEX][MAXVEX];		//邻接矩阵
	int n;								//记录当前图的顶点数
}GraphMatrix;



typedef struct treedata {
      char beg,en;   	/* beg,en是结点序号 */
      int length;     	/* 边长 */
}edge;


GraphMatrix* CreateGraph(void)			//创建无向带权图
{
	int i,j,k,e,m;
	GraphMatrix *ga;
	ga=(GraphMatrix *)malloc(sizeof(GraphMatrix));
	printf("请输入顶点的个数(不超过%d):",MAXVEX);
	scanf("%d",&(ga->n));
	getchar();

	printf("请顺序地输入各顶点的信息(序号即可,用一个字符表示):\n");
	for(i=0; i<ga->n; i++)
		ga->vexs[i]=getchar();     /*读入顶点信息，建立顶点表*/
	getchar();
	for(i=0; i<ga->n; i++)
		for(j=0; j<ga->n; j++){
			if(i==j) {
				ga->arcs[i][j]=0;
			} else {
				ga->arcs[i][j]=999;
			}
		}
			                /*邻接矩阵初始化*/
	printf("请输入边的个数:");
	scanf("%d",&e);

	printf("请输入与边相关联的两个顶点的序号:\n");
	for(k=0;k<e;k++)
	{
		scanf("%d%d%d",&i,&j,&m);                         /*读入边以及权值*/
		ga->arcs[i][j]=m;
		ga->arcs[j][i]=m;
	}
	getchar();
	return ga;
}


void PrintGraph(GraphMatrix *ga)
{
	int i,j;
	printf("\n顶点表为:\n");
	for(i=0; i<ga->n; i++)
		printf("%4c",ga->vexs[i]);
	printf("\n邻接矩阵为:\n");
	for(i=0; i<ga->n; i++)
	{
		for(j=0; j<ga->n; j++)
			printf("%4d",ga->arcs[i][j]);
		printf("\n");
	}
}

//是否所有点都已选中 所有都被选中 返回 0 
int isall(int flag[],int n) {
	int i;
	for(i=0;i<n;i++) {
		if(flag[i]==0) {
			break;
		}
	}
	if(i>=n) {
		return 0;
	} else {
		return 1;
	}
}
 


void avoid_cycle(GraphMatrix *ga,VexType ch) {
	
	printf("开始的点为:%c\n",ch);
	int i,start_index;
	int flag[MAXVEX];
	for(i=0;i<ga->n;i++) {
		flag[i]=0;
		if(ga->vexs[i] ==ch) {
			start_index = i;
		}
	}
	flag[start_index] = 1;
	//第一个开始的点
	int j;
	
	int temp_x,temp_y;
	while(isall(flag,ga->n)) {
		int min_temp=100000;
		for(i=0;i<ga->n;i++) {
			if(flag[i]==1) {
				for(j=0;j<ga->n;j++) {
					if((ga->arcs[i][j] != 0) &&(ga->arcs[i][j]< min_temp) &&(flag[j]==0)) {
						min_temp = ga->arcs[i][j];
						temp_x = i;
						temp_y = j;
					}
				}
			}
		}
		printf("%c到%c\n",ga->vexs[temp_x],ga->vexs[temp_y]);
		
		flag[temp_y] = 1;
//		break;
		//该点被选过 
		
	} 
} 



void prim(GraphMatrix *ga) {
	edge tree[MAXVEX];
	int v;
	int k,min,s,j,d;
	edge x;
	
	for (v=1;v<=ga->n-1;v++){
		
	    tree[v-1].beg = 0;
		tree[v-1].en = v;
	    tree[v-1].length = ga->arcs[0][v];
	}
	

	for (k=0; k< ga->n-2; k++) {
		
    	min = tree[k].length;
    	s = k;
    	for (j=k+1;j<=ga->n-2;j++) {    /* 求最小两栖边所在位置 */
      		if(tree[j].length<min) {
      			min = tree[j].length;
      			s = j;
			}
		}
		v = tree[s].en;
		
		x = tree[s];
		tree[s] = tree[k];
		tree[k] = x;
		
		
		for (j=k+1;j<=ga->n-2;j++) { 
		     d = ga->arcs[v][tree[j].en];
		     if (d<tree[j].length) { 
		        tree[j].length = d;
		        tree[j].beg = v;
		     }
		}
	}
	
	int i;
	for(i=0;i<ga->n-1;i++) {
//		printf("%c",ga->vexs[i]);
//		printf("%d, %d, %d\n",tree[i].beg,tree[i].en,tree[i].length);
		printf("%c到%c\n",ga->vexs[tree[i].beg],ga->vexs[tree[i].en]);
	}
	


}


int main() {
	
	
	GraphMatrix *graph;
	graph = CreateGraph();
	PrintGraph(graph);
	while(1) {

	
	
	printf("---------------------\n");
	printf("---------------------\n");
	printf("1.prim\n");
	printf("2.贪心方法\n");
	printf("3.退出\n"); 
	printf("---------------------\n");
	printf("---------------------\n");
	printf("请输入要使用的方法:\n");
	int nums;
	scanf("%d",&nums);
	switch(nums) {
		case 1:
			prim(graph);break;

		case 2:
			getchar();
			printf("请输入要开始的点:\n");
			char start;
			scanf("%c",&start);	
			avoid_cycle(graph,start);
			break;
		case 3:
			printf("\n886\n");exit(0); 
			
		default:printf("您的输入有误！\n");
	}


	
	}
	
	
	/**
测试用例：
 
请输入顶点的个数(不超过16):6
请顺序地输入各顶点的信息(序号即可,用一个字符表示):
012345
请输入边的个数:8
请输入与边相关联的两个顶点的序号:
0 1 1
0 2 5
0 3 2
1 4 7
1 2 3
2 5 6
3 5 8
4 5 4
	
	**/
	
	return 0;
}
