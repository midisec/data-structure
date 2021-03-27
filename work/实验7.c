//实验7.c 
//by midi

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define Ok 1
#define Maxsize 10 	//用户自定义三元组最大长度
typedef struct{     	//定义三元组表
	int i,j;
	int v;
}TriTupleNode;

typedef struct{  		//定义三元组表
	TriTupleNode data[Maxsize];
	int m;
	int n;
	int t;	 			//矩阵行，列及三元组表长度
	
	int rpos[Maxsize];
}TriTupleTable;


void InitTriTupleNode (TriTupleTable *a){  //输入三元组表
		printf("\n矩阵行或列输入值为-1，则输入结束!:\n");
	int i,j,k,val,maxrow,maxcol;
	maxrow=0;
	maxcol=0;
	i=j=0;
	k=0;
	while(i!=-1&&j!=-1){   		//rol=-1||col=-1结束输入
		printf("input row: ");
		scanf("%d",&i);
		if(i==-1) 
			break;
		printf("input col: ");
		scanf("%d",&j);		
		if(j==-1) 
			break;
		printf("input value: ");
		scanf("%d",&val);
		a->data[k].i=i;
		a->data[k].j=j;
		a->data[k].v=val;
		if (maxrow<i)
			maxrow=i;
		if (maxcol<j) 
			maxcol=j;
		k++;
	}
	a->m=maxrow;
	a->n=maxcol;
	a->t=k;
	
}
void TransposeSMatrix(TriTupleTable *a,TriTupleTable *b){
	int q,col,p;
	b->m=a->n;
	b->n=a->m;
	b->t=a->t;
	if(b->t){
		q=0;
		for(col=1;col<=a->n;++col)
			for(p=0;p<=a->t;++p)
				if(a->data[p].j==col){
					b->data[q].i=a->data[p].j;
					b->data[q].j=a->data[p].i;
					b->data[q].v=a->data[p].v;
					++q;
				}
	}
}





void FastTransposeSMatrix(TriTupleTable *a,TriTupleTable *b) {
	b->m = a->n;
	b->n = a->m;
	b->t = a->t;
    if (b->t) {
        int array[Maxsize];
        int col,t,p;
        for (col=1; col<=a->n; col++) {
            array[col]=0;
        }
        for (t=0; t<a->t; t++) {
            int j=a->data[t].j;
            array[j]++;
        }
        int cpot[(b->m)+1];
        cpot[1]=1;
        for (col=2; col<=a->n; col++) {
            cpot[col]=cpot[col-1]+array[col-1];
        }
        for (p=0; p<a->t; p++) {
            int col=a->data[p].j;
            int q=cpot[col];
            b->data[q-1].i=a->data[p].j;
            b->data[q-1].j=a->data[p].i;
            b->data[q-1].v=a->data[p].v;
            cpot[col]++;
        }
    }
}


void showMatrix(TriTupleTable *a){   	//输出稀疏矩阵
	int p,q;
	int t=0;
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

void main(){
	TriTupleTable *a,*b;
	a=(TriTupleTable*)malloc(sizeof(TriTupleTable));
	b=(TriTupleTable*)malloc(sizeof(TriTupleTable));
	InitTriTupleNode(a);
	printf("\n转置前矩阵:\n");
	showMatrix(a);  

//	普通转置	
//	TransposeSMatrix(a,b);
	
//	原来的输入输出方法
//	快速转置 
	FastTransposeSMatrix(a,b);

	
	printf("\n转置后矩阵:\n");
	showMatrix(b);  
}
