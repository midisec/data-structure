//实验5.c 
//by midi

#include<stdio.h>
#define MAXNUM 20


typedef int ElemType;

void Create(ElemType x[],int *n){
	int i;
	printf("\nPlease input n=");
	scanf("%d",&*n);
	printf("Please input %d data:",*n);
	for(i=1;i<=*n;i++) {
		scanf("%d",&x[i]);
	}

}


double Maxmin(ElemType *x,int n,int *max,int *min){
	int i;
	double sum;
	
	*max=*min=*(x+1);
	for(i=1;i<=n;i++){
		sum += *(x+i);
		if(*(x+i)>*max) {
			*max=*(x+i);
		}
		if(*(x+i)<*min) {
			*min=*(x+i);
		}
	}
	
	
	return sum/n;
	
}


void Swap(ElemType x[],int n) {
	int i;
	
	int max,min;
	max = min = x[1];

	int max_index=1,min_index=1;
	
	for(i=1;i<=n;i++) {
//		printf(" local : x: %d \n", x[i]);
		if(max < x[i]) {
			max = x[i];
			max_index = i;
		}
		if(min > x[i]) {
			min = x[i];
			min_index = i;
		}
		
//		printf("\n max_index %d ,min_index %d \n",max_index,min_index);
	}
	
	
	
	int tem;
	tem = x[max_index];
	x[max_index] = x[min_index];
	x[min_index] = tem;
	
	
	
	for(i=1;i<=n;i++) {
		printf("%4d",x[i]);
	
	}
	
}




void Sorted(ElemType a[],int n) {
	int i,j;
	int buf;
	for (i=1; i<n; ++i)  //比较n-1轮
    {
        for (j=1; j<n-i+1; ++j)  //每轮比较n-1-i次,
        {
            if (a[j] > a[j+1])
            {
                buf = a[j];
                a[j] = a[j+1];
                a[j+1] = buf;
            }
        }
    }
    
    for(i=1;i<=n;i++) {
		printf("%4d",a[i]);
	
	}
    
}


void main(){
	



	ElemType a[MAXNUM+1];
	
	int i,n,max,min;
	Create(a,&n);
	
	
	printf("\nCreate is completed!\nThe data is:");
	for(i=1;i<=n;i++) {
		printf("%4d",a[i]);
	}
	
	double aver;
	//	1．在上例的基础上，修改函数Maxmin，使其还能计算这些数据的平均值，并返回；
	//     对上例采用数组名作为函数的实参和形参，修改成用指向数组的指针作参数完成相应功能。
	ElemType *p;
	p = a;
	aver = Maxmin(p,n,&max,&min);
	printf("\nmax=%d    min=%d",max,min);
	printf("\n aver : %lf",aver);
	
	
	
	//  2．设计算法将一组数据中的最大值和最小值进行交换，然后输出这组数据。要求上机编程实现。
	printf("\n****************swap ***************\n");
	Swap(a,n);
	

		

	//  3．用冒泡排序法将一组数据从小到大重新排列并输出。
	printf("\n****************sort ***************\n");
	Sorted(a,n);


}
