#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _stack {
	char *stack;		/*(���ڿ�) stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;		/* ������ ũ��(size) */
	int top;		/* ������ ��,�ⱸ ��ġ���� ���� */
}Stack;

typedef struct _intstack {
	int *istack;      /*(����) stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;       /* ������ ũ��(size) */
	int top;        /* ������ ��,�ⱸ ��ġ���� ���� */
}IStack;

/*�Լ� �����*/
int createStack(Stack *sp, int size);    /*���� ���� �޸��� �Ҵ�*/
int isStackFull(Stack *sp);              /*���� ������ �� ���ִ��� �˻�*/
int isStackEmpty(Stack *sp);             /*���� ������ ����ִ��� �˻�*/
int push(Stack *sp, char inData);        /*���� ���ÿ� �����͸� �ϳ� ������*/
int pop(Stack *sp, char *popData);       /*���� ���ÿ��� �����͸� ����*/
char peek(Stack *sp);                    /*���� ���ÿ��� �� ���� �����͸� ��*/
int createIStack(IStack *sp, int size);  /*���� ���� �޸��� �Ҵ�*/
int isIStackFull(IStack *sp);            /*���� ������ �� ���ִ��� �˻�*/
int isIStackEmpty(IStack *sp);           /*���� ������ ����ִ��� �˻�*/
int ipush(IStack *sp, int inData);       /*���� ���ÿ� �����͸� �ϳ� ������*/
int ipop(IStack *sp, int *popData);      /*���� ���ÿ��� �����͸� ����*/
int priOperator(char op);                /*�������� �켱������ �����ִ� �Լ�*/
int comOperator(char op1, char op2);     /*�������� �켱������ �����ִ� �Լ�*/
void newArray(char str[]);               /*���Ⱑ �Էµ� ������ ���Ӱ� �ϳ��� �迭�� �ִ� �۾��� ���ִ� �Լ�*/
int calc(int num1, int num2, char c);    /*������ �����ϴ� �Լ�*/
void convAndCalc(char str[]);            /*���� ǥ����� ���� ǥ������� ��ȯ, ���� ǥ����� �̿��Ͽ� �����ϴ� �Լ�*/

int main()
{
	char exit[] = "q\n";//fgets�Լ��� ���� ���� \n �� �����Ƿ� ����.
	printf("\n*************���� ���α׷� �Դϴ�*************\n");
	printf("\n@q�� �Է� ������ ����˴ϴ�.\n");
	printf("\n@������ �߻� ������ ������ �����ϴ�.\n");
	printf("\n1, ¦�� ���� �ʴ� ��ȣ�� ���\n");
	printf("\n2, '+' '-' '*' '/' '%' '^' '(' ')' �̿��� ��ȣ�� ����ϴ� ���\n");
	printf("\n3,�����ڸ� ���ӵǰ� ����� ���\n");
	printf("\n4,���Ŀ� ���ڸ� ����� ���\n");
	printf("\n*************���� ���α׷��� �����մϴ�*************\n");
	while (1)
	{
		char str[100];
		printf("\n������ �Է��� �ּ���->");
		fgets(str, 100, stdin);//���� ���ڵ� �Է� �ޱ� ���� fget�Լ� ���
		if (!strcmp(str, exit))
		{
			printf("\n*************���� ���α׷��� �����մϴ�*************\n");
			break;
		}

		convAndCalc(str);
		printf("\n**********************************************************************\n");
	}
}

/*���� ���� �޸��� �Ҵ�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int createStack(Stack *sp, int size)
{
	if (sp == NULL)
	{
		return 0;
	}
	sp->stack = (char*)calloc(size, sizeof(char));
	if (sp->stack != NULL)
	{
		sp->size = size;
		sp->top = -1;
		return 1;
	}
}

/*���� ������ �� ���ִ��� �˻�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int isStackFull(Stack *sp)
{
	if (sp == NULL)
	{
		return 0;
	}
	if (sp->top >= sp->size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*���� ������ ����ִ��� �˻�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int isStackEmpty(Stack *sp)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (sp->top < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*���� ���ÿ� �����͸� �ϳ� ������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int push(Stack *sp, char inData)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (isStackFull(sp))
	{
		return 0;
	}
	else
	{
		sp->top++;
		sp->stack[sp->top] = inData;
		return 1;
	}
}

/*���� ���ÿ��� �����͸� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int pop(Stack *sp, char *popData)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (isStackEmpty(sp))
	{
		return 0;
	}
	else
	{
		*popData = sp->stack[sp->top];
		sp->top--;
		return 1;
	}
}

/*���� ���ÿ��� �� ���� �����͸� ��*/
char peek(Stack *sp)
{
	char peek;
	if (isStackEmpty(sp))
	{
		return NULL;
	}

	peek = sp->stack[sp->top];
	return peek;
}


