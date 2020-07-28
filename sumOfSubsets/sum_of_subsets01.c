#include <stdio.h>

int promising(int i, int weight, int total);		//유망한 노드를 판별하기 위한 함수
void sum_of_subsets(int i, int weight, int total);		//부분집합의 합 구하는 알고리즘의 구현

 /*문제 13을 위한 변수의 값을 설정*/
int w[7] = { 0,2,10,13,17,22,42 };		//무게의 종류
int W = 52;		// 합이 되는 무게
int n = 6;		//무게의 갯수
int include[7] = { 0, }; // w[i]를 포함하는지 안하는지의 유무
int total = 0; // 남은 아이템의 총 무게를 저장하는 변수
int weight = 0;		// 수준 i의 마디까지의 포함된 무게의 합


int main()
{
	int i;

	/*처음 total의 초기값은 모든 무게의 합과 같다*/
	for (i = 1; i < 7; i++)
	{
		total += w[i];
	}

	printf("\n******************부분집합의 합 구하기 알고리즘을 수행합니다.******************\n\n");
	printf("******************문제 14에 대한 결과입니다******************\n\n");
	printf("진행 절차와 답을 같이 출력합니다\n\n");
	sum_of_subsets(0, weight, total);
	printf("\n");
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

/*부분집합의 합 구하는 알고리즘의 구현*/
void sum_of_subsets(int i, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) //유망하면 다음 작업을 수행
	{
		printf("트리수준 : %d, weight : %d, total : %d\n", i, weight, total);
		if (weight == W)	//구하고자 하는 무게를 채우면 출력을 수행
		{
			printf("\nW를 만족하는 조합은 다음과 같습니다 ->");
			for (j = 1; j <= 6; j++)
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
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;		//w[i+1]을 포함하지 않는 경우
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}

