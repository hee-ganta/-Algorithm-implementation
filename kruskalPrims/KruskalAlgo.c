#include <stdio.h>
#define NUM 11
#define INF 100

/*정점과 정점 사이의 엣지에 대한 정보를 저장할 구조체의 선언*/
typedef struct Node_data{
	int node1;
	int node2;
	int edge;
}Data; 

void create(Data* data, int a, int b, int c);	//구조체에 데이터를 넣어주는 함수
void partition(int low, int high, int *pivotpoint,Data data[13]);
void quicksort(int low, int high, Data data[13]);  //빠른 정렬함수(엣지를 오름차순으로 정렬하기 위하여 사용)
int find(int set[], int x);	//해당 정점의 부모 정점를 찾는 함수
void merge(int set[], int a, int b);	//부모 정점를 같게 해주는 함수
void kruskal(int n,Data data[], int *F);	//크루스칼 알고리즘의 구현


int main()
{
	Data data[13];		//정점들의 연결 상태를 저장해주는 구조체 배열의 선언
	int F[12]; // 선택된 엣지를 저장할 배열의 선언 
	create(&data[0], 1, 2, 32);		//그래프의 연결 상태를 저장
	create(&data[1], 1, 4, 17);
	create(&data[2], 2, 5, 45);
	create(&data[3], 3, 4, 18);
	create(&data[4], 3, 7, 5);
	create(&data[5], 4, 5, 10);
	create(&data[6], 4, 8, 3);
	create(&data[7], 5, 6, 28);
	create(&data[8], 5, 9, 25);
	create(&data[9], 6, 10, 6);
	create(&data[10], 7, 8, 59);
	create(&data[11], 8, 9, 4);
	create(&data[12], 9, 10, 12);
	printf("\n**************kruskal 알고리즘을 수행합니다**************\n\n");
	printf("그래프가 연결되지 않은 부부은 무한대 값으로서 임의로 100의 값으로 지정\n\n");
	quicksort(0, 12, data);		//이음선을 가중치 순서대로 오름차순으로 정렬
	kruskal(NUM,data, F);
	return 0;
}

/*구조체에 데이터를 넣어주는 함수*/
void create(Data* data, int a, int b, int c)
{
	data->node1 = a;
	data->node2 = b;
	data->edge = c;
}

void partition(int low, int high, int *pivotpoint, Data data[13])
{
	int i, j;
	Data temp;
	int pivotitem;

	//피봇을 정돈하고자 하는 배열의 첫 부분으로 설정
	pivotitem = data[low].edge;
	//피봇보다 작은 데이터가 나올 경우 자리를 바꿔주기 위한
	//위치를 담기 위한 변수의 설정
	j = low;
	//피봇으로 부터 다음 데이터부터 배열의 끝 부분 데이터 까지의 정렬의 시작
	for (i = low + 1; i <= high; i++)
	{
		//만약 해당 데이터가 피봇 아이템보다 작은 경우 위치를 앞 부분으로 옮김
		if (data[i].edge < pivotitem)
		{
			j++;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	//정렬을 다 마치고 난 후에 해당 피봇을 피봇보다
	//작은 데이터와 큰 데이터 사이에 위치시킴
	*pivotpoint = j;
	temp = data[low];
	data[low] = data[*pivotpoint];
	data[*pivotpoint] = temp;
}


/*빠른 정렬함수(엣지를 오름차순으로 정렬하기 위하여 사용)*/
void quicksort(int low, int high, Data data[13])
{
	//피봇 정보를 담을 변수의 선언
	int pivotpoint = 0;

	if (high > low)
	{
		//해당 배열에 대하여 맨 앞의 수를 피봇 포인트로 정하고
		//정렬을 다 마친다음
		//피봇이 된 수를 해당 자리에 넣어준다
		partition(low, high, &pivotpoint, data);
		//처음부분에서 피봇의 전 부분까지를 다시 빠른 정렬로 정리 
		quicksort(low, pivotpoint - 1,data);
		//피봇의 다음 부분부터 끝 부분까지 다시 빠른 정렬로 정리
		quicksort(pivotpoint + 1, high,data);
	}
}
/*엣지를 연결할 때 순환경로가 발생하지 않도록 각각의 정점마다
부모 정점의 정보를 저장을 해 준다*/

/*해당 정점의 부모 정점를 찾는 함수*/
int find(int parent[], int r)
{
	if (parent[r] == r) return r;
	return parent[r] = find(parent, parent[r]);
}

/*부모 정점을 같게 해주는 함수*/
void merge(int set[], int a, int b)
{
	a = find(set, a);
	b = find(set, b);
	if (a < b) set[b] = a;
	else set[a] = b;
}

/*크루스칼 알고리즘의 구현*/
void kruskal(int m,Data data[], int *F)
{
	int i, j;	//해당 엣지의 인덱스를 저장할 변수
	int p, q; // 해당 정점의 부모를 저장할 변수
	int k,n;	//반복을 위한 변수의 선언 
	int l = 0;	//엣지을 저장할 배열을 세줄 변수의 저장
	int count = 0;	//이음선의 갯수를 저장할 변수 
	int dcount = 0; //엣지 데이터에 접근하기 위한 변수의 선언
	int e;	//엣지의 정보를 저장할 변수
	int parent[NUM] = { 0, };  //연결되어있는 정점의 부모 정점를 찾기 위한 배열의 선언
	int R[NUM][NUM];		//MST를 저장할 배열의 선언 
	int sum = 0;	//최소 비용 신장트리에서 경로의 합 

	
	/*F배열의 초기화 작업*/
	for (k = 0; k <= m; k++)
	{
		F[k] = 0;
	}

	/*연결 되어있는 부모를 나타내는 배열을 초기화 하는 작업*/
	for (k = 1; k <= m-1; k++)
	{
		parent[k] = k;
	}

	/*배열 R의 초기화 작업*/
	for (k = 1; k <= m-1; k++)
	{
		for (n = 1; n <= m-1; n++)
		{
			R[k][n] = INF;
		}
	}
	
	for (k = 1; k <= m-1; k++)
	{
		R[k][k] = 0;
	}

	while (count < m-2)
	{
		/*각각의 엣지와 정점들의 정보를 변수에 저장하여 연결시에 순환 경로가 있는지 확인해 주는 작업*/
		e = data[dcount].edge;	//엣지저장
		i = data[dcount].node1;	//정점1저장
		j = data[dcount].node2;	//정점2저장

		p = find(parent, i);	//정점1의 부모 정점를 찾음
		q = find(parent, j);	//정점2의 부모 정점를 찾음

		if (p != q)	//만약 결합시에 순환 경로가 생성되지 않는다면
		{
			merge(parent, i, j); //부모 정점를 같게 해 줌 
			F[l] = e;	//엣지 배열에 정보를 저장
			count++;
			l++;
			R[i][j] = e;	//MST에 정보를 저장
			R[j][i] = e;
			sum += e;
		}
		dcount++;
	}

	printf("뽑힌 경로의 순서는 다음과 같습니다->");
	for (k = 0; k < m-2; k++)
	{
		printf("%d ", F[k]);
	}
	printf("\n\n");

	printf("최소 비용 신장 트리에서의 엣지 가중치의 합 -> %d\n", sum);

	printf("\nkruskal Algorithm을 사용하여 MST를 출력합니다(인접행렬로 표현)\n");
	for (k = 1; k <= m-1; k++)
	{
		for (n = 1; n <= m-1; n++)
		{
			printf("%3d ", R[k][n]);
		}
		printf("\n");
	}

}

