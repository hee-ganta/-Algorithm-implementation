#include <stdio.h>
#include <stdlib.h>


#define MAX 100 //최대 받을 수 있는 아이템의 개수
typedef struct node NODE;
typedef struct _list PRIQUE;

struct node {
	int level; //노드의 현제 레벨
	int profit;//노드의 해당 값어치
	int weight;//노드의 현재 무게 
	int items[MAX]; // 현재의 노드 상태에서 어떤 아이템이 들어 있는지 정보를 저장해주는 배열
					//해당 인덱스의 아이템이 들어가 있으면 1을 저장, 들어가 있지 않으면 0을 저장 
	double bound;
	NODE *next;
	NODE *prev;
}; //노드 정보를 담을 구조s체 선언 

struct _list {
	NODE *head;
	NODE *tail;
	int size;
}; //우선순위 큐를 링크드 리스트로 구현

void initialize(PRIQUE *PQ);//우선순위 큐 관리 구조체의 초기화
void insert(PRIQUE *PQ, NODE m);//우선순위큐에 데이터를 넣어줌 
void remove1(PRIQUE *PQ, NODE *m);
int empty(PRIQUE *PQ);//우선순위 큐가 비어있는지 검사
void knapsack(int n, int *p, int *w, int W, int *maxprofit);//Best-First방법으로 배낭 채우기 알고리즘을 수행
double bound(NODE u);//해당 노드의 값어치 한계값을 반환
void quicksort(int low, int high, double *S); //무게당 값어치를 내림차순으로 배열
void partition(int low, int high, int *pivotpoint, double *S);


/*필요한 변수들을 전역변수로 지정*/
int W;
int n; //아이템의 개수를 저장 할 변수
int maxprofit = 0;
int w[MAX] = { 0. }; //아이템의 무게를 저장할 배열
int p[MAX] = { 0, }; //아이템의 값어치를 저장할 배열
double pw[MAX] = { 0, }; //아이템의 무게당 값어치를 저장할 배열
int bestitems[MAX] = { 0, }; //해당노드가 유망하고 그것이 답이라면 지금까지 어떤 데이터가 들어있는지 정보를 담을 배열
							 //해당 인덱스의 아이템이 들어가 있으면 1을 저장, 들어가 있지 않으면 0을 저장 
int count = 1;

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

	printf("\n\n**********************Best-First 알고리즘을 수행한 결과입니다**********************\n\n");
	knapsack(n,p,w,W,&maxprofit);
	printf("넣을 수 있는 최대 값어치는 %d입니다.\n", maxprofit);
	printf("넣은 아이템의 종류는 다음과 같습니다 ->");
	for (i = 1; i <= n; i++)
	{
		if (bestitems[i] == 1)//bestitems배열을 이용하여 담은 아이템의 종류를 출력
		{
			printf("w%d ", i);
		}
	}
	printf("\n\n");
	printf("탐방한 노드의 수는 %d개 입니다\n\n", count);
	return 0;
}

/*Best-First 방법으로 배낭 채우기 알고리즘을 수행*/
void knapsack(int n, int *p, int *w, int W, int *maxprofit)
{
	PRIQUE PQ;//우선순위 큐(리스트)를 관리할 구조체의 선언
	NODE u, v;//부모노드와 자식 노드를 우선순위 큐(리스트)에 넣기 위한 노드 변수 선언
	int i;

	initialize(&PQ);//우선순위 큐의 초기화
	v.level = 0;//0의 수준에서의 노드의 정보를 초기화
	v.profit = 0;
	v.weight = 0;
	*maxprofit = 0;
	v.bound = bound(v);
	insert(&PQ, v);//노드를 우선순위 큐에 집어넣음
	while (empty(&PQ) == 0)//우선순위 큐가 비어있을 때 까지 반복
	{
		remove1(&PQ, &v);//우선순위 큐에서 한계치가 가장 높은 노드를 빼냄
		if (v.bound > *maxprofit)
		{
			count = count + 2;
			u.level = v.level + 1;//단계를 하나 올려 준 다음 아이템을 넣었을 때의 노드로 전환
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			for (i = 1; i < u.level; i++) //이때까지의 아이템 저장 상태를 자식 노드에게 정보를 저장
			{
				u.items[i] = v.items[i];
			}

			u.items[u.level] = 1; //한 단계를 높였을 때의 경우 이므로 아이템을 넣은 상태로 바꿔줌
			if (u.weight <= W && u.profit > *maxprofit)
			{
				*maxprofit = u.profit;
				for (i = 1; i <= u.level; i++) //이때의 상태가 가장 유망하다고 생각하여 bestitems배열에 아이템 저장 상태를 넘겨줌
				{
					bestitems[i] = u.items[i];
				}
			}
			u.bound = bound(u);//한계치를 해당 노드에 저장
			if (u.bound > *maxprofit) //이 자식 노드가 유망하면 우선순위 큐에 집어넣음
				insert(&PQ, u);
			u.weight = v.weight;//한 단계를 높인 상태에서 아이템을 넣지 않았을 때의 노드 상태로 바꿔줌
			u.profit = v.profit;
			u.bound = bound(u);//이때의 한계치를 노드에 저장
			u.items[u.level] = 0;//한 단계를 높였을 때의 경우 이므로 아이템을 넣지 않은 상태로 바꿔줌
			if (u.bound > *maxprofit)//이 자식 노드가 유망하면 우선순위 큐에 넣어줌
				insert(&PQ, u);
		}
	}
	free(PQ.head); //동적 할당의 종료
	free(PQ.tail);
}

