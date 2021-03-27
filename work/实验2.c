//实验2.c 
//by midi

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//带头结点的

typedef struct pNode{
	int coef; //系数
	int exp;//指数
	struct pNode* link;
}pNode;


typedef struct{
	int n;
	struct pNode *head;
} poly;


void Create(poly *p) {//生成表头结点
	pNode *pn,*pre,*q;
	p->head=(pNode*)malloc(sizeof(pNode));
	p->head->exp=-1;
	p->head->link=NULL;
	
	
	p->n=0;
	while(1) {
		pn=(pNode*)malloc(sizeof(pNode));
		
		printf("coef:\n");
		scanf("%d",&pn->coef); //输入项的系数
		
		printf("exp:\n");
		scanf("%d",&pn->exp); //输入项的指数
		
		if (pn->exp<0) break; //若输入项指数负数，结果输入
		
		pre=p->head;
		q=p->head->link;
		
		while(q&&q->exp < pn->exp) {   //增序排列
			pre=q;
			q=q->link;
		}
		pn->link=q;
		pre->link=pn;
		p->n++;
	}
}


//老师提供的代码无头节点 参考后修改了部分 
void Add(poly *px,poly *qx)  {
	pNode *q,*q1=qx->head,*p,*temp;  //q1指向表头结点
	pNode *u,*pre;
	p=px->head->link;  //p指向多项式px的第一个结点
	q=q1->link;  //q1是q的前驱
	
	pre = p;
	int x;

	while(( p != NULL ) && ( q != NULL )) {
		if(p->exp < q->exp) {
			pre = p;  p = p->link;
		}else if(p->exp == q->exp) {
			x = p->coef + q->coef;
			if(x!=0) {
				
				p->coef = x;
				pre = p;
			}else {
				pre->link = p->link;
                free(p);
			}
			p = pre->link;
            u=q;
            q=q->link;
            free(u);

		}else {
			u=q->link;
            q->link=p;
            pre->link=q;
            pre=q;
			q=u;
		}
	}
	if ( q!= NULL){
		pre->link=q;
	}

	
}
	
 
// 一元多项式格式输出 
int print_poly(poly list1){
	int i=0;
	pNode *pn;
	if(!list1.head)
		return 0;
	pn=list1.head;
	for(i=0; i<list1.n; i++){
		pn=pn->link;
		if(i != list1.n-1) {
			printf("%d*x^%d+",pn->coef,pn->exp);
		}else {
			printf("%d*x^%d",pn->coef,pn->exp);
		}

	}
	return 1;
}


//多项式相加后输出函数    （相加的结果覆盖在 px上） 
void output(poly *p) {
	pNode *q;
	if(!p->head->link) //判断多项式是否为空 健壮性  头节点好处 
		return ;
	q=p->head->link; //单独输出第一项
	printf("%d*x^%d",q->coef,q->exp);
	q=q->link;
	while(q){
		if(q->exp==0) //对常数项的输出 
			if(q->coef>0) //常数系数>0的情况
				printf("+%d",q->coef);
			else printf("%d",q->coef); //常数系数<0的情况
		else if(q->coef>0) //非常数项项系数>0情况
			printf("+%d*x^%d",q->coef,q->exp);
		else //非常数项系数<0的情况
			printf("%d*x^%d",q->coef,q->exp);
		q=q->link;
	}
}


int main(){
	poly list1;
	poly list2;
	
	
	printf("\n第一个一元多项式为:(指数为负数时 停止输入):\n");	
	Create (&list1);	
	

	print_poly(list1);
	printf("\n");
	
	printf("\n第二个一元多项式为:(指数为负数时 停止输入):\n");
	Create (&list2);
	
	print_poly(list2);
	printf("\n");
	
	Add(&list1,&list2);	
	printf("\n一元多项式相加的结果为:\n");
	output(&list1);
//	
}
