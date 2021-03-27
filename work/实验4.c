//实验4.c 
//by midi

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


#define MAXSIZE 100

//顺序栈 

typedef struct Stack_number{
	double data[MAXSIZE];
	int top;
	
}Stack_number;

typedef struct Stack_operator{
	char data[MAXSIZE];
	int top;
	
}Stack_operator;


//初始化 
void init_number_stack(Stack_number *stack) {
	stack->top = 0;
}

void init_operator_stack(Stack_operator *stack) {
	stack->top = 0;
}



//入栈    data[0]不存数据  top指针指向最上层数据 
void Push_number(Stack_number *stack, double number) {
	stack->top++;
	stack->data[stack->top] = number;
} 

void Push_operator(Stack_operator *stack, char oper) {
	stack->top++;
	stack->data[stack->top] = oper;
}


//出栈
//需要取出当前的数
void Pop_number(Stack_number *stack, double *number) {
	*number = stack->data[stack->top];
	stack->top--;
}

void Pop_operator(Stack_operator *stack, char *oper) {
	*oper = stack->data[stack->top];
	stack->top--;
}


//取栈顶元素
double GetTop_number(Stack_number stack) {
	return stack.data[stack.top];
}


char GetTop_operator(Stack_operator stack) {
	return stack.data[stack.top];
}

//判断栈空

int isEmpty_number(Stack_number *stack) {
	if(stack->top == 0) {
		return 1;
	} else {
		return 0;
	}
}

int isEmpty_operator(Stack_operator *stack) {
	if(stack->top == 0) {
		return 1;
	} else {
		return 0;
	}
}



//判定运算符的栈顶运算符与读入的运算符之间优先关系
char Role(char c1,char c2) {
	
    char c;
    switch(c1){
        case '+':
        case '-':
	    	switch(c2){
		        case '+':
	            case '-':
		        case ')':
	            case '#':c='>';break;
		        default:c='<';
	    	}
			break;
        case '*':
        case '/':
            if(c2=='('){
				c='<';
			}
			else{
				c='>';
			}
            break;
        case '(':
		    if(c2==')'){
				c='=';
			}
		    else{
				c='<';
			}
            break;
        case ')':c='>';break;
        case '#':
		    if(c2=='#'){
				c='=';
			}
		    else{
				c='<';
			}
    }
    return c;
}





//是否是运算符 
int isOperator(char c) {
	char ch[7] = "+-*/()#";   //   # 不能丢。。。 否则死循环 一直判断是 数组 
	
	int i,flag=0;
	for(i=0;i<7;i++) {
		if(ch[i]==c) {
			flag=1;
			break;
		}
	}
	
	
	return flag;
	
} 


//计算 +-*/ 
double jisuan(double a,char oper, double b) {
	double sum;
    switch(oper)
    {
    	case '+':sum=a+b;break;
		case '-':sum=a-b;break;
        case '*':sum=a*b;break;
        case '/':sum=a/b;break;
    }
    return sum;
}



void is_legal(char *s) {
	//1 括号问题  (括号必须在 )前面
	int i;
	int flag1=0,flag2=0;
	
	for(i = 0;i < strlen(s);i++) {
		if(s[i] == '(') {
			flag1 = 1;
		}
		if(s[i] == ')') {
			flag2 = 1;
			break;
		}
		
	}
	
	if(flag1 == flag2) {
		//合法
	}
	if(flag1 ==1 && flag2 ==0) {
		//缺少右括号 
		printf("输入格式有误！输入缺少右括号！！ \n");
		getchar();
		exit(0);
	} 
	if(flag1 ==0 && flag2 ==1) {
		//右括号先出现 
		printf("输入格式有误！输入的右括号先出现 ！！ \n");
		getchar();
		exit(0);
	}
	
	//2 连续运算符问题  除了括号 运算符不能连续出现前面
	for(i = 0;i < strlen(s);i++) {
		if(i > 0 && i < strlen(s) - 1 && isOperator(s[i]) && (isOperator(s[i - 1]) || isOperator(s[i + 1]))
			&&(s[i] != '(' && s[i] != ')') && (s[i - 1] != '(' && s[i - 1] != ')')
			&&(s[i + 1] != '(' && s[i + 1] != ')')) {
				
				
			printf("输入格式有误！连续输入了运算符！！\n");
			getchar();
			exit(0);
	}
	
	
}
}
 


double Yunsuan(char *s) {
	
	//假设输入的运算符不合法：
	is_legal(s);
	
	
	
	//对输入的多项式进行检查！！
	int i=0,flag=0;
	char e;
	double a,b;
	double result;
	
	Stack_number SN;
	Stack_operator SO;
	
	init_number_stack(&SN);
	init_operator_stack(&SO);
	
	int len = strlen(s);
	char c1=s[0];  //用上一个字符处理小数问题 
	s[len] = '#';
	s[len+1] = '\0';   //上一步将/0覆盖成# 需要重新加 /0 ！！
	Push_operator(&SO,'#');
	
	while(s[i]!='#'|| GetTop_operator(SO) != '#') {
//		printf("yes1 ");
//		printf("%d",i);
		
		if(s[i] == ' '){
			i++;
			continue;
		}
		//判断该字符是 数组还是运算符  
		if( !isOperator(s[i])) {  //不是运算符的时候 
			
			
			if(c1=='.'){//如果上一个字符是小数点
		        flag++;
		    }
		    if(flag){
		    	double t;
		    	Pop_number(&SN,&t);
				Push_number(&SN,t + (double)(s[i] - '0') / pow(10,flag));//对小数点后的部分 按位数运算并入栈 
				flag++;
			}
			
			if(s[i]!='.'&&!flag){
	            if(!isOperator(c1)&&!isEmpty_number(&SN)){ //如果上一个字符是数字（说明是多位数） 根据位数运算后入栈
	            	double t;
	            	Pop_number(&SN,&t);
	                Push_number(&SN,t * 10 + s[i] - '0');
	            }
	            else//否则压入运算数栈
	            	Push_number(&SN,(double)(s[i]-'0'));
		    }

	    	c1=s[i];
			i++; //读取下一个字符
		}
		
		else {
//			printf("no ");
			
			flag = 0;
			switch(Role(GetTop_operator(SO),s[i])) {
				case '>':
					Pop_operator(&SO,&e);
					Pop_number(&SN,&b);
					Pop_number(&SN,&a);
					Push_number(&SN,jisuan(a,e,b));
					break;
				case '=':
					Pop_operator(&SO,&e);
					c1 = s[i++];
					break;
				case '<':
					Push_operator(&SO,s[i]);
					c1 = s[i++];
					break;
					
			}
			
		}
		
	}
	result = GetTop_number(SN);
	
	return result;
}



int main() {
	
	
	char s[100];
	printf("请输入表达式：\n");
	gets(s);

	double result = Yunsuan(s);
	
	printf("%lf",result);

//	printf("%c", Role('+','+'));
	
	return 0;
}
