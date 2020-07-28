#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // 아이템의 수는 100개로 제한 
int promising(int i, int weight, int profit);
void knapsack(int i, int profit, int weight);//배낭 채우기 문재를 해결하는 알고리즘(Depth_First)
void quicksort(int low, int high, double *S); //무게당 값어치를 내림차순으로 배열
void partition(int low, int high, int *pivotpoint, double *S);

/*필요한 변수들을 전역변수로 지정*/
int W;
int n; //아이템의 개수를 저장 할 변수
int maxprofit = 0;
int numbest = 0;
int w[MAX] = { 0. }; //아이템의 무게를 저장할 배열
int p[MAX] = { 0, }; //아이템의 값어치를 저장할 배열
double pw[MAX] = { 0, }; //아이템의 무게당 값어치를 저장할 배열
int include[MAX] = { 0, };  //1의 값이면 해당 아이템을 넣는다는 뜻이고 0 이면 해당 아이템을 넣지 않는다는 뜻이다.
int bestset[MAX] = { 0, };
int weight = 0;  //가방안의 누적 아이템의 무게(초기에는 들어 있지 않음으로 0)
int profit = 0; //가방안 누적 아이템의 값어치(초기에는 들어 있지 않음으로 0)
int count = 1; // 탐방한 노드의 수를 세주는 변수

int main()
{
	int i;
	printf("아이템의 개수를 입력해 주세요: ");
	scanf("%d", &n);
	printf("채울 수 있는 무게를 입력해 주세요: ");
	scanf("%d", &W);

	printf("아이템들의 속성값을 입력\n");
	for (i = 1; i <= n; i++)
	{
		printf("값어치 무게 : ");
		scanf("%d %d", &p[i], &w[i]);
		pw[i] = (double)p[i] / (double)w[i];
	}

	quicksort(1, n, pw); //값어치를 기준으로 내림차순으로 아이템을 배열

	printf("\n*****************************\n");
	printf("아이템은 다음과 같습니다\n\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d ->p%d : %d, w%d : %d\n", i, i, p[i], i, w[i]);
	}

	printf("\n\n**********************Depth-First 알고리즘을 수행한 결과입니다**********************\n\n");
	knapsack(0, weight, profit);
	printf("넣을 수 있는 최대 값어치는 %d입니다.\n", maxprofit);
	printf("넣은 아이템의 종류는 다음과 같습니다 ->");
	for (i = 1; i <= n; i++)
	{
		if (bestset[i] == 1)
		{
			printf("w%d ", i);
		}
	}
	printf("\n\n");
	printf("탐방한 노드의 수는 %d개 입니다\n\n", count);
	return 0;
}

/*유망한 노드인지 아닌지 판별을 해 주는 함수
유망하면 1을 반환, 유망하지 않으면 0을 반환*/
int promising(int i, int weight, int profit)
{
	int j;
	int totweight;
	double bound;

	if (weight >= W) //만약 가방안의 무게가 채우고자 하는 무게보다 크다면 그 노드는 유망하지 않다
	{
		return 0;
	}
	else
	{
		j = i + 1; //트리의 단계를 하나 올려 준다
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) // 깊이가 n을 초과하거나 가방이 수용 할 수 있는 범위를 초과하면 반복문 종료 
		{
			totweight = totweight + w[j]; //채운 무게를 더함 
			bound = bound + p[j]; //채운 아이템에 대한 값어치를 더함
			j++;
		}
		if (j <= n)
		{
			bound = bound + (W - totweight) * (double)p[j] / (double)w[j]; // 만약 아이템을 다 채우지 않았는데 가방의 무게를 초과했다면
																		   // 무게당 값어치로 마지막 아이템을 부분적으로 채워서 노드의 기대값을 산출
		}
		if (bound > maxprofit) // 이 값어치가 현재 구한 최대 값어치 보다 크면 그 노드는 유망
			return 1;
		else
			return 0;

	}
}

/*배낭채우기 문제를 해결하는 알고리즘*/
void knapsack(int i, int profit, int weight)
{
	int j;
	if (weight <= W && profit > maxprofit) //배낭안의 무게가 채우고자 하는 무게 보다 작고 현재 이윤이 구해놓은 이윤보다 크다면
	{
		maxprofit = profit;
		numbest = i;
		for (j = 1; j <= n; j++)
		{
			bestset[j] = include[j]; //현재 어떤 아이템이 들어 있는 상황인지를 저장
		}
	}

	if (promising(i, weight, profit)) //현재 단계에서 노드가 유망 하다면
	{
		include[i + 1] = 1; //다음번 아이템을 넣었을 때의 경우
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		count++;
		include[i + 1] = 0; //다음번 아이템을 넣지 않았을 때의 경우
		knapsack(i + 1, profit, weight);
		count++;

	}
}

//빠른 정렬의 구현
void quicksort(int low, int high, double *S)
{
	//피봇 정보를 담을 변수의 선언
	int pivotpoint = 0;

	if (high > low)
	{
		//해당 배열에 대하여 맨 앞의 수를 피봇 포인트로 정하고
		//정렬을 다 마친다음
		//피봇이 된 수를 해당 자리에 넣어준다
		partition(low, high, &pivotpoint, S);
		//처음부분에서 피봇의 전 부분까지를 다시 빠른 정렬로 정리 
		quicksort(low, pivotpoint - 1, S);
		//피봇의 다음 부분부터 끝 부분까지 다시 빠른 정렬로 정리
		quicksort(pivotpoint + 1, high, S);
	}
}

void partition(int low, int high, int *pivotpoint, double *S)
{
	int i, j, wtemp, ptemp;
	double pivotitem;
	double temp;

	//피봇을 정돈하고자 하는 배열의 첫 부분으로 설정
	pivotitem = S[low];
	//피봇보다 작은 데이터가 나올 경우 자리를 바꿔주기 위한
	//위치를 담기 위한 변수의 설정
	j = low;
	//피봇으로 부터 다음 데이터부터 배열의 끝 부분 데이터 까지의 정렬의 시작
	for (i = low + 1; i <= high; i++)
	{
		//만약 해당 데이터가 피봇 아이템보다 큰 경우 위치를 앞 부분으로 옮김
		if (S[i] > pivotitem)
		{
			j++;
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;

			wtemp = w[i];
			w[i] = w[j];
			w[j] = wtemp;

			ptemp = p[i];
			p[i] = p[j];
			p[j] = ptemp;


		}
	}
	//정렬을 다 마치고 난 후에 해당 피봇을 피봇보다
	//작은 데이터와 큰 데이터 사이에 위치시킴
	*pivotpoint = j;
	temp = S[low];
	S[low] = S[*pivotpoint];
	S[*pivotpoint] = temp;

	wtemp = w[low];
	w[low] = w[*pivotpoint];
	w[*pivotpoint] = wtemp;

	ptemp = p[low];
	p[low] = p[*pivotpoint];
	p[*pivotpoint] = ptemp;
}