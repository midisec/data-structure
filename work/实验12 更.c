//实验12.c 
//by midi

#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int arr[MAX];
//直接顺序查找 
// 1. 顺序查找 带监视哨 从后往前 
// 2. 顺序查找 递归实现 



int search(int arr[],int i,int key) {
	if(arr[i] == key) {
		return i;
	} else {
		return search(arr,i-1,key);
	}
} 



int main() {
	
	
	int nums,i;
	printf("一共有多少个数~?\n");
	scanf("%d",&nums);
	for(i=1;i<=nums;i++) {
		printf("请输入第%d个数:\n",i); 
		scanf("%d",&arr[i]);
	}
	printf("请输入要查找的数:\n");
	int key;
	scanf("%d",&key);
	arr[0] = key;
	
	while(1) {
		printf("------------------------\n");
		printf("请输入要查找的方法:\n");
		printf("1.顺序查找 带监视哨 从后往前 \n");
		printf("2.顺序查找 递归\n");
		printf("3.退出\n");
		printf("请输入要查找的方式:\n");
		printf("------------------------\n");
		int way;
		scanf("%d",&way);
		int result;
		switch(way) {
			case 1:
				while(arr[i] != key) {
					i--;
				}
			//	printf("%d",i);	
				if(i==0) {
					printf("没找到该数!\n");
					 
				} else {
					printf("找到了，这是第%d个数\n",i); 
				}
				;break;
			case 2:
				result = search(arr,nums,key);
				//	printf("%d",result);
				if(result) {
					printf("找到了，这是第%d个数\n",result);
				} else {
					printf("没找到该数!\n");
				};
				break;
			case 3:printf("\n886\n");exit(0);
				
			default:printf("输入有误!\n"); 
		} 
	}
	
	
	 

	return 0;
}
