#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//무한대값
#define inf 100000
int bin(int n, int k);
int bin2(int n, int k);
int bin3(int n, int k);
void floyd2(int n, int W[][7], int D[][7], int P[][7]);
void print_path(int i, int j, int P[][7]);

//Shorest Path 경로의 정보를 넣을 배열과 인덱스의 선언
int a[7] = { 0, };
int num = 0;

int main()
{
	int n, k;
	int i,j;
	int l;
	clock_t start, end;//걸리는 시간을 측정하기 위한 변수의 선언
	//플로이드 알고리즘에 이용할 이차원 배열의 선언(v1 ~ v7)
	int W[7][7] = { {0,4,inf,inf,inf,10,inf},{3,0,inf,18,inf,inf,inf},{inf,6,0,inf,inf,inf,inf},{inf,5,15,0,2,19,5},{inf,inf,12,1,0,inf,inf},{inf,inf,inf,inf,inf,0,10},{inf,inf,inf,8,inf,inf,0} };//경로의 가중치를 저장할 이차원 배열
	int D[7][7] = {0, };//최단 경로를 저장할 이차원 배열
	int P[7][7] = {0, };//최단경로의 중간지점 가운데 가장 높은 인덱스를 저장
	//플로이드 알고리즘에 이용할 이차원 배열의 선언(a1 ~ a7)
	int cW[7][7] = { {0,inf,inf,8,inf,inf,inf},{10,0,inf,inf,inf,inf,inf},{inf,inf,0,1,12,inf,inf},{5,19,2,0,15,5,inf},{inf,inf,inf,inf,0,6,inf},{inf,inf,inf,18,inf,0,3},{inf,10,inf,inf,inf,4,0} };
	printf("이항계수 구하기를 시작하겠습니다!\n");
	printf("전체 개수를 입력 :");
	scanf("%d", &n);
	printf("꺼낼 개수를 입력:");
	scanf("%d", &k);
	start = clock();
	printf("분할정복법으로 이항계수를 구한 결과값은 %d 입니다\n", bin(n, k));
	end = clock();
	printf("이항계수를 구하는데 걸리는 시간(분할정복법) -> %d\n\n", (int)(end - start));//걸리는 시간의 측정
	start = clock();
	printf("동적계획법으로 이항계수를 구한 결과값은 %d 입니다(이차원 배열을 이용)\n", bin2(n, k));
	end = clock();
	printf("이항계수를 구하는데 걸리는 시간(동적계획법 - 이차원 배열) -> %d\n\n", (int)(end - start));//걸리는 시간의 측정
	start = clock();
	printf("동적계획법으로 이항계수를 구한 결과값은 %d 입니다(일차원 배열을 이용)\n", bin3(n, k));
	end = clock();
	printf("이항계수를 구하는데 걸리는 시간(동적계획법 - 일차원 배열) -> %d\n\n", (int)(end - start));//걸리는 시간의 측정
	printf("v1 ~ v7 까지의 플로이드 알고리즘 작업 시작!\n");
	floyd2(7, W, D, P);
	printf("\na1 ~ a7 까지의 플로이드 알고리즘 작업 시작!\n");
	//Shorest Path 경로의 정보를 넣을 배열과 인덱스를 초기화
	for (l = 0; l < num; l++)
	{
		a[l] = 0;
	}
	num = 0;
	floyd2(7, cW, D, P);
	return 0;

}

/*분할정복법으로 이항계수를 구하는 알고리즘*/
int bin(int n, int k)
{
	/*재귀식의 아이디어는 전체 n개의 숫자 중 k개를 뽑을 때
	두가지의 경우로 나뉠 수 있다
	임의의 숫자 하나를 선택하고
	해당 숫자가 뽑고자 하는 숫자들의 부분에 포함이 될수도 있고 아닌 경우가 있다.
	이를 이용하여 관계식을 만들어 보면 다음과 같다.*/
	// 뽑고자하는 숫자의 개수가 0 이거나 전체 숫자와 같은 경우 이항계수는 1이다.
	if (k == 0 || n == k)
		return 1;
	else
		return bin(n - 1, k - 1) + bin(n - 1, k);

	/*이 방법은 이미 했던 연산을 반복적으로 수행되기 때문에
	효율적이지 못하다.*/
}

