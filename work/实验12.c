//实验12.c 
//by midi

#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int arr[MAX];
//直接顺序查找 
// 1. 顺序查找 带监视哨 从后往前 
// 2. 折半查找 递归实现 

int zheban(int arr[],int l,int r,int key) {
	
	if(l>r) {
		return -1;
	} 
	int mid = (l+r)/2;
	if(arr[mid]==key) {
		return mid;
	} else if(key<arr[mid]) {
		return zheban(arr,l,mid-1,key);
	} else {
		return zheban(arr,mid+1,r,key);
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
		printf("2.折半查找 递归\n");
		printf("3.退出");
		printf("请输入要查找的方式:\n");
		printf("------------------------\n");
		int way;
		scanf("%d",&way);
		switch(way) {
			case 1:
				while(arr[i] != key) {
					i--;
				}
			//	printf("%d",i);	
				if(i==0) {
					printf("没找到该数!\n");
					 
				} else {
					printf("找到了，这是第%d个数\n"); 
				}
				;break;
			case 2:
				if(zheban(arr,1,nums,key) == -1) {
					printf("没找到该数!\n");
				} else {
					printf("该数在第%d个\n",zheban(arr,1,nums,key));
				} 
				break;
			case 3:printf("\n886\n");exit(0);
				
			default:printf("输入有误!\n"); 
		} 
	}
	
	
	 
	
	
	
//	while(arr[i] != key) {
//		i--;
//	}
////	printf("%d",i);	
//	if(i==0) {
//		printf("没找到该数!\n");
//		 
//	} else {
//		printf("找到了，这是第%d个数\n"); 
//	}
	

//	int id = zheban(arr,1,nums,key);
//	if(id == -1) {
//		printf("没找到该数!\n");
//	} else {
//		printf("该数在第%d个",id);
//	} 

	
	
	
	return 0;
}