/*���� ���� �޸��� �Ҵ�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int createIStack(IStack *sp, int size)
{
	if (sp == NULL)
	{
		return 0;
	}
	sp->istack = (int*)calloc(size, sizeof(int));
	if (sp->istack != NULL)
	{
		sp->size = size;
		sp->top = -1;
		return 1;
	}
}

/*���� ������ �� ���ִ��� �˻�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int isIStackFull(IStack *sp)
{
	if (sp == NULL)
	{
		return 0;
	}
	if (sp->top >= sp->size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*���� ������ ����ִ��� �˻�*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int isIStackEmpty(IStack *sp)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (sp->top < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*���� ���ÿ� �����͸� �ϳ� ������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int ipush(IStack *sp, int inData)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (isStackFull(sp))
	{
		return 0;
	}
	else
	{
		sp->top++;
		sp->istack[sp->top] = inData;
		return 1;
	}
}

/*���� ���ÿ��� �����͸� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int ipop(IStack *sp, int *popData)
{
	if (sp == NULL)
	{
		return 0;
	}

	if (isStackEmpty(sp))
	{
		return 0;
	}
	else
	{
		*popData = sp->istack[sp->top];
		sp->top--;
		return 1;
	}
}





/*�������� �켱������ �����ִ� �Լ�*/
int priOperator(char op)
{
	switch (op)
	{
	case '^': return 4;
	case '*': return 3;
	case '/': return 3;
	case '%': return 3;
	case '+': return 2;
	case '-': return 2;
	case '(': return 1;
	}
	return -1;// ���н�
}

