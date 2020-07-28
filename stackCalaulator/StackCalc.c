#include "StackCalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*문자 스택 메모리의 할당*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*문자 스택이 꽉 차있는지 검사*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*문자 스택이 비어있는지 검사*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*문자 스택에 데이터를 하나 저장함*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*문자 스택에서 데이터를 꺼냄*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*문자 스택에서 맨 위의 데이터를 봄*/
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


/*정수 스택 메모리의 할당*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*정수 스택이 꽉 차있는지 검사*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*정수 스택이 비어있는지 검사*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*정수 스택에 데이터를 하나 저장함*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*정수 스택에서 데이터를 꺼냄*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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





/*연산자의 우선순위를 정해주는 함수*/
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
	return -1;// 실패시
}

/*연산자의 우선순위를 비교해주는 함수*/
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

/*띄어쓰기가 입력된 수식을 새롭게 하나의 배열에 넣는 작업을 해주는 함수*/
void newArray(char str[])
{
	int i, idx = 0;

	for (i = 0; str[i] != 0; i++)
	{
		/*space와tab키를 제거*/
		if (str[i] != ' ' && str[i] !='	')
		{
			str[idx++] = str[i];
		}
	}
	str[idx] = 0;//문장의 종지부
}


/*연산을 수행하는 함수*/
/*반환 값 - 연산이 수행되어 나온 함수*/
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

/*중위 표기식을 후위 표기식으로 변환, 후위 표기식을 이용하여 연산하는 함수*/
void convAndCalc(char str[])
{
	/*문자 스택과 정수 스택의 선언*/
	Stack stack;
	IStack istack;

	/*각 상황에 따른 부분을 표시해 주기 위한 정수 선언*/
	int minCount = 1;
	int stackNum = 0;
	int numCount = 1;
	int minCheck = 0;

	/*에러를 판단하기 위한 정수 선언*/
	int bacCount1 = 0;
	int bacCount2 = 0;
	int opCount = 1;
	int isOperator = 0;

	/*연산에 필요한 정수를 담을 변수 선언*/
	int popData1, popData2, result;

	/*스택의 생성*/
	createStack(&stack,100);
	createIStack(&istack,100);
	newArray(str);
	int len = strlen(str);
	char *convStr = calloc(len + 100, sizeof(char));

	int i,j,idx = 0;
	char tok, popchar;

	memset(convStr, 0, sizeof(char)*len + 1);


	for (i = 0; i < len; i++)
	{
		tok = str[i];

		/*정수부분의 처리*/
		if (isdigit(tok))
		{

			if (minCount == 0)
			{
				convStr[idx++] = ' ';
				minCount++;
			}
			convStr[idx] = tok;

			//스택에 정수를 넣는 작업
			if (!isdigit(str[i + 1]))
			{
				/*해당 정수가 양수인지 음수인지 판단*/
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
		/*문자 부분의 처리*/
		else
		{   
			minCount = 0;
			numCount = 1;
			/*연산자의 종류마다 기능을 다르게 수행*/
			switch (tok)
			{
			case '(' :
				//sCheck = push(&stack, tok);
				if (sCheck == 0)
				{
					//stackCheck++;
				}
				bacCount1++;
				break;
			case ')' :
				while (1)
				{
					pop(&stack, &popchar);
					if (popchar == '(')
						break;
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*연산의 수행*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2,convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				bacCount2++;
				break;
			case '+' :
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*연산의 수행*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '*' :
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*연산의 수행*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '/' :
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*연산의 수행*/
					ipop(&istack, &popData1);
					ipop(&istack, &popData2);
					result = calc(popData1, popData2, convStr[idx]);
					ipush(&istack, result);
					idx++;
				}
				push(&stack, tok);
				opCount++;
				break;
			case '%' :
				while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
				{
					pop(&stack, &popchar);
					convStr[idx++] = ' ';
					convStr[idx] = popchar;
					/*연산의 수행*/
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
				/*지수 부분은 연속적으로 나오면 그대로 스택에 저장*/
				if (comOperator(peek(&stack), tok) == 0)
				{
					push(&stack, tok);
					opCount++;
				}
				/*위와 같은 경우가 아닐 경우 다른 연산자와 동일하게 처리*/
				else
				{
					while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
					{
						pop(&stack, &popchar);
						convStr[idx++] = ' ';
						convStr[idx] = popchar;
						/*연산의 수행*/
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
			/*음수 부분은 음의 정수를 표현하는 것인지 연산자인 것인지 구분*/
			case '-' : 
				/*맨 앞에 나와 있는 음의 부호는 정수의 음의 부호이다*/
				if (i == 0)
				{
					minCount = 1;
					convStr[idx] = '-';
					idx++;
					minCheck++;
				}
				/*음의 부호 앞이 문자*/
				else if (!isdigit(str[i - 1]))
				{
					/*')'문자 다음에 나오는 음의 부호는 빼기 연산자의 역활이다.*/
					if (str[i - 1] == ')')
					{
						while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
						{
							pop(&stack, &popchar);
							convStr[idx++] = ' ';
							convStr[idx] = popchar;
							/*연산의 수행*/
							ipop(&istack, &popData1);
							ipop(&istack, &popData2);
							result = calc(popData1, popData2, convStr[idx]);
							ipush(&istack, result);
							idx++;
						}
						push(&stack, tok);
					}
					/*나머지 문자 뒤에 나오는 음의 부호는 음의 숫자를 나타내는 것이다.*/
					else
					{
						minCount = 1;
						convStr[idx] = '-';
						idx++;
						minCheck++;
					}
				}
				/*그 이외의 것은 빼기 연산자의 역활이다.*/
				else
				{
					while (!isStackEmpty(&stack) && comOperator(peek(&stack), tok) >= 0)
					{
						pop(&stack, &popchar);
						convStr[idx++] = ' ';
						convStr[idx] = popchar;
						/*연산의 수행*/
						ipop(&istack, &popData1);
						ipop(&istack, &popData2);
						result = calc(popData1, popData2, convStr[idx]);
						ipush(&istack, result);
						idx++;
					}
					push(&stack, tok);
				}
				opCount++;
				break;
			/*지정된 수식 기호 이외의 문자가 있는지 확인해주기 위한 작업*/
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
		/*연산의 수행*/
		ipop(&istack, &popData1);
		ipop(&istack, &popData2);
		result = calc(popData1, popData2, convStr[idx]);
		ipush(&istack, result);
		idx++;
	}
	
	if (bacCount1 == bacCount2 && opCount == 0 && isOperator == 0)
	{
		printf("#후위 표기식->");
		convStr[idx] = 0;
		printf("%s", convStr);
		printf("\n");
		ipop(&istack, &result);
		printf("결과값 -> %d\n", result);
		strcpy(str, convStr);
		printf("\n");
	}
	else
	{
		printf("ERROR\n");
	}
	
	
	free(convStr);
}



