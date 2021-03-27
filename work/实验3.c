//实验3.c 
//by midi

#include<stdio.h>
#include<stdlib.h>

#define TIMES 1000
// 寻找次数 

#define NUMS 10
// 洞口数

 
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
	
//	头插法 循环单链表  
    for(i=0;i<NUMS;i++)
    {
        p=(LinkList)malloc(sizeof(LNode));
        tem->next = p;
        tem = p;
        
//        (*head)->data++;   //计数用 
    }

	tem->next = *head;

}


void initlist(LinkList head)
{
    LinkList p;
    p=head->next;
    
    do {
    	p->data=1;
    	p=p->next;
	}while(p!=head);

    
}

void findrabbit(LinkList head)
{
    LinkList p;
    int i,j=1,q,n,u;
    p=head->next;
    //狐狸来了
    for(i=0;i<TIMES;i++)
    {
        u=((1.0/2)*j*(j+1));  //每次第u个洞口 

        u=u%NUMS;
//        printf("%d ",u);
        p=head->next;
        
        if(u==0) {
        	for(q=0;q<NUMS-1;q++) { //特殊情况  ！！ 此时第十个洞并非第一个洞 ！！ 一共有十个洞口 
            	p=p->next;
        		}
        		p->data=0;
        		j++;
		}else {
			
			
			
			
			for(q=1;q<u;q++) { //确保十个洞循环进,j是相隔的山洞数
            	p=p->next;
        		}
        	p->data=0;
        	j++;
	
			}

    }
}


void outputlist(LinkList head)
{
    LinkList p;
    p=head->next;
    int count=1; 

	do {
		

	   	if(p->data == 1) {
	   		
			printf("该洞口是: %d 号洞口 \n",count);
			p=p->next;
			count++;
			
			}
		else {
				p=p->next;
				count++;
			}
   	
   }while(p!=head);
//   printf("total:%d", (*head).data);
}

int main()
{
    LinkList head;     //head 头指针 
    createlist(&head);
    initlist(head);
    findrabbit(head);
    
    printf("\n"); 
    outputlist(head);
    return 0;
}