double bound(NODE u)
{
	int j;
	int totweight; // W를 넘기지 않을 때까지 쪼개지 않은 아이템들을 넣었을 때의 무게를 저장 해 줄 변수
	double result;//노드 값어치의 한계를 저장 해 줄 변수

	if (u.weight >= W)//노드의 무게가 W넘었으면 이는 더이상 유망하지 않음으로 고려 해 주지 않기 위해 0을 반환
		return 0;
	else
	{
		result = u.profit;//해당 노드의 값어치를 넘겨줌 
		j = u.level + 1;
		totweight = u.weight; //해당 노드의 무게를 넘겨줌

		while (j <= n && totweight + w[j] <= W) //레벨이 아이템의 수를 넘기지 않고 무게를 더했을 때 가방이 담을 수 있는 최대 무게를 넘기지 않을 때까지 작업을 수행
		{
			totweight = totweight + w[j]; //무게를 누적
			result = result + p[j];//값어치를 누적
			j++;
		}
		if (j <= n) //만일 아이템을 다 넣지 않았는데 반복문을 나왔을 경우
			result = result + (W - totweight) * p[j] / w[j]; //W와 아이템을 넣었을 때의 무게가 같게 만들어 주기 위해서 아이템의 무게당 값어치를 고려하여 더해줌
		return result;//값어치의 한계값을 반환
	}
}

/*링크드 리스트의 구현 성공 - 1을 반환, 실패 - 0을 반환*/
void initialize(PRIQUE *PQ)
{
	PQ->head = (NODE*)malloc(sizeof(NODE));
	if (PQ->head == NULL)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}
	PQ->head->bound = -1; // 머리 부분에는 가장 작은 기대치
	PQ->tail = (NODE*)malloc(sizeof(NODE));
	if (PQ->tail == NULL)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}
	PQ->tail->bound = 1000;// 꼬리 부분에는 가장 큰 기대치
	PQ->head->next = PQ->tail; //꼬리부분과 머리 부분을 서로 이어줌
	PQ->head->prev = PQ->head;
	PQ->tail->next = PQ->tail;
	PQ->tail->prev = PQ->head;
	PQ->size = 0;
}

/*새로운 노드의 삽입 함수(노드의 한계값을 기준으로 작은 것은 head 부분 큰 것은 tail부분 쪽으로 나열)*/
void insert(PRIQUE *PQ, NODE m)
{	
	int i;
	NODE *np;
	NODE *cur;
	np = (NODE*)malloc(sizeof(NODE));
	cur = (NODE*)malloc(sizeof(NODE));
	if (np == NULL || cur == NULL)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}
	np->bound = m.bound; //넣고자 하는 정보를 노드에 넣는 작업
	np->level = m.level;
	np->weight = m.weight;
	np->profit = m.profit;
	for (i = 1; i <= n; i++)
	{
		np->items[i] = m.items[i];
	}
	cur = PQ->head;
	while (cur->bound <= m.bound) //노드의 최대 한계값을 기준으로 작으면 머리부분쪽으로 
	{							  //크면 꼬리 부분쪽으로 순서대로 배치함으로 커서를 옮김
		cur = cur->next;
	}
	np->next = cur; //노드들을 서로 이어줌
	np->prev = cur->prev;
	cur->prev->next = np;
	cur->prev = np;
	PQ->size++;
	cur = NULL;
	free(cur); // 동적할당의 종효
}

void remove1(PRIQUE *PQ, NODE *m)
{
	int i;
	NODE *cur;
	cur = (NODE*)malloc(sizeof(NODE));
	if (cur == NULL)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}
	cur = PQ->tail->prev;

	m->bound = cur->bound; //우선순위 큐에서 한계값이 가장 큰 노드에 커서를 옮겨 그 정보를 노드에게 전달
	m->level = cur->level;
	m->profit = cur->profit;
	m->weight = cur->weight;
	for (i = 1; i <= n; i++)
	{
		m->items[i] = cur->items[i];
	}
	cur->prev->next = cur->next; //탐색한 노드는 우선순위 큐에서 배제시킴
	cur->next->prev = cur->prev;
	m->prev = NULL;
	m->next = NULL;
	cur = NULL;
	free(cur);
	PQ->size--;

}

/*리스트가 비어 있는지를 검사 성공 - 1을 반환,  실패 - 0을 반환*/
int empty(PRIQUE *PQ)
{
	if (PQ->size <= 0) //우선순위 큐의 사이즈가 0보다 작으면 비어 있음
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

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