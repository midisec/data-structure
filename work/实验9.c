//实验9.c 
//by midi

#include<stdio.h>
#include<stdlib.h>
#define Maxsize 10
typedef struct{     	//定义三元组表
	int i,j;
	int v;
}TriTupleNode;
typedef struct{  		//定义三元组表
	TriTupleNode data[Maxsize];
	int m;
	int n;
	int t;	 			//矩阵行，列及三元组表长度
}TriTupleTable;

// 三元组的结构与实验7基本一致  这次三原组从1开始记录数据  0被用来记录 总行 总列 总有效个数 
int flag;


void easy_way() {
	
	int m,n;
	printf("请输入行列 例如:3 3\n");
	scanf("%d %d",&m,&n);
	int arr[m][n];
	int b[n];
	int i,j,k;
	//输入 
	printf("请输入%d个数:\n",m*n);
	for(i=0;i<m;i++) {
		
		for(j=0;j<n;j++) {
			scanf("%d",&arr[i][j]);
		}
	}
	
	
		//输出 
	printf("\n-----------------------\n");
	printf("\n输入的二维矩阵为:\n");
	for(i=0;i<m;i++) {
		
		for(j=0;j<n;j++) {
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n-----------------------\n");
	int s,count=0;
	// 
	int min,max;
	for(j=0;j<m;j++) {
		
		min = arr[j][0];
		for(i=0;i<n;i++) {
			if(arr[j][i] < min) {
				min = arr[j][i];
			}
		}
		//找出这行最小值 
		
		s=0;
		for(i=0;i<n;i++) {
			if(arr[j][i] == min) {
				b[s] =i;
				s++;
			}
		}
		//找出这行有几个最小值
//		printf("min：%d\n",min);
		
		max = min;
		for(i=0;i<s;i++) {
			for(k=0;k<m;k++) {
				if(max < arr[k][b[i]]) {
					break;
				}
				if(k==m-1) { 
					printf("\n数组[%d][%d]为鞍点值为: %d\n",j,b[i],arr[j][b[i]]);
					count++;
				}
			}
		}

	}
	
	if(count == 0) {
		printf("无\n");
	}
	
}



// sort 
//防止用户乱序输入
void Tuplesort(TriTupleTable *a){
	int z,x,temp1,temp2,temp3;
	for(z=0;z<a->t;z++)
		for(x=1;x<a->t-z;x++)
		{	if(a->data[x].i==a->data[x+1].i){
				if(a->data[x].j>a->data[x+1].j){
				temp1=a->data[x].i;
				temp2=a->data[x].j;
				temp3=a->data[x].v;
				a->data[x].i=a->data[x+1].i;
				a->data[x].j=a->data[x+1].j;
				a->data[x].v=a->data[x+1].v;
				a->data[x+1].i=temp1;
				a->data[x+1].j=temp2;
				a->data[x+1].v=temp3;
				}
			}
			if(a->data[x].i>a->data[x+1].i){
				temp1=a->data[x].i;
				temp2=a->data[x].j;
				temp3=a->data[x].v;
				a->data[x].i=a->data[x+1].i;
				a->data[x].j=a->data[x+1].j;
				a->data[x].v=a->data[x+1].v;
				a->data[x+1].i=temp1;
				a->data[x+1].j=temp2;
				a->data[x+1].v=temp3;
				}
		}			
}



// 初始化 百度的输入方式（健壮性较好） 
void InitTriTupleNode (TriTupleTable *a){
	int i,j,k,val;
	i=j=0;
	k=1;
	printf("请输入矩阵最大行数: ");
		scanf("%d",&a->data[0].i);
		printf("请输入矩阵最大列数: ");
		scanf("%d",&a->data[0].j);		
		printf("请输入矩阵有效数字的个数: ");
		scanf("%d",&a->data[0].v);
		a->m =a->data[0].i;
		a->n =a->data[0].j;
		a->t =a->data[0].v;
	while(k<=a->t&&i!=-1&&j!=-1){   		//rol=-1||col=-1结束输入
Q:		printf("输入矩阵元素的行: ");
		scanf("%d",&i);
		if(i>a->m){
			printf("输入错误，请重新输入!\n");
			goto Q; //健壮性 
		} 
		else if(i==-1) 
			break;
W:		printf("输入矩阵元素的列: ");
		scanf("%d",&j);		
		if(j>a->n){
			printf("输入错误，请重新输入!\n");
			goto W; //健壮性 
		} 
		else if(i==-1) 
			break;
		printf("输入矩阵元素的值: ");
		scanf("%d",&val);
		a->data[k].i=i;
		a->data[k].j=j;
		a->data[k].v=val;
		k++;
	}
	Tuplesort(a);  //防止用户乱序输入
} 


void showMatrix(TriTupleTable *a){   	//输出稀疏矩阵
	int p,q;
	int t=1;
	for(p=1;p<=a->m;p++){
		for(q=1;q<=a->n;q++){ 
			if(a->data[t].i==p&&a->data[t].j==q){
				printf("%d\t",a->data[t].v);
				t++;
			}
			else 
				printf("0\t");
		}
		printf("\n");
	}
}


//普通转置 实验 7 一模一样的代码 
void TransposeSMatrix(TriTupleTable *a,TriTupleTable *b){
	int q,col,p;
	b->m=a->n;
	b->n=a->m;
	b->t=a->t;
	b->data[0].i = a->n;
	b->data[0].j = a->m;
	b->data[0].v = a->t;
	if(b->t){
		q=1;
		for(col=1;col<=a->n;++col)
			for(p=1;p<=a->t;++p)
				if(a->data[p].j==col){
					b->data[q].i=a->data[p].j;
					b->data[q].j=a->data[p].i;
					b->data[q].v=a->data[p].v;
					++q;
				}
	}
	
	
	
}


void isAD(TriTupleTable *a,int x,int min) {
	
	TriTupleTable *b;
	b=(TriTupleTable*)malloc(sizeof(TriTupleTable));
	TransposeSMatrix(a,b);
	//此时的b已经转置好了
//	printf("b:\n");
//	showMatrix(b); 

	int t=1;
	

	
	int index_x=0,index_y=0;
	int tem=0;
	// 同理先找到第一个值 
	for(t = 1; t<=a->t; t++) {
		if (b->data[t].i == x) {
			index_x = b->data[t].i;
			index_y = b->data[t].j;
			tem = b->data[t].v;
			break;
		} else {
			index_x = 0;
			index_y = 0;
			tem = 0;
		}
	}
	
	
	for(t = 1; t<=a->t; t++) {
		if (b->data[t].i == x) {
			if(tem < b->data[t].v) {
				index_x = b->data[t].i;
				index_y = b->data[t].j;
				tem = b->data[t].v;
			}
		}
	}
	
//	printf("\n(%d,%d)值为:%d\n",index_x,index_y,tem);

	if((index_x == x)&&(min == tem)&&(x!=0)) {
		printf("\n第(%d,%d)为鞍点值为:%d\n",index_y,index_x,tem);
		flag = 1;
	}


	
} 
 
void find(TriTupleTable *a) {
	int p,q;
	int t=1;

	
	int index=1;
	int minlist[a->m];
	
	int index_x=0,index_y=0;
	int tem=0;
	
	p=1;
	for (p=1;p<=a->data[0].j;p++) {

	//先找到  第一行第一个值	
	for(t = 1; t<=a->t; t++) {
		if (a->data[t].i == p) {
			index_x = a->data[t].i;
			index_y = a->data[t].j;
			tem = a->data[t].v;
			break;
		} else {
			index_x = 0;
			index_y = 0;
			tem = 0;
		}
	}
	
//	printf("\n第一个数:%d,%d,%d\n",index_x,index_y,tem);
	
	for(t = 1; t<=a->t; t++) {
		if (a->data[t].i == p) {
			if(tem > a->data[t].v) {
				index_x = a->data[t].i;
				index_y = a->data[t].j;
				tem = a->data[t].v;
			}
		}
	}
//	printf("\n第%d行最小的数:（%d,%d)值为:%d\n",p,index_x,index_y,tem);
	// 将最小的这个数的 纵坐标 index_y 传给 转置矩阵 当作横坐标去找该行最大值 若找到了 这个 index_k  
	// 并且等于 index_x 则返回说这个是鞍点 

	isAD(a,index_y,tem);

	
	}
	
	if(flag != 1) {
		printf("没有鞍点!!\n");
	}
}






int main() {
	
//  二维数组直接操作 
//	easy_way();
	
	TriTupleTable *a;
	a=(TriTupleTable*)malloc(sizeof(TriTupleTable));


	InitTriTupleNode(a);
	showMatrix(a);
	printf("\n");
	find(a);
	
	return 0;
}
