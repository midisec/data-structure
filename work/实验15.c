//ʵ��15.c 
//by midi

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 200
typedef struct {
	int id;
	char name[50];
	double score[5];
//	政治、语文、英语、数学、物理
	double total;
}Student;

typedef struct {
	Student *elem;
	int length;
}SqList;

int rule_lenght;
//添加了第一条数据之后 后面添加数据的准考证号长度必须符合一致 

int ex_zero_nums;
//若准考证前面是0开头 记录0的个数; 

void CreateSqlist(SqList *stu_system) {
	(*stu_system).elem=(Student *)malloc(MAXSIZE*sizeof(Student));
	(*stu_system).length = 0;
//	printf("顺序表创建成功!\n");
}
 
int cheak_id(SqList *stu_system, int id) {
	int i;
	int flag=1;
	
	if((*stu_system).length == 0) {
		return 1;
	}
	else {
		for(i=0;i<=(*stu_system).length;i++) {
			if((*stu_system).elem[i].id == id) {
				flag =0;
			}
		} 
	}
	
	return flag;
} 


int cheak_score(double score[],int n) {
	int i=0;
	for(i;i<n;i++) {
		if(score[i] < 0) {
			return 0;
		}
	}
	return 1;
}


double get_score_sum(double arr[]) {
	int i=0;
	double sum = 0;
	for(i;i<5;i++) {
		sum += arr[i];
	}
	return sum;
} 


void init_student(SqList *stu_system) {
	int i=(*stu_system).length;
	
	
	char cheak_zero[50]; 
	int tem_id;
	char tem_name[50];
	double tem_score[5];
	

	
	while(1) {

//		(*stu_system).elem[i].id
		
		
		//第一个数据 特别重要 来判断用户输入的准考证号 前面有几个0 
		if((*stu_system).length == 0) {
			printf("请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩(-1为结束录入)\n当前共有%d个学生信息! \n",(*stu_system).length);
			scanf("%s %s %lf %lf %lf %lf %lf",cheak_zero,tem_name,&tem_score[0],&tem_score[1],&tem_score[2],&tem_score[3],&tem_score[4]);
			//此时 准考证号为 字符数组 来判断 准考证号前的0     
			//区分 
			//010015
			//000001
			if(cheak_score(tem_score,4)) {
				
				int k=0;
				//统计总长 
				while(cheak_zero[k] != '\0') {
					rule_lenght++;
					k++;
				}
				
				//统计前面的0
				k=0;
				while(cheak_zero[k] != '\0') {
					if(cheak_zero[k]=='0') {
						ex_zero_nums++;
						k++;
					}
					else {
						break;
					}
				}
				if(ex_zero_nums>=2) {
					ex_zero_nums =2;
				}
				//添加 
				//将字符串改成相应整形数字
				 
				tem_id = atoi(cheak_zero);
//				printf("%d",tem_id);
				
				if(cheak_id(stu_system,tem_id)) {
					(*stu_system).elem[i].id = tem_id;
					strcpy((*stu_system).elem[i].name,tem_name);
					(*stu_system).elem[i].score[0] = tem_score[0];
					(*stu_system).elem[i].score[1] = tem_score[1];
					(*stu_system).elem[i].score[2] = tem_score[2];
					(*stu_system).elem[i].score[3] = tem_score[3];
					(*stu_system).elem[i].score[4] = tem_score[4];
					printf("第%d条数据添加成功!\n",(*stu_system).length + 1);
					
					(*stu_system).elem[i].total = tem_score[0]+tem_score[1]+tem_score[2]+tem_score[3]+tem_score[4];
					i++;
					(*stu_system).length++;
				}else {
					printf("您添加的准考证号有重!请重新添加\n"); 
				}
				

		}
		
		}
		
		
		else {
			
		printf("请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩\n当前共有%d个学生信息!\n",(*stu_system).length);
		
	
		scanf("%d",&tem_id);
		if(tem_id == -1) {
			printf("录入结束!\n");
			break;
		}
		
		scanf("%s %lf %lf %lf %lf %lf",tem_name,&tem_score[0],&tem_score[1],&tem_score[2],&tem_score[3],&tem_score[4]);
		

		
		if(cheak_score(tem_score,4)) {
			//先进行对分数的检查  若分数不符合 则直接返回重新输入
			// 先检查分数规则，再检查准考证号，减少了对数据库中查找
			 if(cheak_id(stu_system,tem_id)) {
			 		

					(*stu_system).elem[i].id = tem_id;
					strcpy((*stu_system).elem[i].name,tem_name);
					(*stu_system).elem[i].score[0] = tem_score[0];
					(*stu_system).elem[i].score[1] = tem_score[1];
					(*stu_system).elem[i].score[2] = tem_score[2];
					(*stu_system).elem[i].score[3] = tem_score[3];
					(*stu_system).elem[i].score[4] = tem_score[4];
					printf("第%d条数据添加成功!\n",(*stu_system).length + 1);
					(*stu_system).elem[i].total = tem_score[0]+tem_score[1]+tem_score[2]+tem_score[3]+tem_score[4];
					i++;
					(*stu_system).length++;
					
					
				}else {
					printf("您添加的准考证号有重!请重新添加\n"); 
				}
			 
			 
			 
		} else {
			printf("您输入的分数有误!请重新输入!\n");
		} 
		
		
		
	}
	}
}


