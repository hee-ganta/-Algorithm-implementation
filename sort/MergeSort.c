#include <stdio.h>
#include <stdlib.h>
void mergesort1(int n, int s[]);
void merge1(int h, int m, int U[], int V[], int S[]);
void mergesort2(int low, int high);
void merge2(int low, int mid, int hight);

//적용하고자 하는 배열을 전역적으로 정의한다
int S1[8] = { 123,34,189,56,150,12,9,240 };
int S2[8] = { 123,34,189,56,150,12,9,240 };

int main()
{
	int i;
	//첫번째 병합 정렬로 배열을 정렬
	printf("병합정렬 과정 1로 배열의 정렬 시작!<배열을 두개를 선언하여 이용>\n");
	printf("--------------------------------\n");
	printf("정렬 전 배열->");
	//정렬하기전 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S1[i]);
	}
	printf("\n");
	mergesort1(8, S1);
	printf("최종으로 정렬한 배열(mergesort1) ->");
	//정돈한 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S1[i]);
	}
	printf("\n--------------------------------\n");
	printf("\n");
	printf("병합정렬 과정 2로 배열의 정렬 시작!<배열을 한개를 선언하여 이용>\n");
	printf("--------------------------------\n");
	printf("정렬 전 배열->");
	//정렬하기전 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S2[i]);
	}
	printf("\n");
	mergesort2(0, 7);
	printf("최종으로 정렬한 배열(mergesort2) ->");
	//정돈한 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S2[i]);
	}
	printf("\n--------------------------------\n");
	return 0;
}

//mergesort의 첫번째 방법
void mergesort1(int n, int S[])
{
	int i, j, k;
	//두개의 배열로 쪼개기 위한 상수의 설정
	int h = n / 2, m = n - h;
	//쪼갠 데이터를 담기 위한 두개의 배열 선언
	int *U, *V;
	//크기 h 만큼의 배열 U의 동적할당, 크기 m 만큼의 배열 V의 동적할당
	U = calloc(h, sizeof(int));
	V = calloc(m, sizeof(int));
	//크기가 1 이상인 배열을 두개의 배열로 쪼개기
	if (n > 1)
	{
		//원래 배열 S의 쪼갠 앞부분을 배열 U에 저장
		for (i = 0; i < h; i++)
		{
			U[i] = S[i];
		}
		//원래 배열 S의 쪼개 뒷부분을 배열 V에 저장
		for (j = 0; j < m; j++)
		{
			V[j] = S[h + j];
		}
		//앞부분을 쪼갠 배열을 길이가 2이상일 때 까지 재귀 함수를 통해 계속해서 분할
		mergesort1(h, U);
		//뒷부분을 쪼갠 배열을 길이가 2이상일 떄 까지 재귀 함수를 통해 계속해서 분할
		mergesort1(m, V);

		//모든 분할한 배열을 병합하는 함수를 호출
		merge1(h, m, U, V, S);
		//정돈한 과정을 보여준다	
		printf("정돈의 과정 ->");
		for (k = 0; k < h + m; k++)
		{
			printf(" %d", S[k]);
		}
		printf("\n");

	}
	//동적할당을 종료
	free(U);
	free(V);
}

//merge의 첫번째 방법
void merge1(int h, int m, int U[], int V[], int S[])
{
	//배열의 인덱스데 대한 변수의 선언
	int i = 0, j = 0, k = 0;
	int l;
	//쪼갠 두 배열에서 서로 왼쪽 부터 비교하여 작은 수를 배열에 넣어줌
	while (i < h && j < m)
	{
		//왼쪽 배열에 있는 데이터가 오른쪽에 있는 데이터 보다 작은 경우
		if (U[i] < V[j])
		{
			S[k] = U[i];
			i++;
		}
		//왼쪽 배열에 있는 데이터가 오른쪽에 있는 데이터 보다 큰 경우
		else
		{
			S[k] = V[j];
			j++;
		}
		//새로 넣어주고 있는 배열의 인덱스를 오른쪽으로 한 칸 이동
		k++;
	}

	//두 배열중 한 배열에 더이상 데이터가 없는 경우 나머지 배열에 있는 데이터를 배열에 넣어줌
	//오른쪽 배열에 데이터가 남아 있는 경우
	if (i >= h)
	{
		for (l = j; l <m; l++)
		{
			S[k + (l - j)] = V[l];
		}
	}
	//왼쪽 배열에 데이터가 남아 있는 경우
	else
	{
		for (l = i; l < h; l++)
		{
			S[k + (l - i)] = U[l];
		}
	}
}

void mergesort2(int low, int high)
{
	int i;
	//중간 지점을 넣을 변수의 선언
	int mid;

	if (low < high)
	{
		mid = (low + high) / 2;//해당 길이를 반으로 나눈 다음 변수에 저장
		mergesort2(low, mid);//왼쪽 부분을 재귀적으로 호출하여 반복
		mergesort2(mid + 1, high);//오른쪽 부분을 재귀적으로 호출하여 반복
		merge2(low, mid, high);//정돈을 한 다음 병합의 작업
	    //정돈하는 과정을 보여줌
		printf("정돈의 과정 ->");
		for (i = low; i <= high; i++)
		{
			printf(" %d", S2[i]);
		}
		printf("\n");
	}
}


void merge2(int low, int mid, int high)
{
	int i, j, k;
	int l;
	//배열을 정돈하여 저장할 배열을 동적 할당으로 선언
	int *U;
	U = calloc(high+1, sizeof(int));

	i = low; j = mid + 1; k = low;

	//반으로 쪼갠 배열중 한 부분이 빌때까지 두 수중 비교하여 작은 수를 배열에 넣어줌
	while (i <= mid && j <= high)
	{
		//왼쪽 부분의 수가 작은 경우
		if (S2[i] < S2[j])
		{
			U[k] = S2[i];//배열에 순차적으로 저장
			i++;
		}
		//오른쪽 부분의 수가 큰 경우
		else
		{
			U[k] = S2[j];//배열에 순차적으로 저장
			j++;
		}
		k++;
	}

	//왼쪽 부분 혹은 오른쪽 부분 중 한 배열이 비면 안 비는 부분의 수를 순차적으로 배열 U에 저장

	//왼쪽 부분이 빌 경우
	if (i > mid)
	{
		for (l = j; l <= high; l++)
		{
			U[k + (l - j)] = S2[l];//배열에 순차적으로 저장
		}
	}
	//오른쪽 부분이 빌 경우
	else
	{
		for (l = i; l <= mid; l++)
		{
			U[k + (l - i)] = S2[l];//배열에 순차적으로 저장
		}
	}

	//배열 U에 있는 데이터를 배열 S2로 옮김
	for (l = low; l <= high; l++)
	{
		S2[l] = U[l];
	}
	//동적할당을 종료
	free(U);
	
}