/*동적계획법으로 이항계수를 구하는 알고리즘(이차원 배열을 사용)*/
int bin2(int n, int k)
{
	int i, j, l;
	int **B;
	int result = 0;
	/*배열을 만들어 주워서 답을 구하기까지
	숫자를 저장한 다음 답을
	구하고 해당 배열을 지워준다*/

	//동적할당으로 이차원 배열을 만들어줌
	B = calloc(n + 1, sizeof(int));

	for (l = 0; l < n + 1; l++)
	{
		B[l] = calloc(k + 1, sizeof(int));
	}

	/*전체 숫자의 개수(n)는 배열B의 행의 부분이고
	뽑고자 하는 숫자의 개수(k)를 열로 표현해준다*/
	for (i = 0; i <= n; i++)
	{
		/* 행의 부분보다 열의 부분이 큰 경우는 해당 사항이 없음으로
		조건으로 설정
		뽑고자 하는 숫자의 개수보다 큰 부분은
		답을 구할 때 필요하지 않은 부분이므로
		k보다 큰 부분의 열은 필요하지 않아
		조건으로 설정*/
		for (j = 0; j <= i && j <= k; j++)
		{
			if (j == 0 || j == i)// 뽑고자하는 숫자의 개수가 0 이거나 전체 숫자와 같은 경우 이항계수는 1이다.
				B[i][j] = 1;
			else
				B[i][j] = B[i - 1][j - 1] + B[i - 1][j];//윗부분 행을 이용하여 행을 구해준다
		}
	}
	//구하고자 하는 결과값을 저장
	result = B[n][k];

	//동적할당의 종료
	for (i = 0; i < n + 1; i++)
	{
		free(B[i]);
	}
	free(B);
	return result;
}


/*동적계획법으로 이항계수를 구하는 알고리즘(일차원 배열을 사용)*/
int bin3(int n, int k)
{
	int i;
	int  h = 0;//전체 개수의 설정
	int tmp1,tmp2;// 새로운 행을 만들때 연산을 해주기 위해 잠시 숫자를 넣어줄 매개변수
	int *B;//최종 이항계수를 위해서 필요한 데이터를 넣어줄 일차원 배열의 선언
	int result = 0;

	//배열의 동적할당
	B = calloc(k+1, sizeof(int));

	/*h는 전쳬숫자의 개수를 의미한다
	현재 내가 알고 싶은 조건 n에 만족할때 까지 동적계획법 알고리즘을 수행한다.*/
	while (h <= n)
	{
		/*전체숫자의 개수(n)가 뽑고자 하는 수의 개수(k)보다 큰 경우에는
		뽑는수의 개수가 전체수의 개수와 동일 할 때 까지만 구하고
		그 이상은 유효하지 않으므로 구하지 않는다.
		또한 전체 숫자의 개수와 뽑는 숫자의 개수가 같으면
		해당하는 이항 계수는 1이다.*/
		if (h <= k)
		{
			B[0] = 1;//뽑는 숫자의 개수가 0 일 경우에 이항계수는 1이다.

			/*새로운 이항 계수를 구하기 위해 배열을 새로 정돈하는 과정*/
			tmp1 = B[0];
			for (i = 1; i < h; i++)
			{
				tmp2 = B[i];
				B[i] = tmp1 + B[i];
				tmp1 = tmp2;
			}
			B[h] = 1;//h인덱스까지 배열을 정돈한다. 
		}
		/*전체숫자의 개수(h)가 뽑고자 하는 숫자의 개수(k) 보다 큰 경우
		뽑고자 하는 개수까지만의 과정을 정돈한다.
		그 이상으로 데이터를 구해 보아도 결과에는 영향을 미치지 않기 떄문이다.*/
		else if(h > k)
		{
			B[0] = 1;
			tmp1 = B[0];
			/*새로운 이항 계수를 구하기 위해 배열을 새로 정돈하는 과정*/
			for (i = 1; i <= k; i++)//k인덱스까지 배열을 정돈한다.
			{
				tmp2 = B[i];
				B[i] = tmp1 + B[i];
				tmp1 = tmp2;
			}
		}
		h++;
	}
	result = B[k];//결과를 저장
	free(B);//동적할당의 종료
	return result;
}

