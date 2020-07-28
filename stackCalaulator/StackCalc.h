#pragma once

typedef struct _stack {
	char *stack;		/* stack으로 사용되는 동적할당 배열을 가리키는 포인터 변수 */
	int size;		/* 스택의 크기(size) */
	int top;		/* 스택의 입,출구 위치정보 저장 */
}Stack;

typedef struct _intstack {
	int *istack;
	int size;
	int top;
}IStack;

/*정수 스택 메모리 할당*/
int createIStack(IStack*, int);

/*정수 스택 메모리가 꽉 차 있는지 검사*/
int isIStackFull(IStack);

/*정수 스택 메모리가 비어있는지 검사*/
int isIStackEmpty(IStack *sPtr);

/*정수 스텍 메모리에 데이터를 저장*/
int ipush(IStack *, int);

/*정수 스택 메모리에서 데이터를 빼냄*/
int ipop(IStack *, int *);

/*문자 스택 메모리 할당*/
int createStack(Stack *, int);	

/*문자 스택 메모리가 꽉 차있는지 검사*/
int isStackFull(Stack *sPtr);

/*문자 스택 메모리가 비어있는지 검사*/
int isStackEmpty(Stack *sPtr);

/*문자 스텍 메모리에 데이터를 저장*/
int push(Stack *, char);	

/*문자 스택 메모리에서 데이터를 빼냄*/
int pop(Stack *,char *);

/*문자 스택 맨 위에 있는 데이터를 봄*/
char peek(Stack *);

/*문자 스택 메모리에 있는 데이터를 출력*/
void printStack(Stack*);		
	
/*중위 표기식을 후위 표기식으로 변환, 후위 표기식을 이용하여 연산하는 함수*/
void ConvAndCalc(char str[]);

/*연산자의 우선순위를 정해주는 함수*/
int PriOperator(char op);

/*연산자의 우선순위를 비교해 주는 함수*/
int ComOperator(char op1, char op2);





