#include <stdio.h>
#define INF 100
#define NUM 11
void prim1(int n, int W[][NUM], int F[NUM]);
void prim2(int n, int W[][NUM], int F[NUM]);

int main()
{
	int W[NUM][NUM] = { {0,0,0,0,0,0,0,0,0,0,0},
	{0,0,32,INF,17,INF,INF,INF,INF,INF,INF },
	{0,32,0,INF ,INF ,45,INF ,INF ,INF ,INF ,INF },
	{0,INF ,INF ,0,18,INF ,INF ,5,INF ,INF ,INF },
	{0,17,INF ,18,0,10,INF ,INF ,3,INF ,INF },
	{0,INF ,45,INF ,10,0,28,INF ,INF ,25,INF },
	{0,INF ,INF ,INF ,INF ,28,0,INF ,INF ,INF ,6},
	{0,INF ,INF ,5,INF ,INF ,INF ,0,59,INF ,INF },
	{0,INF,INF,INF,3,INF,INF,59,0,4,INF },
	{0,INF ,INF ,INF,INF,25,INF,INF,4,0,12},
	{0,INF,INF ,INF ,INF ,INF ,6,INF ,INF ,12,0}
	}; // 문제에 대한 인접행렬
	int F1[NUM] = { 0, };	//엣지의 집합을 넣을 배열 공간의 선언
	int F2[NUM] = { 0, };   //엣지의 집합을 넣을 배열 공간의 선언
	printf("\n**************prim's 알고리즘을 수행합니다**************\n\n");
	printf("그래프가 연결되지 않은 부부은 무한대 값으로서 임의로 100의 값으로 지정\n\n");
	printf("**************v1부터 알고리즘을 수행합니다.**************\n\n");
	prim1(NUM - 1, W, F1);
	printf("**************v5부터 알고리즘을 수행합니다.**************\n\n");
	prim2(NUM - 1, W, F2);
	return 0;
}


