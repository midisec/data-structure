//实验6.c 
//by midi

#include <stdio.h>
#include <stdlib.h>


typedef struct monkey {
	int id;
	struct monkey *next;
}Monkey,*PMonkey;


//创建猴子循环单链表
PMonkey CreatList(int num) {
	PMonkey head,r,tmp;
	int i;
	
	head = (PMonkey)malloc(sizeof(Monkey));  //初始化 头结点存储猴子总数 
	head->id = num; 
	head->next = NULL;

	r = head;

	for(i = 1;i <= num;i++){
//		头插法 
		tmp = (PMonkey)malloc(sizeof(Monkey));
		tmp->id = i;
		tmp->next = NULL;
		r->next = tmp;
		r = r->next;

	}
	r->next = head->next;

	return head;
}


int SearchKing(PMonkey L) {
	 int num,per;
	 int i;
	 PMonkey p,tmp;  // 用tmp做中介
	 num = L->id;  // 头指针中的id数据记录总猴子数量 
     p = L;    
    
	 for(per = 13; num > 1; per--, num--){  //删到只有一只猴子存在
	
//		printf("per :%d num: %d \n",per,num);
        if(!per){   //到0重新循环
            per = 13;
        }
        for(i = 1; i < per; i++){

             p = p->next;  //指向要删除的猴子 p->next 
        }

        tmp = p->next;
        p->next = tmp->next;
        free(tmp);
    }    
    
    
    
    return p->id;
}



//void OutPut(PMonkey L) {
//	
//	PMonkey p,tmp;
//	
//	p = L->next;
//	
//	do {
//		
//		printf("%d", p->id);
//		p = p->next;
//		
//	} while(p != L->next);
//
//} 


int main() {
	PMonkey L;
	
	int num;
	printf("请输入猴子个数:\n");
	scanf("%d",&num);

	L = CreatList(num);
	
	int King_id; 
	King_id = SearchKing(L);
	printf("第 %d 个猴子是猴王\n",King_id);
	
//	OutPut(L); //测试单链表 
	return 0;

}