/*�������� �켱������ �����ִ� �Լ�*/
int comOperator(char op1, char op2)
{
	int numop1 = priOperator(op1);
	int numop2 = priOperator(op2);

	if (numop1 > numop2)
	{
		return 1;
	}
	else if (numop1 < numop2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/*���Ⱑ �Էµ� ������ ���Ӱ� �ϳ��� �迭�� �ִ� �۾��� ���ִ� �Լ�*/
void newArray(char str[])
{
	int i, idx = 0;

	for (i = 0; str[i] != 0; i++)
	{
		/*spaceŰ�� tabŰ�� ����*/
		if (str[i] != ' ' && str[i] != '	')
		{
			str[idx++] = str[i];
		}
	}
	str[idx] = 0;//������ ������
}


/*������ �����ϴ� �Լ�*/
/*��ȯ �� - ������ ����Ǿ� ���� �Լ�*/
int calc(int num1, int num2, char c)
{
	int result = 0;
	switch (c)
	{
	case '+':
		result = num2 + num1;
		break;
	case '-':
		result = num2 - num1;
		break;
	case '*':
		result = num2 * num1;
		break;
	case '/':
		result = num2 / num1;
		break;
	case '%':
		result = num2 % num1;
		break;
	case '^':
		result = (int)pow(num2, num1);
		break;
	}
	return result;
}

/*���� ǥ����� ���� ǥ������� ��ȯ, ���� ǥ����� �̿��Ͽ� �����ϴ� �Լ�*/
void convAndCalc(char str[])
{
	/*���� ���ð� ���� ������ ����*/
	Stack stack;
	IStack istack;

	/*�� ��Ȳ�� ���� �κ��� ǥ���� �ֱ� ���� ���� ����*/
	int minCount = 1;
	int stackNum = 0;
	int numCount = 1;
	int minCheck = 0;

	/*������ �Ǵ��ϱ� ���� ���� ����*/
	int bacCount1 = 0;
	int bacCount2 = 0;
	int opCount = 1;
	int isOperator = 0;

	/*���꿡 �ʿ��� ������ ���� ���� ����*/
	int popData1, popData2, result;

	/*������ ����*/
	createStack(&stack, 100);
	createIStack(&istack, 100);
	newArray(str);
	int len = strlen(str);
	char *convStr = calloc(len + 100, sizeof(char));

	int i, j, idx = 0;
	char tok, popchar;

	memset(convStr, 0, sizeof(char)*len + 1);


	for (i = 0; i < len; i++)
	{
		tok = str[i];

		/*�����κ��� ó��*/
		if (isdigit(tok))
		{

			if (minCount == 0)
			{
				convStr[idx++] = ' ';
				minCount++;
			}
			convStr[idx] = tok;

			//���ÿ� ������ �ִ� �۾�
			if (!isdigit(str[i + 1]))
			{
				/*�ش� ������ ������� �������� �Ǵ�*/
				if (minCheck == 0)
				{
					for (j = i - (numCount - 1); j <= i; j++)
					{
						stackNum += (str[j] - 48) * ((int)pow(10, --numCount));
					}
					opCount--;
					ipush(&istack, stackNum);
					stackNum = 0;
				}
				else if (minCheck == 1)
				{
					for (j = i - (numCount - 1); j <= i; j++)
					{
						stackNum += (str[j] - 48) * ((int)pow(10, --numCount));
					}
					stackNum = -1 * stackNum;
					ipush(&istack, stackNum);
					opCount--;
					stackNum = 0;
					minCheck--;
				}
			}
			idx++;
			numCount++;
		}
		/*���� �κ��� ó��*/
		else
		{
			minCount = 0;
			numCount = 1;
			/*�������� �������� ����� �ٸ��� ����*/
			switch (tok)
			{
			case '(':
				push(&stack, tok);
				bacCount1++;
				break;
			case ')':
				while (1)
				{
					pop(&stack, &popchar);
					if (popchar == '(')
						break;
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*������ ����*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				bacCount2++;
				break;
			case '+':
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*������ ����*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '*':
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*������ ����*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '/':
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*������ ����*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '%':
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*������ ����*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '^':
				/*���� �κ��� ���������� ������ �״�� ���ÿ� ����*/
				if (comOperator(peek(&stack), tok) == 0)
				{
					push(&stack, tok);
					opCount++;
				}
				/*���� ���� ��찡 �ƴ� ��� �ٸ� �����ڿ� �����ϰ� ó��*/
				else
				{
					while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
					{
						pop(&stack, &popchar);
						convStr[idx++] = ' ';
						convStr[idx] = popchar;
						/*������ ����*/
						ipop(&istack, &popData1);
						ipop(&istack, &popData2);
						result = calc(popData1, popData2, convStr[idx]);
						ipush(&istack, result);
						idx++;
					}
					opCount++;
					push(&stack, tok);
				}
				break;
				/*���� �κ��� ���� ������ ǥ���ϴ� ������ �������� ������ ����*/
			case '-':
				/*�� �տ� ���� �ִ� ���� ��ȣ�� ������ ���� ��ȣ�̴�*/
				if (i == 0)
				{
					minCount = 1;
					convStr[idx] = '-';
					idx++;
					minCheck++;
				}
				/*���� ��ȣ ���� ����*/
				else if (!isdigit(str[i - 1]))
				{
					/*')'���� ������ ������ ���� ��ȣ�� ���� �������� ��Ȱ�̴�.*/
					if (str[i - 1] == ')')
					{
						while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
						{
							pop(&stack, &popchar);
							convStr[idx++] = ' ';
							convStr[idx] = popchar;
							/*������ ����*/
							ipop(&istack, &popData1);
							ipop(&istack, &popData2);
							result = calc(popData1, popData2, convStr[idx]);
							ipush(&istack, result);
							idx++;
						}
						push(&stack, tok);
						opCount++;
					}
					/*������ ���� �ڿ� ������ ���� ��ȣ�� ���� ���ڸ� ��Ÿ���� ���̴�.*/
					else
					{
						minCount = 1;
						convStr[idx] = '-';
						idx++;
						minCheck++;
					}
				}
				/*�� �̿��� ���� ���� �������� ��Ȱ�̴�.*/
				else
				{
					while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
					{
						pop(&stack, &popchar);
						convStr[idx++] = ' ';
						convStr[idx] = popchar;
						/*������ ����*/
						ipop(&istack, &popData1);
						ipop(&istack, &popData2);
						result = calc(popData1, popData2, convStr[idx]);
						ipush(&istack, result);
						idx++;
					}
					push(&stack, tok);
					opCount++;
				}
				break;
				/*������ ���� ��ȣ �̿��� ���ڰ� �ִ��� Ȯ�����ֱ� ���� �۾�*/
			case '\n':
				break;
			default:
				isOperator++;
				break;

			}
		}
	}

	while (!isStackEmpty(&stack))
	{
		pop(&stack, &popchar);
		convStr[idx++] = ' ';
		convStr[idx] = popchar;
		/*������ ����*/
		ipop(&istack, &popData1);
		ipop(&istack, &popData2);
		result = calc(popData1, popData2, convStr[idx]);
		ipush(&istack, result);
		idx++;
	}

	if (bacCount1 == bacCount2 && opCount == 0 && isOperator == 0)
	{
		printf("#���� ǥ���->");
		convStr[idx] = 0;
		printf("%s", convStr);
		printf("\n");
		ipop(&istack, &result);
		printf("����� -> %d\n", result);
		strcpy(str, convStr);
		printf("\n");
	}
	else
	{
		printf("ERROR\n");
	}


	free(convStr);
}