#pragma once

typedef struct _stack {
	char *stack;		/* stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;		/* ������ ũ��(size) */
	int top;		/* ������ ��,�ⱸ ��ġ���� ���� */
}Stack;

typedef struct _intstack {
	int *istack;
	int size;
	int top;
}IStack;

/*���� ���� �޸� �Ҵ�*/
int createIStack(IStack*, int);

/*���� ���� �޸𸮰� �� �� �ִ��� �˻�*/
int isIStackFull(IStack);

/*���� ���� �޸𸮰� ����ִ��� �˻�*/
int isIStackEmpty(IStack *sPtr);

/*���� ���� �޸𸮿� �����͸� ����*/
int ipush(IStack *, int);

/*���� ���� �޸𸮿��� �����͸� ����*/
int ipop(IStack *, int *);

/*���� ���� �޸� �Ҵ�*/
int createStack(Stack *, int);	

/*���� ���� �޸𸮰� �� ���ִ��� �˻�*/
int isStackFull(Stack *sPtr);

/*���� ���� �޸𸮰� ����ִ��� �˻�*/
int isStackEmpty(Stack *sPtr);

/*���� ���� �޸𸮿� �����͸� ����*/
int push(Stack *, char);	

/*���� ���� �޸𸮿��� �����͸� ����*/
int pop(Stack *,char *);

/*���� ���� �� ���� �ִ� �����͸� ��*/
char peek(Stack *);

/*���� ���� �޸𸮿� �ִ� �����͸� ���*/
void printStack(Stack*);		
	
/*���� ǥ����� ���� ǥ������� ��ȯ, ���� ǥ����� �̿��Ͽ� �����ϴ� �Լ�*/
void ConvAndCalc(char str[]);

/*�������� �켱������ �����ִ� �Լ�*/
int PriOperator(char op);

/*�������� �켱������ ���� �ִ� �Լ�*/
int ComOperator(char op1, char op2);





