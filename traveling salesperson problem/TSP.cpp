#include <stdio.h>
#define  INF 100
#define MAX 100

void travel(int n, int W[][6], int P[][MAX], int* minlength); // 외판원 알고리즘을 구현하는 함수
int ver_to_bin(int a);		//행렬D를 재울때 해당 꼭지점에 대한 이진수 표기법으로 바꿔주기 위한 함수
int bin(int a);			//정수를 넣고 1을 빼 주워 해당 정수 자리수로 만들수 있는 최대값을 구하기 위한 함수
void print_path(int P[][MAX], int a, int b, int* n);	 //경로를 출력해 주기 위한 함수
int city_count(int l, int n, int check[]);			//몇개의 꼭지점을 거치는지 확인하는 작업


int main()
{
	int W[6][6] = { {0,0,0,0,0,0},{0,0,8,13,18,20},{0,3,0,7,8,10},{0,4,11,0,10,7},{0,6,6,7,0,11},{0,10,6,2,1,0} };
	int P[6][MAX] = { 0, }; // 경로에 대한 정보를 담기 위한 배열 선언
	int minlength = 0;		//최단 경로 길이를 담기 위한 변수의 선언
	int i, j;
	int totn = bin(5) - 2;

	/*꼭지점의 연결 상태를 출력*/
	printf("꼭지점의 연결 상태를 출력합니다\n");
	for (i = 1; i < 6; i++)
	{
		for (j = 1; j < 6; j++)
		{
			printf("%1d ", W[i][j]);
		}
		printf("\n\n");
	}
	travel(5, W, P, &minlength);

	printf("\n최단 경로의 길이는 %d 입니다.\n\n", minlength);

	/*시작점과 종점은 v1 지점이고 나머지의 최단 경로는 print_path함수를 이용하여 출력*/
	printf("최단 경로는 다음과 같습니다.\n");
	printf("v1->");
	print_path(P, 1, bin(5) - 2, &totn);
	printf("v1\n");
	return 0;
}


/*행렬D를 재울때 해당 꼭지점에 대한 이진수 표기법으로 바꿔주기 위한 함수*/
int ver_to_bin(int a)
{
	int result = 1;
	int i;
	for (i = 0; i < a - 1; i++)
	{
		result = result * 2;
	}
	return result;
}

/*정수를 넣고 1을 빼 주워 해당 정수 자리수로 만들수 있는 최대값을 구하기 위한 함수*/
int bin(int a)
{
	int result = 1;
	int i;
	for (i = 0; i < a; i++)
	{
		result = result * 2;
	}
	return result;
}


/*몇개의 꼭지점을 거치는지 확인하는 작업(비트마스킹 방법을 이용)*/
int city_count(int l, int n, int check[])
{
	int count = 0;		//열이 몇개의 꼭지점을 거치는지 저장하기 위한 변수
	int j;


	for (j = 0; j < n; j++)
	{
		if (j == 0)		//첫번째 꼭지점은 카운트 하지 않는다
		{
			if (l % 2 == 1)
			{
				check[j + 1] = 1;
			}
		}
		else		//두번째 꼭지점부터는 카운트를 해준다
		{
			if (l % 2 == 1)
			{
				count++;
				check[j + 1] = 1;
			}
		}
		l = l >> 1;  //shiftright 작업 수행
	}

	return count;

}

/*외판원 알고리즘의 구현
 (입력)
  n -> 꼭지점의 개수
  W -> 꼭지점의 연결상태
  P -> 최소가 되는 도시의 저장
  minlength -> 최소 연결 수치
  */

void travel(int n, int W[][6], int P[][MAX], int* minlength)
{
	int i, j, k, l;
	int D[6][MAX];
	int count = 0;
	int check[MAX] = { 0, }; // 현재 어느 도시를 지나치는 경우를 고려하는지 저장하는 배열 (1이면 지나치는 경우, 0 이면 안 지나치는 경우)

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			D[i][j] = INF;
		}
	}


	/*한 꼭지점에서 바로 목적지까지 가는 경우*/
	for (i = 2; i <= 5; i++)
	{
		D[i][0] = W[i][1];
	}

	/*Traveling Sales Preson 알고리즘 구현*/
	/*꼭지점1을 제외한 나머지 꼭지점들을 시작점과 거쳐가는 지점으로 마지막으로 꼭지점1로 가는 경우를 행렬D에 저장하는 알고리즘*/
	for (k = 1; k <= n - 2; k++) // 거쳐가는 꼭지점의 개수는 n-2개가 최대이다.
	{
		for (l = 1; l <= bin(n) - 1; l++)  //열에 대한 모든 경우의 수를 고려
		{
			count = city_count(l, n, check); //해당 열에 대한 꼭지점의 수를 구함 

			if (count == k)		//탐방하고자하는 꼭지점의 수가 일치하면 계산을 진행
			{
				for (i = 2; i <= n; i++)	//꼭지점1 다음의 출발지의 설정
				{
					for (j = 2; j <= n; j++)
					{
						if ((check[1] != 1) && (check[i] != 1) && (check[j] == 1) && (D[i][l] > W[i][j] + D[j][l - ver_to_bin(j)]))
						{
							D[i][l] = W[i][j] + D[j][l - ver_to_bin(j)];	//최소값이 나올 때마다 값을 생신하여 배열에 저장
							P[i][l] = j;		//이때의 경로를 배열에 저장 			
						}
					}
				}
			}

			/*체크 배열의 상태를 초기화 시켜준다*/
			for (i = 0; i <= n; i++)
			{
				check[i] = 0;
			}

		}
	}

	/*시작점을 꼭지점1로 하여 순회하는 경우를 저장*/
	for (j = 2; j <= n; j++)
	{
		if (D[1][bin(n) - 2] > W[1][j] + D[j][(bin(n) - 2) - ver_to_bin(j)])
		{
			D[1][bin(n) - 2] = W[1][j] + D[j][(bin(n) - 2) - ver_to_bin(j)];	//최소값이 나올 때마다 값을 생신하여 배열에 저장 
			P[1][bin(n) - 2] = j;		//이때의 경로를 배열에 저장
			*minlength = D[1][bin(n) - 2];  //최소 경로의 길이를 배열에 저장 
		}
	}


	/*행렬 D의 출력*/
	printf("D행렬을 출력합니다\n\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < bin(n) - 1; j++)
		{
			printf("%3d ", D[i][j]);
		}
		printf("\n");
	}

	/*행렬 P의 출력*/
	printf("\n\nP행렬을 출력합니다\n\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < bin(n) - 1; j++)
		{
			printf("%3d ", P[i][j]);
		}
		printf("\n");
	}
}


/*경로를 출력해 주기 위한 함수*/
void print_path(int P[][MAX], int a, int b, int* n)
{
	if (*n == 0)	//모든 경로를 지나쳤으면 재귀 함수의 탈출
	{
		return;
	}
	else	//재귀 함수를 통하여 경로를 출력 
	{
		printf("v%d->", P[a][b]);
		*n = *n - ver_to_bin(P[a][b]);
		print_path(P, P[a][b], *n, n);
	}
}