/*prim's Algorithm을 사용하여 MST를 출력하는 함수*/
/*집합Y의 정의는 현재 연결된 정점들의 집합이라고 정의한다*/
/*시작점은 v1이다*/
void prim1(int n, int W[][NUM], int F[NUM])
{
	int i,j;
	int vnear; // Y와 Y의 여집합 사이에서 길이가 가장 짧은 길이를 가지게 되는 Y의 여집합 정점을 저장하는 매개변수
	int min;	//거리의 최소값을 저장할 매개변수
	int nearest[NUM];	//Y에 속한 정점 중에서 임의의 정점에서 가장 가까운 정점을 저장 
	int distance[NUM];	//임의의 정점과 그때의 nearest를 잇는 엣지의 가중치를 저장 
	int count = 1;		//배열F에 인덱스에 접근하기 위한 변수의 선언
	int R[NUM][NUM] = { 0, };		//MST의 정보를 담을 배열의 선언
	int check[NUM] = { 0, }; // 정점의 연결상태를 담는 배열(연결이 되어 있지 않으면0, 연결이 되어 있으면 1을 저장)
	int sum = 0; //엣지 가중치의 합을 저장하는 변수

	/*MST정보를 담을 배열의 초기화 작업*/
	for (i = 1; i <= NUM - 1; i++)
	{
		for (j = 1; j <= NUM-1; j++)
		{
			R[i][j] = INF;
		}
	}

	/*MST정보를 담을 배열의 초기화 작업*/
	for (i = 1; i <= NUM - 1; i++)
	{
		R[i][i] = 0;
	}

	/*해당 엣지의 정보를 담을 배열의 초기화*/
	for (i = 0; i <= n; i++)
	{
		F[i] = 0;
	}
	
	/*모든 해당 마디에 집합Y에 대하여 초기화를 해 준다.(이때, 시작점은 v1이다.)*/
	/*Y로 부터의 거리를 초기화를 해준다.(시작점이 v1임으로 distance[i] 는 vi와 v1사이의 거리이다.)*/
	check[1] = 1;
	for (i = 2; i <= n; i++)
	{
		nearest[i] = 1;	
		distance[i] = W[1][i];		
	}
	

	printf("정점들이 연결지어지는 과정을 출력합니다.(v1부터 시작)\n");
	/*도시의 개수가 n개 이면 엣지는 최소 n-1개가 있으면 모든 정점들이 연결이 될 수 있다.*/
	for (j = 1; j <= n - 1; j++)
	{
		min = INF;

		/*각각의 정점들에 대하여 가장 짧은 엣지의 길이를 min에다가 저장을 하고 그때 해당하는 Y여집합에 포함되는 
		정점을 vnear에다가 저장을 해 준다.*/
		for (i = 2; i <= n; i++)
		{
			if (0 <= distance[i] && distance[i] < min)
			{
				min = distance[i];
				vnear = i;
			}
		}
		/*정점이 선택되었는지 상태를 저장과 출력을 해 주는 함수*/
		/*check 배열의 값은0 이면 연결이 안 된 상태이고 1이면 연결이 되어있는 상태이다*/
		printf("%d번 과정 후 ->",j);
		check[vnear] = 1;
		for (i = 1; i <= n; i++)
		{
			printf("%d ",check[i]);
		}
		printf("\n");
		//MST에다가 해당 정보를 저장
		R[nearest[vnear]][vnear] = min;
		R[vnear][nearest[vnear]] = min;
		sum += min;

		//엣지의 정보를 행렬F에 저장
		F[count] = min;
		count++;

		distance[vnear] = -1; // vnear에 해당하는 정점은 이제 연결이 되어 있음으로 엣지를 고려를 해 주지 않기 위하여 -1로 저장

		//새로 들어온 노드vnear에 대하여 거리에 대한 정보의 갱신
		for (i = 2; i <= n; i++)
		{
			if (W[i][vnear] < distance[i])
			{
				distance[i] = W[i][vnear];
				nearest[i] = vnear;
			}
		}
	}


	printf("\n뽑힌 엣지의 순서는 다음과 같습니다 ->");
	for (j = 1; j <= n - 1; j++)
	{
		printf("%d ", F[j]);
	}
	printf("\n");
	printf("\n");

	printf("최소 비용 신장 트리에서의 엣지의 합 -> %d\n", sum);


	printf("\nprim's Algorithm을 사용하여 MST를 출력합니다(V1부터 시작, 인접행렬로 표현)\n");
	for (i = 1; i <= NUM - 1; i++)
	{
		for (j = 1; j <= NUM - 1; j++)
		{
			printf("%3d ", R[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*prim's Algorithm을 사용하여 MST를 출력하는 함수*/
/*집합Y의 정의는 현재 연결죈 노드들의 집합이라고 정의한다*/
/*시작점은 v5이다*/
void prim2(int n, int W[][NUM], int F[NUM])
{
	int i, j;
	int vnear; // Y와 Y의 여집합 사이에서 길이가 가장 짧은 길이를 가지게 되는 Y의 여집합 정점을 저장하는 매개변수
	int min;	//거리의 최소값을 저장할 매개변수
	int nearest[NUM];	//Y에 속한 정점 중에서 임의의 정점에서 가장 가까운 정점을 저장 
	int distance[NUM];	//임의의 정점과 그때의 nearest를 잇는 엣지의 가중치를 저장 
	int count = 1;	//배열F에 인덱스에 접근하기 위한 변수의 선언 
	int R[NUM][NUM] = { 0, };	//MST의 정보를 담을 배열의 선언
	int check[NUM] = { 0, }; // 정점의 연결상태를 담는 배열(연결이 되어 있지 않으면0, 연결이 되어 있으면 1을 저장)
	int sum = 0; //엣지의 합을 저장하는 변수

	/*MST정보를 담을 배열의 초기화 작업*/
	for (i = 1; i <= NUM - 1; i++)
	{
		for (j = 1; j <= NUM - 1; j++)
		{
			R[i][j] = INF;
		}
	}

	/*MST정보를 담을 배열의 초기화 작업*/
	for (i = 1; i <= NUM - 1; i++)
	{
		R[i][i] = 0;
	}

	/*해당 엣지의 정보를 담을 배열의 초기화*/
	for (i = 0; i <= n; i++)
	{
		F[i] = 0;
	}

	/*모든 해당 마디에 집합Y에 대하여 초기화를 해 준다.(이때, 시작점은 v5이다.)*/
	/*Y로 부터의 거리를 초기화를 해준다.(시작점이 v1임으로 distance[i] 는 vi와 v5사이의 거리이다.)*/
	check[5] = 1;
	for (i = 1; i <= n; i++)
	{
		if (i != 5)
		{
			nearest[i] = 5;
			distance[i] = W[5][i];
		}
	}

	printf("정점들이 연결지어지는 과정을 출력합니다.(v5부터 시작)\n");
	/*도시의 개수가 n개 이면 엣지는 최소 n-1개가 있으면 모든 노드들이 연결이 될 수 있다.*/
	for (j = 1; j <= n - 1; j++)
	{
		min = INF;

		/*각각의 정점들에 대하여 가장 짧은 엣지의 길이를 min에다가 저장을 하고 그때 해당하는 Y여집합에 포함되는
		정점을 vnear에다가 저장을 해 준다.*/
		for (i = 1; i <= n; i++)
		{
			if (n != 5)
			{
				if (0 <= distance[i] && distance[i] < min)
				{
					min = distance[i];
					vnear = i;
				}
			}
		}

		/*정점 선택되었는지 상태를 저장과 출력을 해 주는 함수*/
		/*check 배열의 값은0 이면 연결이 안된 상태이고 1이면 연결이 되어있는 상태이다*/
		printf("%d번 과정 후 ->", j);
		check[vnear] = 1;
		for (i = 1; i <= n; i++)
		{
			printf("%d ", check[i]);
		}
		printf("\n");

		//MST에다가 해당 정보를 저장
		R[nearest[vnear]][vnear] = min;
		R[vnear][nearest[vnear]] = min;
		sum += min;

		//엣지의 정보를 행렬F에 저장
		F[count] = min;
		count++;

		distance[vnear] = -1; // vnear에 해당하는 정점는 이제 연결이 되어 있음으로 거리를 고려를 해 주지 않기 위하여 -1로 저장

		//새로 들어온 정점vnear에 대하여 거리에 대한 정보의 갱신
		for (i = 1; i <= n; i++)
		{
			if (i != 5)
			{
				if (W[i][vnear] < distance[i])
				{
					distance[i] = W[i][vnear];
					nearest[i] = vnear;
				}
			}
		}
	}


	printf("\n뽑힌 엣지의 순서는 다음과 같습니다 ->");
	for (j = 1; j <= n - 1; j++)
	{
		printf("%d ", F[j]);
	}
	printf("\n\n");
	
	printf("최소 비용 신장 트리에서의 엣지 가중치의 합 -> %d\n", sum);


	printf("\nprim's Algorithm을 사용하여 MST를 출력합니다(V5부터 시작, 인접행렬로 표현)\n");
	for (i = 1; i <= NUM - 1; i++)
	{
		for (j = 1; j <= NUM - 1; j++)
		{
			printf("%3d ", R[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}