//判断准考证有多长
int get_id_length(int id) {
	int length=0;
	while(id / 10 > 0) {
		length++;
		id = id/10;
	}
	
	return length+1;
} 


//根据准考证号排序 如果用二分查找 
void sort(SqList *stu_system) {
	//准考证长度统一，先来判断下有多长
	
}


// 顺序查找 
void search_function1(SqList *stu_system, int id) {
	//根据准考证号查找!
	
	int i;
	int flag=-1;
	int global = -1;
	if((*stu_system).length == 0) {
		printf("对不起，您还没有添加学生信息!");
	}
	else {
		for(i=0;i<(*stu_system).length;i++) {
//			printf("i:%d,id=%d, keyid= %d\n",i,(*stu_system).elem[i].id,id);
			if((*stu_system).elem[i].id == id) {
				flag = (*stu_system).elem[i].id;
				global =i;
			}
		} 
	}
//	printf("flag:%d\n",flag);
	
	if(flag!=-1) {
		printf("找到了！该学生的信息为:\n");
		// 准考证的补充
		
		if(get_id_length(flag) != rule_lenght) {
			
			printf("学号为:");
			for(i=get_id_length(flag);i<rule_lenght;i++) {
				printf("0");
			}
			printf("%d,姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n",(*stu_system).elem[global].id,(*stu_system).elem[global].name,(*stu_system).elem[global].score[0],(*stu_system).elem[global].score[1],(*stu_system).elem[global].score[2],(*stu_system).elem[global].score[3],(*stu_system).elem[global].score[4],get_score_sum((*stu_system).elem[global].score));
			
		} 
		else {
			printf("学号为:%d,姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n",(*stu_system).elem[global].id,(*stu_system).elem[global].name,(*stu_system).elem[global].score[0],(*stu_system).elem[global].score[1],(*stu_system).elem[global].score[2],(*stu_system).elem[global].score[3],(*stu_system).elem[global].score[4],get_score_sum((*stu_system).elem[global].score));

		} 
		
	} else {
		printf("没有找到该学生!\n");
	}
}



int get_max_2_nums(int id,int n) {
	
	int two_max_nums;

	while(n>0) {
		if(n==2){
			two_max_nums = id;	
			break;
		} 
		else {
			id = id/10;
			n = n-1;
		}
	}
	return two_max_nums;
	
}

int get_max_1_nums(int id,int n) {
	
	int one_max_nums;

	while(n>0) {
		if(n==1){
			one_max_nums = id;	
			break;
		} 
		else {
			id = id/10;
			n = n-1;
		}
	}
	return one_max_nums;
	
}



