#include <stdio.h>
#include <string.h>
#include "StackCalc.h"


int main()
{
	char exit[] = "q\n";//fgets함수는 개행 문자 \n 도 읽으므로 지정.
	printf("\n*************계산기 프로그램 입니다*************\n");
	printf("\n@q를 입력 받으면 종료됩니다.\n");
	printf("\n@에러의 발생 조건은 다음과 같습니다.\n");
	printf("\n1, 짝이 맞지 않는 괄호일 경우\n");
	printf("\n2, '+' '-' '*' '/' '%' '^' '(' ')' 이외의 기호를 사용하는 경우\n");
	printf("\n3,연산자를 연속되게 사용한 경우\n");
	printf("\n4,수식에 문자를 사용한 경우\n");
	printf("\n*************계산기 프로그램을 시작합니다*************\n");
	while (1)
	{
		char str[100];
		printf("\n수식을 입력해 주세요->");
		fgets(str, 100, stdin);//공백 문자도 입력 받기 위해 fget함수 사용
		if (!strcmp(str,exit))
		{
			printf("\n*************계산기 프로그램을 종료합니다*************\n");
			break;
		}
		
		convAndCalc(str);
		printf("\n**********************************************************************\n");
	}
}
