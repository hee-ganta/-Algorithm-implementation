#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 100
int minmult(int n, int d[], int P[][MAX]);   //연쇄 행렬 곱셉에서 최소 곱셈 수를 구하는 함수
void order(int i, int j);     //행렬의 최적의 곱셈 식을 출력해주는 함수
int minimum(int i, int j, int k, int M[][MAX], int d[]);   //최소값을 반환해주는 함수

int P[MAX][MAX] = { 0, }; //행렬P의 선언 및 초기화
int d[MAX] = { 0, }; //연쇄 행렬 곱셈에서의 행렬들의 열과 행의 개수의 데이터를 담을 배열의 선언


int main()
{
	int num = 0;
	int num2 = 0;
	int i;
	printf("*******연쇄 행렬 곱셈 알고리즘을 시작합니다********\n");
	printf("행렬의 개수를 입력해 주세요: ");     //몇개의 행렬을 곱 할 것인지 저장해 줌
	scanf("%d", &num);
	printf("행렬의 행과 열에 대한 정보를 입력해 주세요(%d 개의 숫자를 입력하세요): ",num+1);
	for (i = 0; i <= num; i++)
	{
		scanf("%d", &d[i]);
	}
	num2 =minmult(num, d, P);                            //행렬의 최적의 곱셈 식을 구하기 위한 행렬M과 행렬P를 구하는 함수
	printf("\n------------------------------------------------\n");
	printf("연쇄행렬 곱셈의 최적 곱셈에 대한 식입니다 -> ");
	order(1, num);              //연쇄행렬의 최적 곱셈 식을 출력하는 함수
	printf("\n최소 곱셈의 수는 다음과 같습니다->%d\n", num2);
	printf("\n");
	return 0;
}

/*최소값을 반환해주는 함수의 구현(연쇄행렬 곱셈 알고리즘에 사용)*/
/*반환하는 값은 최소가 될 때의 k 값을 반환한다.*/
int minimum(int i, int j, int k, int M[][MAX],int d[])
{
	/*현재 행렬안에 쓰레기 값으로 되어 있음으로 첫번째 비교 대상은 행렬에 넣어준다.*/
	if (k == i)
	{
		/*k를 중심으로 두 행렬을 곱하였을때의 곱셈의 수를 구하는 재귀관계식이다.*/
		M[i][j] = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
		/*이때의 k값을 반환*/
		return k;
	}

	if (k != i)
	{
		/*만일 새로운 k를 중심으로 쪼개어 연산을 실행 하였을때 그 값이 더 작으면 최적의 값을 갱신하여 준다.*/
		if (M[i][j] > M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j])
		{
			/*k를 중심으로 두 행렬을 곱하였을때의 곱셈의 수를 구하는 재귀관계식이다.*/
			M[i][j] = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
			/*이때k 값을 반환 */
			return k;
		}
	}
	return P[i][j];
}

/*연쇄 행렬 곱셉에서 최소 곱셈 수를 구하는 함수*/
 /*이때 반환값은 행렬1에서 행렬n까지 곱하는데 최소 곱셈 수이다.*/
int minmult(int n, int d[], int P[][MAX])
{
	int i, j, k, diagonal,knum;
	/*행렬의 최소 곱셈을 담기 위한 배열의 선언*/
	int M[MAX][MAX] = { 0, };
	/*배열의 초기화*/
	for (i = 0; i <= n; i++)
	{
		M[i][i] = 0;
	}

	/*연쇄 행렬 곱의 최적의 곱셈 수를 구하는 알고리즘*/
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;
			for (k = i; k <= j - 1; k++)
			{
				knum = minimum(i, j, k, M,d);   //최소값을 찾아줌
				P[i][j] = knum;           //행렬P에다가 갱신되면 k값 그렇지 않으면 값을 유지하여 넣어줌
			}
		}
	}

    /*행렬M의 출력*/
	printf("\n연쇄 행렬곱셈 알고리즘 행렬M 구하기\n");

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			printf("%5d", M[i][j]);
		}
		printf("\n");
	}
	printf("\n------------------------------------------------\n");
	printf("\n");
	/*행렬P의 출력*/
	printf("연쇄 행렬곱셈 알고리즘 행렬P 구하기\n");
	
	for (i = 1; i < n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			printf("%3d", P[i][j]);
		}
		printf("\n");
	}
	return M[1][n];
}

/*연쇄행렬의 최적의 곱셈 식을 출력해주는 함수*/
void order(int i, int j)
{
	int k;
	if (i == j)
	{
		printf("A%d", i);
	}
	else
	{
		k = P[i][j];
		printf("(");      //나눠줄 부분이 있으면 괄호를 열어 나눠준다.
		order(i, k);
		order(k + 1, j);
		printf(")");     //더이상 나눠줄 부분이 없으면 괄호로 닫는다.
	}
}



