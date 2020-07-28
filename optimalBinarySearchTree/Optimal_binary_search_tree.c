#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 100
/*트리 노드 데이터의 생성*/
typedef struct {
	char  key[10];
	double  p;
}Member;

/*트리의 노드*/
typedef struct node {
	char key[10];
	struct node *left;
	struct node *right;
}nodetype;
typedef nodetype* node_pointer;	//노드 포인터 구조체

Member key[MAX + 1];// 입력받을 키 멤버의 구조체의 선언
double A[MAX + 1][MAX];//최소 신장 트리에서의 확률의 최소값을 담을 행렬의 선언
int R[MAX + 1][MAX];//최소 신장 트리에서 어느 인덱스가 뿌리가 될 때가 최소가 되는지 키값을 담을 행렬의 선언
double p[MAX] = { 0, }; //최소 신장 트리에서 확률을 담을 배열의 선언
node_pointer root;//루트를 가르키는 포인터의 선언

void input_data(int n);    //트리를 만들 노드들의 데이터를 넣어주는 함수
double iSum(int i, int j);  //i부터 j까지의 확률의 덧셈의 값을 반환하는 함수
void optsearchtree(int n, double p[], double A[][MAX], double *minavg, int R[][MAX]);  //행렬 A와 행렬 R을 구하는 알고리즘
int minimum(int i, int j, int k);  //최소값을 반환해주는 함수의 구현(최소 신장 트리에서 사용)
void make_root(int n);  //루트를 생성해주는 함수
node_pointer tree(int i, int j); //최적 이진 탐색 트리를 구현하는 함수
void print_root();    //최적 이진 탐색 트리 루트를 출력
void print_tree(node_pointer root); //중위 표기법으로 트리의 노드들을 표현

int main()
{
	int num = 0;
	double minavg = 0.0;
	printf("***********최적 이분검색트리의 작업을 시작하겠습니다***********\n");
	printf("입력받을 키의 개수를 입력해 주세요: ");
	scanf("%d", &num);
	input_data(num);
	optsearchtree(num, p, A, &minavg, R);
	printf("최소 평균검색 시간 -> %.3lf\n\n", minavg);
	make_root(num);
	print_root();
	printf("최적 이분검색 트리의 출력(중위 표기법) -> ");
	print_tree(root);
	printf("\n");
	return 0;
}

/*트리를 만들 노드들의 데이터를 넣어주는 함수*/
void input_data(int num)
{
	int i;
	double per = 0.0;
	char name[20];
	/*트리 노드 데이터의 입력*/
	for (i = 1; i <= num; i++)
	{
		printf("--------------------------\n");
		printf("키값을 입력하세요 : ");
		scanf("%s", name);
		strcpy(key[i].key, name);
		printf("확률을 입력하세요 : ");
		scanf("%lf", &per);
		key[i].p = per;
	}
	printf("\n");
	/*노드 데이터에 들어 있는 확률을 배열에 저장*/
	for (i = 1; i <= num; i++)
	{
		p[i] = key[i].p;
	}
}

/*최소값을 반환해주는 함수의 구현(최소 신장 트리에서 사용)*/
int minimum(int i, int j, int k)
{
	/*현재 행렬안에 초기화 되어 있음으로 첫번째 비교 대상은 행렬에 넣어준다.*/
	if (k == i)
	{
		/*k를 루트에다가 두고 확률을 곱하였을때의 재귀관계식이다.*/
		A[i][j] = A[i][k - 1] + A[k + 1][j] + iSum(i, j);
		/*이때의 k값을 반환 */
		return k;
	}

	if (k != i)
	{
		/*만일 새로운 k를 중심으로 쪼개어 연산을 실행 하였을때 그 값이 더 작으면 최적의 값을 갱신하여 준다.*/
		if (A[i][j] >A[i][k - 1] + A[k + 1][j] + iSum(i, j))
		{
			/*k를 루트에다가 두고 확률을 곱하였을때의 재귀관계식이다.*/
			A[i][j] = A[i][k - 1] + A[k + 1][j] + iSum(i, j);
			/*이때의 k값을 반환 */
			return k;
		}
	}
	return R[i][j];  //k일때 해당하지 않으면 원래의 값을 리턴
}

/*i부터 j까지의 확률의 덧셈의 값을 반환하는 함수*/
double iSum(int i, int j)
{
	double sum = 0;
	int k;

	/*인덱스 i부터 j까지의 합 구하기*/
	for (k = i; k <= j; k++)
	{
		sum += key[k].p;
	}
	return sum;
}

/*행렬 A와 행렬 R을 구하는 알고리즘*/
void optsearchtree(int n, double p[], double A[][MAX], double *minavg, int R[][MAX])
{
	int i, j, k, diagonal,knum;
	/*배열 A와 배열 D의 초기화 작업*/
	for (i = 0; i <= n; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}

	A[n + 1][n] = 0;
	R[n + 1][n] = 0;
	/*대각선의 순서대로 확률을 동적 계획법으로 구함*/
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;
			for (k = i; k <= j; k++)
			{
				knum = minimum(i, j, k);
				R[i][j] = knum;    //k가 루트이면 값을 갱신하고 그러지 않으면 원래의 값을 유지한다.
			}
		}
	}
	*minavg = A[1][n]; //key1부터 keyn까지 최소 신장 트리를 만드는데 최소 확률의 계산값

	/*행렬 A의 출력*/
	printf("\n--------------------------------\n");
	printf("최적 이분검색트리 알고리즘 행렬A 구하기!\n");
	for (i = 1; i <= n+1; i++)
	{
		for (j = 0; j <= n; j++)
		{
			printf("%.3lf ", A[i][j]);
		}
		printf("\n");
	}

	/*행렬R의 출력*/
	printf("\n--------------------------------\n");
	printf("최적 이분검색트리 알고리즘 행렬R 구하기!\n");
	for (i = 1; i <= n + 1; i++)
	{
		for (j = 0; j <= n; j++)
		{
			printf("%2d ", R[i][j]);
		}
		printf("\n");
	}
}

/*루트를 생성해주는 함수*/
void make_root(int n)
{
	root = tree(1, n); // n은 노드의 개수이다.
}

/*최적 이진 탐색 트리를 구현하는 함수*/
node_pointer tree(int i, int j)
{
	int k;
	node_pointer p;

	k = R[i][j];
	if (k == 0)
	{
		return NULL;
	}
	else
	{
		p = (node_pointer)malloc(sizeof(nodetype)); //새로운 노드 생성을 위한 메모리 할당
		strcpy(p->key, key[k].key);                 //key 값을 노드로 복사
		p->left = tree(i, k - 1);                   //왼쪽 서브 트리의 생성
		p->right = tree(k + 1, j);                  //오른쪽 서브 트리의 생성
		return p;                                   //노드의 포인터 반환
	}
}

/*최적 이진 탐색 트리 루트를 출력*/
void print_root()
{
	node_pointer p;
	p = root;
	printf("최적 이진 탐색 트리 최상위 노드->%s\n", p->key);
}

/*중위 표기법으로 트리의 노드들을 표현*/
void print_tree(node_pointer root)
{
	if (root != NULL)
	{
		print_tree(root->left);
		printf(" %s ", root->key);
		print_tree(root->right);
	}
}