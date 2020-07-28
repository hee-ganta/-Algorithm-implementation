#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int promising(int i, int weight, int total);	//유망한 것을 판별하기 위한 함수(임의의 설정)
void sum_of_subsets02(int i, int n, int weight, int total);	//부분집합의 합 구하는 함수(임의의 설정)
void sum_of_subsets03(int i, int n, int weight, int total); //부분집합의 합 구하는 함수(하나의 해답만 찾기)
void quicksort(int low, int high, int *S);	//퀵정렬 함수
void partition(int low, int high, int *pivotpoint, int *S);

int W;
int n;
int *w;
int *include;
int total = 0; // 남은 아이템의 총 무게를 저장하는 변수
int weight = 0;		// 수준 i의 마디까지의 포함된 무게의 합
int count = 0;


int main()
{
	int i;
	clock_t start, end;

	printf("\n******************부분집합의 합 구하기 알고리즘을 수행합니다.******************\n\n");

	printf("배낭이 저장할 수 있는 최대 무게값을 입력해 주세요:");
	scanf("%d", &W);
	printf("아이템의 개수를 입력해 주세요:");
	scanf("%d", &n);
	w = calloc(n + 1, sizeof(int));
	include = calloc(n + 1, sizeof(int));
	printf("아이템들의 무게를 입력해 주세요:");
	for (i = 1; i < n + 1; i++)
	{
		scanf("%d", &w[i]);
	}
	for (i = 1; i < 7; i++)  // 처음 total의 초기값은 모든 무게의 합과 같다
	{
		total += w[i];
	}
	quicksort(1, n, w); // 입력받은 무게를 오름차순으로 정렬
	printf("오름차순으로 정렬한 아이템의 결과는 다음과 같습니다\n");
	for (i = 1; i < n + 1; i++)
	{
		printf("w%d:%d	", i, w[i]);
	}
	printf("\n\n");
	printf("******************부분집합 알고리즘을 수행한 결과입니다******************\n\n");
	start = clock();
	sum_of_subsets02(0, n, weight, total);
	end = clock();
	printf("걸린 시간은 %d 입니다.\n\n", end - start);
	printf("******************문제 16에 대한 결과입니다(하나의 해답만 추출)******************\n\n");
	start = clock();
	sum_of_subsets03(0, n, weight, total);
	end = clock();
	printf("걸린 시간은 %d 입니다.\n\n", end - start);
	free(w);
	free(include);
	return 0;
}
/*유망한 것을 판별하기 위한 함수
참의 값이면 1을 반환, 거짓의 값이면 0을 반환한다*/
int promising(int i, int weight, int total)
{
	/*조건을 만족하면 유망함을 반환값으로 내어준다
	//현재의 무게와 나머지 무게의 합이 채울 무게의 합보다 크고
	현재 무게가 답과 동일하거나 혹은 현재 무게와 다음 무게의 합이 채우고자 하는 무게 보다 작으면
	유망함을 이용한다.*/
	if ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*부분집합의 합 구하는 함수(임의의 설정)*/
void sum_of_subsets02(int i, int n, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) /*유망하면 다음 작업을 수행*/
	{
		/*구하고자 하는 무게를 채우면 출력을 수행*/
		if (weight == W)
		{
			printf("W를 만족하는 조합은 다음과 같습니다 ->");
			for (j = 1; j <= n; j++)
			{
				if (include[j] == 1)
				{
					printf("w%d ", j);
				}
			}
			printf("\n");
			printf("\n");
		}
		/*그렇지 않으면 다음 무게를 포함할지 안할지를 구분하여 재귀적으로 작업을 수행*/
		else
		{
			include[i + 1] = 1;		//w[i+1]을 포함하는 경우
			sum_of_subsets02(i + 1, n, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;		//w[i+1]을 포함하지 않는 경우
			sum_of_subsets02(i + 1, n, weight, total - w[i + 1]);
		}
	}
}

/*부분집합의 합 구하는 함수(하나의 해답만 찾기)*/
void sum_of_subsets03(int i, int n, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) //유망하면 다음 작업을 수행
	{
		if (weight == W)//구하고자 하는 무게를 채우면 출력을 수행
		{
			count++;
			printf("W를 만족하는 조합은 다음과 같습니다 ->");
			for (j = 1; j <= n; j++)
			{
				if (include[j] == 1)
				{
					printf("w%d ", j);
				}
			}
			printf("\n");
			printf("\n");
		}
		else //그렇지 않으면 다음 무게를 포함할지 안할지를 구분하여 재귀적으로 작업을 수행
		{
			if (count == 0)
			{
				include[i + 1] = 1;		//w[i+1]을 포함하는 경우
				sum_of_subsets03(i + 1, n, weight + w[i + 1], total - w[i + 1]);
				include[i + 1] = 0;		//w[i+1]을 포함하지 않는 경우
				sum_of_subsets03(i + 1, n, weight, total - w[i + 1]);
			}
		}
	}
}

//퀵 정렬의 구현
void quicksort(int low, int high,int *S)
{
	//피봇 정보를 담을 변수의 선언
	int pivotpoint = 0;

	if (high > low)
	{
		//해당 배열에 대하여 맨 앞의 수를 피봇 포인트로 정하고
		//정렬을 다 마친다음
		//피봇이 된 수를 해당 자리에 넣어준다
		partition(low, high, &pivotpoint,S);
		//처음부분에서 피봇의 전 부분까지를 다시 빠른 정렬로 정리 
		quicksort(low, pivotpoint - 1,S);
		//피봇의 다음 부분부터 끝 부분까지 다시 빠른 정렬로 정리
		quicksort(pivotpoint + 1, high,S);
	}
}

void partition(int low, int high, int *pivotpoint, int *S)
{
	int i, j, temp;
	int pivotitem;

	//피봇을 정돈하고자 하는 배열의 첫 부분으로 설정
	pivotitem = S[low];
	//피봇보다 작은 데이터가 나올 경우 자리를 바꿔주기 위한
	//위치를 담기 위한 변수의 설정
	j = low;
	//피봇으로 부터 다음 데이터부터 배열의 끝 부분 데이터 까지의 정렬의 시작
	for (i = low + 1; i <= high; i++)
	{
		//만약 해당 데이터가 피봇 아이템보다 작은 경우 위치를 앞 부분으로 옮김
		if (S[i] < pivotitem)
		{
			j++;
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
	}
	//정렬을 다 마치고 난 후에 해당 피봇을 피봇보다
	//작은 데이터와 큰 데이터 사이에 위치시킴
	*pivotpoint = j;
	temp = S[low];
	S[low] = S[*pivotpoint];
	S[*pivotpoint] = temp;	
}

