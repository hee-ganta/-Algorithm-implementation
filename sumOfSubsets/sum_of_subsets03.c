#include <stdio.h>
#include <Windows.h>
#include <time.h>


int promising(int i, int weight, int total);		//유망한 것을 판별하기 위한 함수
int estimate_sum_of_subsets(int n);  //몬테칼로 알고리즘울 사용하여 추정값 추정

/*문제 13을 위한 변수의 값을 설정*/
int w[7] = { 0,2,10,13,17,22,42 };		//무게의 종류
int W = 52;		// 합이 되는 무게
int n = 6;		//무게의 갯수
int total = 0; // 남은 아이템의 총 무게를 저장하는 변수
int weight = 0;		// 수준 i의 마디까지의 포함된 무게의 합



int main()
{
	int i;
	int numnodes;//총 계산한 마디의 수
	int total_numnodes = 0;//총 계산한 마디의 수의 평균을 구하기 위한 합계

	/*처음 total의 초기값은 모든 무게의 합과 같다*/
	for (i = 1; i < 7; i++)
	{
		total += w[i];
	}

	printf("******************문제 17에 대한 결과입니다(문제 13번에 대한 경우)******************\n\n");
	for (i = 0; i < 20; i++)
	{

		numnodes = estimate_sum_of_subsets(n);//몬테칼로 추정치 구하기
		printf("%d : 계산한 노드수 -> %d\n",i+1, numnodes);
		weight = 0;		//값을 다시 초기화
		total = 106;
		Sleep(500);
		total_numnodes += numnodes;

	}
	printf("평균 추정치 -> %d\n", (total_numnodes / 20));
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


/*몬테칼로 추정치 구하기*/
int estimate_sum_of_subsets(int n)
{
	int i, j; //i상태공간 트리 수준, j:유망자식을 랜덤으로 고르는 변수 저장
	int m; // 유망한 자식마디의 개수
	int mprod; // 각 수준에서 만들어진 m0*m1....m(i-1)의 표현
	int numnodes; // 가지친 상태공간트리에서 마디의 개수 추정치
	int a[2] = { 0, }; //해당 뿌리에서 노드를 넣을때와 넣지 않을 때를 구분하기 위한 배열의 선언

	
	i = 0;	//뿌리상태의 상태 공간 트리
	numnodes = 1;
	m = 1;
	mprod = 1;

	while (m != 0 && i != n && weight != W)
	{
	
		mprod = mprod * m;// 각 수준에서 만들어진 m0*m1....m(i-1)의 표현을 만들어줌
		numnodes = numnodes + mprod * 2; //검사한 노드수의 갱신
		i++;					 //상태공간트리수준을 한단계 올려줌
		m = 0;

		if (promising(i, weight + w[i], total - w[i])) //해당 뿌리에서 무게를 넣을 때 자식이 유망한지 검사		
		{
			a[0] = 1; //왼쪽 자식의 체크
			m++;
		}

		if (promising(i, weight, total - w[i])) // 해당 뿌리에서 무게를 넣지 않았을때 자식이 유망한지 검사
		{
			a[1] = 1; //오른쪽 자식의 체크
			m++;
		}

		if (m != 0) //자식마디가 존재한다면 어느 것을 선택할지 고르는 작업
		{
			if (a[0] == 1 && a[1] == 1)	//포함하는 경우와 포함하지 않는 경우를 다 만족하는 경우
			{
				srand((unsigned int)time(NULL));
				j = rand() % 2 + 1; //랜덤한 수를 지정				
			}
			else if (a[0] == 1 && a[1] != 1) //포함하는 경우만 만족하는 경우(왼쪽 노드)
			{
				j = 1;
			}
			else if (a[0] != 1 && a[1] == 1) //포함하지 않는 경우만 만족하는 경우(오른쪽 노드)
			{
				j = 2;
			}
		}

		if (j == 1) // 포함하였을 경우
		{
			weight = weight + w[i];
			total = total - w[i];
		}

		if (j == 2)  // 포함하지 않았을 경우
		{
			weight = weight;
			total = total - w[i];
		}

		a[0] = 0; //배열의 상태 초기화 작업
		a[1] = 0;		
	}
	return numnodes;
}
