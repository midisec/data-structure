//实验13.c 
//by midi

#include<stdio.h>
#include<stdlib.h>

typedef int Elemtype;

typedef struct LNode {
    Elemtype data;
    struct LNode *next;
}LNode,*LinkList;


void createlist(LinkList *head)
{
    int i;
    *head=(LinkList)malloc(sizeof(LNode));
    
    (*head)->data = 0;
    LinkList p,tem;
    tem = *head;
	int value,length;
	printf("请输入该链表的长度:\n");
	scanf("%d",&length);
	
//	头插法 循环单链表  
    for(i=0;i<length;i++)
    {
        p=(LinkList)malloc(sizeof(LNode));
        printf("请该链表输入第%d个值:",i+1);
        
        scanf("%d",&value);
        p->data = value;
        tem->next = p;
        tem = p;
        
//        (*head)->data++;   //计数用 
    }

//	tem->next = *head;
	tem->next = NULL;
	printf("该链表创建完成!\n");

}

void print(LinkList head)
{
    LinkList p;
    p=head->next;
    
    do {
		printf("%d ",p->data);
		p = p->next;
	}while(p!=NULL);

    
}



void AandBtoC(LinkList Ahead,LinkList Bhead,LinkList *Chead) {
	LinkList Ap,Bp;
	Ap=Ahead->next;
	Bp=Bhead->next;
	
	// C头结点  还是需要开空间的 
	*Chead=(LinkList)malloc(sizeof(LNode));
	(*Chead)->data = 0;
	
	LinkList tem;
	tem = *Chead;

	
	
	printf("\n");
	do {
		
		if(Ap->data < Bp->data) {
			
//			printf("%d ",Ap->data);
			tem->next = Ap;
			tem = Ap;
			Ap = Ap->next;
		} else if(Ap->data > Bp->data) {
			
//			printf("%d ", Bp->data);
			tem->next = Bp;
			tem = Bp;
			Bp = Bp->next;
		} else {
			Bp = Bp->next;  //相等情况 跳过B中 这个元素 
		}
			
	}while(Ap!=NULL&&Bp!=NULL);
	
	if(Ap!=NULL) {
		
		do{
//			printf("%d ",Ap->data);
			tem->next = Ap;
			tem = Ap;
			Ap = Ap->next;
		}while(Ap!=NULL);
	}
	
	if(Bp!=NULL) {
		do{
//			printf("%d ",Bp->data);
			tem->next = Bp;
			tem = Bp;
			Bp = Bp->next;
		}while(Bp!=NULL);
	}
	
	tem = NULL;
	
//	LinkList p;
//	p = *Chead;
//    do {
//		printf("%d ",p->data);
//		p = p->next;
//	}while(p!=NULL);
	
}



int main() {
	
	
	LinkList Ahead,Bhead;     //head 头指针 
	printf("创建A链表:\n");
	createlist(&Ahead);
	printf("A链表为:\n");
	print(Ahead);
	printf("\n创建B链表:\n");
	createlist(&Bhead);
	printf("B链表为:\n");
	print(Bhead);
	printf("\n");
	
	LinkList Chead;
	AandBtoC(Ahead,Bhead,&Chead);
	printf("合并后的C链表为:\n");
	print(Chead);

	//输入的AB 默认已经排序的 
	
	
	return 0;
}
