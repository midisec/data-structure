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
	int e; //边数 
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
	ga->e = e;
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


int cmp(const void *a, const void *b)
{
	return (*(edge *)a).length - (*(edge *)b).length;
}

void kruskal(GraphMatrix *ga) {
	// 邻接矩阵到 edge[] 
	edge arr[MAXVEX];
	int i=0,j;
	
	int p=0;
	for(i;i<ga->e;i++) {
		for(j=0;j<i;j++) {
			if(ga->arcs[i][j] != 0 && ga->arcs[i][j] != 999) {
				arr[p].beg = j;
				arr[p].en = i;
				arr[p].length = ga->arcs[i][j];
				p++;
			}
		}
	}
	
	// arr[] 根据arr[].length 排序 从小到大！
	
	for(i=0;i<ga->e;i++) {
		printf("%c -> %c 值为 %d \n",ga->vexs[arr[i].beg],ga->vexs[arr[i].en],arr[i].length);
	}
	
	printf("根据length 排序后:\n");
	
	qsort(arr, ga->e, sizeof(edge), cmp);
	
	for(i=0;i<ga->e;i++) {
		printf("%c -> %c 值为 %d \n",ga->vexs[arr[i].beg],ga->vexs[arr[i].en],arr[i].length);
	}
	// 2. 筛选最小边 判断是否是回路。
	
	int e_flag = 0;
	// 如果边数为 (顶点数-1) 则不再寻找
	
	int end_index=0;
	int ends[ga->n];
	ends[end_index] = arr[0].en;
	printf("%c到%c\n",ga->vexs[arr[0].beg],ga->vexs[arr[0].en]);
	e_flag++;

	for(i=1;i<ga->e;i++) {
		
		int flag;
		for(j=0;j<=end_index;j++) {
			flag=0;
			// 如果之前走过这个点 （形成回路 则跳过这条边） 
			if (arr[i].en == ends[j]) {
				flag =1;
				break;
			}	
		}
		if(flag==0) {
			ends[++end_index] = arr[i].en;
			e_flag++;
			printf("%c到%c\n",ga->vexs[arr[i].beg],ga->vexs[arr[i].en]);
		}
		// 边数为 (顶点数-1) 则不再寻找
		if(e_flag == ga->n-1) {
			break;
		}
	} 
	
}





int main() {
	
	
	
	GraphMatrix *graph;
	graph = CreateGraph();
	PrintGraph(graph);

	
	kruskal(graph);
	return 0;
}