void floyd2(int n, int W[][7], int D[][7], int P[][7])
{
	int i, j, k;
	int start = 0, end = 0;//최단경로의 시작점과 종점
	clock_t cstart, cend; // 걸리는 시간을 측정하기 위한 변수의 선언

	//지점(i+1)부터(j+1)까지 최단 경로로 지나가는데 거쳐가는 지점
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			P[i][j] = 0;
		}
	}
	//최단 경로의 길이를 담을 배열의 초기화
	D = W;

	cstart = clock();
	//거져가는 지점(k+1)를 1지점부터 차례대로 비교하여 넣어줌
	for (k = 0; k < n; k++)
	{
		//시작점(i+1)를 1지점 부터 차례대로 계산
		for (i = 0; i < n; i++)
		{
			//도착점(j+1)를 1 지점 부터 차례대로 계산
			for (j = 0; j < n; j++)
			{
				/*지점(i+1)에서 지점(j+1)를 갈 때 지점(k+1)을 거쳐서 가는 것이 최단거리인지
				거쳐서 가지 않는 것이 최단거리인지 비교*/
				if (D[i][k] + D[k][j] < D[i][j])
				{
					P[i][j] = k+1;//(i+1)지점에서 (j+1)을 갈 때 지점 (k+1)을 거쳐가는 것이 최단거리 이면 P행렬 인덱스에 저장
					D[i][j] = D[i][k] + D[k][j];//최단거리의 갱신 작업
					printf("\n-------------------------------------------------------------------\n");
					printf("최단 경로의 갱신 -> D[%d][%d] = %d\n",i+1,j+1,D[i][j]);
					printf("거쳐가는 인덱스의 갱신 -> P[%d][%d] = %d\n", i + 1, j + 1, P[i][j]);
				}
			}
		}
	}
	cend = clock();
	//행렬D를 출력
	printf("\nD행렬을 출력합니다!\n");
	printf("   1  2  3  4  5  6  7 \n");
	for (i = 0; i < n; i++)
	{
		printf("%d|",i+1);
		for (j = 0; j < n; j++)
		{
			printf("%3d", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//행렬P를 출력
	printf("P행렬을 출력합니다!\n");
	printf("   1  2  3  4  5  6  7 \n");
	for (i = 0; i < 7; i++)
	{
		printf("%d|", i+1);
		for (j = 0; j < 7; j++)
		{
			printf("%3d", P[i][j]);
		}
		printf("\n");
	}
	printf("\n행렬D와 행렬P를 구하는데 걸리는 시간 -> %d\n", (int)(cend - cstart));

	/*최단 경로를 구하기*/
	printf("\n최단 경로구하기를 시작하겠습니다!\n");
	printf("시작점을 입력하세요:");
	scanf("%d", &start);
	printf("종점을 입력하세요:");
	scanf("%d", &end);
	//printf("최단경로로 갈 때 거치는 인덱스 ->");
	cstart = clock();
	print_path(start, end, P);
	printf("최단경로로 갈 때 거치는 인덱스 ->");
	for (k = 0; k < num; k++)
	{
		printf("%2d ", a[k]);
	}

	printf("\n");
	cend = clock();
	printf("\n");
	printf("shortest path를 구하는데 걸리는 시간 -> %d\n", (int)(cend - cstart));
}

void print_path(int i, int j, int P[][7])
{
	printf("P[%d][%d] 안에 있는 값은 %d 입니다.\n",i,j,P[i-1][j-1]);
	if (P[i-1][j-1] == 0)
	{
		return;
	}
	//행렬	P[i-1][j-1]지점을 기준으로 앞부분과 뒷부분 사이의 최단거리를 거칠때 존재하는 지점을 구해준다
	print_path(i, P[i-1][j-1],P);
	//ShortestPath 경로 데이터 저장
	a[num] = P[i - 1][j - 1];
	num++;
	print_path(P[i-1][j-1], j, P);
}