void out_function2(SqList *stu_system, int id,double key_sum,int how) {
	
	
	
//	printf("function2 second :%d\n",id);
	// how 1 为大于
	// how 0 为等于
	// how -1为小于 
	// how 2 没有该条件 默认 
	
	int i,j;
	int tem_id;
	if (how == 2) { 
	 
		if((*stu_system).length == 0) {
			printf("对不起，您还没有添加学生信息!");
		}
		else {
			for(i=0;i<(*stu_system).length;i++) {
				
				if(get_id_length((*stu_system).elem[i].id) < rule_lenght) {
					
					//准考试第一位为0
					if(rule_lenght - get_id_length((*stu_system).elem[i].id) == 1) {
						tem_id = get_max_1_nums((*stu_system).elem[i].id,rule_lenght-1);
						if(id == tem_id) {
							printf("学号为:0");
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score)); 
	
						}
					} 
					else {
						if(id == 0) {
							
						//准考试第一位第二位都为0
							
						printf("学号为:");
						for(j=get_id_length((*stu_system).elem[i].id);j<rule_lenght;j++) {
							printf("0");
						}
						printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
							
							
							
						}

						
	
					}
					
				}else {
					//准考证第一位非0 
					tem_id = get_max_2_nums((*stu_system).elem[i].id,rule_lenght);
					
					if(id == tem_id) {
						printf("学号为:%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
					}
				}
				
				
			} 
		}
	} 
	else if(how == -1) {
		if((*stu_system).length == 0) {
			printf("对不起，您还没有添加学生信息!");
		}
		else {
			for(i=0;i<(*stu_system).length;i++) {
				
				if(get_id_length((*stu_system).elem[i].id) < rule_lenght) {
					//准考试第一位为0
					
					if(rule_lenght - get_id_length((*stu_system).elem[i].id) == 1) {
						tem_id = get_max_1_nums((*stu_system).elem[i].id,rule_lenght-1);
						if(id == tem_id && get_score_sum((*stu_system).elem[i].score) <key_sum) {
							printf("学号为:0");
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
	
						}
					} 
					else {
						
						if(id == 0 && get_score_sum((*stu_system).elem[i].score) <key_sum) {
							
							printf("学号为:");
							for(j=get_id_length((*stu_system).elem[i].id);j<rule_lenght;j++) {
								printf("0");
							}
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
						}

						
					//准考试第一位第二位都为0	
					}
					
				}else {
					//准考证第一位非0 
					tem_id = get_max_2_nums((*stu_system).elem[i].id,rule_lenght);
					
					if(id == tem_id && get_score_sum((*stu_system).elem[i].score) <key_sum) {
						printf("学号为:%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
					}
				}
				
				
			} 
		}
		
	} 
	else if(how == 0) {
		if((*stu_system).length == 0) {
			printf("对不起，您还没有添加学生信息!");
		}
		else {
			for(i=0;i<(*stu_system).length;i++) {
				
				if(get_id_length((*stu_system).elem[i].id) < rule_lenght) {
					//准考试第一位为0
					
					if(rule_lenght - get_id_length((*stu_system).elem[i].id) == 1) {
						tem_id = get_max_1_nums((*stu_system).elem[i].id,rule_lenght-1);
						if(id == tem_id && get_score_sum((*stu_system).elem[i].score) == key_sum) {
							printf("学号为:0");
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
	
						}
					} 
					else {
						
						if(id == 0 &&get_score_sum((*stu_system).elem[i].score) ==key_sum) {
							
							printf("学号为:");
							for(j=get_id_length((*stu_system).elem[i].id);j<rule_lenght;j++) {
								printf("0");
							}
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
						}

						

					}
					
				}else {
					//准考证第一位非0 
					tem_id = get_max_2_nums((*stu_system).elem[i].id,rule_lenght);
					
					if(id == tem_id && get_score_sum((*stu_system).elem[i].score) ==key_sum) {
						printf("学号为:%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
					}
				}
				
				
			} 
		}
	}
	else {
				if((*stu_system).length == 0) {
			printf("对不起，您还没有添加学生信息!");
		}
		else {
			for(i=0;i<(*stu_system).length;i++) {
				
				if(get_id_length((*stu_system).elem[i].id) < rule_lenght) {
					//准考试第一位为0
					
					if(rule_lenght - get_id_length((*stu_system).elem[i].id) == 1) {
						tem_id = get_max_1_nums((*stu_system).elem[i].id,rule_lenght-1);
						if(id == tem_id && get_score_sum((*stu_system).elem[i].score) >key_sum) {
							printf("学号为:0");
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
	
						}
					} 
					else {
						
						if(id == 0 && get_score_sum((*stu_system).elem[i].score) >key_sum) {
							
							printf("学号为:");
							for(j=get_id_length((*stu_system).elem[i].id);j<rule_lenght;j++) {
								printf("0");
							}
							printf("%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
						}

						
					//准考试第一位第二位都为0	
					}
					
				}else {
					//准考证第一位非0 
					tem_id = get_max_2_nums((*stu_system).elem[i].id,rule_lenght);
					
					if(id == tem_id && get_score_sum((*stu_system).elem[i].score) >key_sum) {
						printf("学号为:%d 姓名为:%s,政治分数:%lf、语文分数:%lf、英语分数:%lf、数学分数:%lf、物理分数:%lf,总分为:%lf.\n\n",(*stu_system).elem[i].id,(*stu_system).elem[i].name,(*stu_system).elem[i].score[0],(*stu_system).elem[i].score[1],(*stu_system).elem[i].score[2],(*stu_system).elem[i].score[3],(*stu_system).elem[i].score[4],get_score_sum((*stu_system).elem[i].score));
					}
				}
				
				
			} 
		}
		
	}
	
}

int main() {
	SqList *L=( SqList *)malloc(sizeof(SqList));
	CreateSqlist(L);
	init_student(L);



	int id;
	
	int stu_id;
	
	int are_id;
	
	double global_sum;
	
	int score_choose_id;
	while(1) {
		
		printf("---------------------------------\n");
		printf("---------------------------------\n");
		printf("1.查找\n");
		printf("2.输出\n");
		printf("3.计算\n"); 
		printf("4.退出\n"); 
		printf("---------------------------------\n");
		printf("---------------------------------\n");
		
		printf("请输入方法id:\n");
		scanf("%d",&id);
		switch(id) {
			case 1:
				printf("请输入要查找学生的准考证号:\n");
				scanf("%d",&stu_id);
//				printf("stu_id: %d\n",stu_id); 
				search_function1(L,stu_id);
				printf("\n");
			break;
			case 2:
				printf("请输入要输出的地区编号(两位):\n");
				scanf("%d",&are_id);
				printf("请输入要输出的总分信息:\n");
				scanf("%lf",&global_sum);
				if(are_id>=0 && are_id <=99 &&global_sum) {
					printf("---------------------------------\n");
					printf("1.总分大于%lf\n",global_sum);
					printf("2.总分等于%lf\n",global_sum);
					printf("3.总分小于%lf\n",global_sum);
					printf("4.输出该地区所有学生信息\n"); 
					printf("---------------------------------\n");
					
					scanf("%d",&score_choose_id);
					printf("输出结果为:\n"); 
					switch(score_choose_id) {
						case 1:out_function2(L,are_id,global_sum,1);break;
						case 2:out_function2(L,are_id,global_sum,0);break;
						case 3:out_function2(L,are_id,global_sum,-1);break;
						case 4:out_function2(L,are_id,global_sum,2);break;
						default:printf("您的输入有误！\n");
					}

					
				} else {
					printf("您输入的信息有误！\n"); 
				}
				printf("\n"); 
				break;
			case 3:
				printf("顺序表长度为:%d,平均查找长度为:%lf\n",L->length,(1+L->length)/2.0);
				break; 
				
			
			default:printf("您的输入有误！\n");
			case 4:printf("\n886\n");exit(0);
		}
		
	}
	
	
//	printf("准考证号总长度：%d 准考证前有几个0(地区上的)：%d",rule_lenght,ex_zero_nums);
	return 0;
}


//测试用例:
/*
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩(-1为结束录入)
当前共有0个学生信息!
000001
wmd1
10 20 30 40 50
第1条数据添加成功!
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩
当前共有1个学生信息!
000002
wmd2
20 30 40 50 60
第2条数据添加成功!
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩
当前共有2个学生信息!
010001
wmd3
20 40 40 50 60
第3条数据添加成功!
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩
当前共有3个学生信息!
010002
wmd4
30 40 40 20 60
第4条数据添加成功!
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩
当前共有4个学生信息!
660001
wmd5
30 30 30 30 30
第5条数据添加成功!
请输入学生的准考证号 姓名 以及政治、语文、英语、数学、物理成绩
当前共有5个学生信息!
-1
录入结束!



方法1 测试
 

请输入方法id:
1
请输入要查找学生的准考证号:
660000
没有找到该学生!

---------------------------------
---------------------------------
1.查找
2.输出
3.计算
4.退出
---------------------------------
---------------------------------
请输入方法id:
1
请输入要查找学生的准考证号:
660001
找到了！该学生的信息为:
学号为:660001,姓名为:wmd5,政治分数:30.000000、语文分数:30.000000、英语分数:30.000000、数学分数:30.000000、物理分数:30.000000,总分为:150.000000.
 
 
 
 请输入方法id:
2
请输入要输出的地区编号(两位):
00
请输入要输出的总分信息:
100
---------------------------------
1.总分大于100.000000
2.总分等于100.000000
3.总分小于100.000000
4.输出该地区所有学生信息
---------------------------------
4
输出结果为:
学号为:000001 姓名为:wmd1,政治分数:10.000000、语文分数:20.000000、英语分数:30.000000、数学分数:40.000000、物理分数:50.000000,总分为:150.000000.

学号为:000002 姓名为:wmd2,政治分数:20.000000、语文分数:30.000000、英语分数:40.000000、数学分数:50.000000、物理分数:60.000000,总分为:200.000000.




方法2 测试
---------------------------------
---------------------------------
1.查找
2.输出
3.计算
4.退出
---------------------------------
---------------------------------
请输入方法id:
2
请输入要输出的地区编号(两位):
00
请输入要输出的总分信息:
160
---------------------------------
1.总分大于160.000000
2.总分等于160.000000
3.总分小于160.000000
4.输出该地区所有学生信息
---------------------------------
3
输出结果为:
学号为:000001 姓名为:wmd1,政治分数:10.000000、语文分数:20.000000、英语分数:30.000000、数学分数:40.000000、物理分数:50.000000,总分为:150.000000.



方法3 测试

---------------------------------
---------------------------------
1.查找
2.输出
3.计算
4.退出
---------------------------------
---------------------------------
请输入方法id:
3
顺序表长度为:5,平均查找长度为:3.000000

---------------------------------

*/ 


