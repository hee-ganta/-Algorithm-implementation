#include <stdio.h>
#include <stdlib.h>


#define MAX 100 //�ִ� ���� �� �ִ� �������� ����
typedef struct node NODE;
typedef struct _list PRIQUE;

struct node {
	int level; //����� ���� ����
	int profit;//����� �ش� ����ġ
	int weight;//����� ���� ���� 
	int items[MAX]; // ������ ��� ���¿��� � �������� ��� �ִ��� ������ �������ִ� �迭
					//�ش� �ε����� �������� �� ������ 1�� ����, �� ���� ������ 0�� ���� 
	double bound;
	NODE *next;
	NODE *prev;
}; //��� ������ ���� ����sü ���� 

struct _list {
	NODE *head;
	NODE *tail;
	int size;
}; //�켱���� ť�� ��ũ�� ����Ʈ�� ����

void initialize(PRIQUE *PQ);//�켱���� ť ���� ����ü�� �ʱ�ȭ
void insert(PRIQUE *PQ, NODE m);//�켱����ť�� �����͸� �־��� 
void remove1(PRIQUE *PQ, NODE *m);
int empty(PRIQUE *PQ);//�켱���� ť�� ����ִ��� �˻�
void knapsack(int n, int *p, int *w, int W, int *maxprofit);//Best-First������� �賶 ä��� �˰����� ����
double bound(NODE u);//�ش� ����� ����ġ �Ѱ谪�� ��ȯ
void quicksort(int low, int high, double *S); //���Դ� ����ġ�� ������������ �迭
void partition(int low, int high, int *pivotpoint, double *S);


/*�ʿ��� �������� ���������� ����*/
int W;
int n; //�������� ������ ���� �� ����
int maxprofit = 0;
int w[MAX] = { 0. }; //�������� ���Ը� ������ �迭
int p[MAX] = { 0, }; //�������� ����ġ�� ������ �迭
double pw[MAX] = { 0, }; //�������� ���Դ� ����ġ�� ������ �迭
int bestitems[MAX] = { 0, }; //�ش��尡 �����ϰ� �װ��� ���̶�� ���ݱ��� � �����Ͱ� ����ִ��� ������ ���� �迭
							 //�ش� �ε����� �������� �� ������ 1�� ����, �� ���� ������ 0�� ���� 
int count = 1;

int main()
{
	int i;

	printf("�������� ������ �Է��� �ּ���: ");
	scanf("%d", &n);
	printf("ä�� �� �ִ� ���Ը� �Է��� �ּ���: ");
	scanf("%d", &W);

	printf("�����۵��� �Ӽ����� �Է�\n");
	for (i = 1; i <= n; i++)
	{
		printf("����ġ ���� : ");
		scanf("%d %d", &p[i], &w[i]);
		pw[i] = (double)p[i] / (double)w[i];
	}

	quicksort(1, n, pw); //����ġ�� �������� ������������ �������� �迭

	printf("\n*****************************\n");
	printf("�������� ������ �����ϴ�\n\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d ->p%d : %d, w%d : %d\n", i, i, p[i], i, w[i]);
	}

	printf("\n\n**********************Best-First �˰����� ������ ����Դϴ�**********************\n\n");
	knapsack(n,p,w,W,&maxprofit);
	printf("���� �� �ִ� �ִ� ����ġ�� %d�Դϴ�.\n", maxprofit);
	printf("���� �������� ������ ������ �����ϴ� ->");
	for (i = 1; i <= n; i++)
	{
		if (bestitems[i] == 1)//bestitems�迭�� �̿��Ͽ� ���� �������� ������ ���
		{
			printf("w%d ", i);
		}
	}
	printf("\n\n");
	printf("Ž���� ����� ���� %d�� �Դϴ�\n\n", count);
	return 0;
}

/*Best-First ������� �賶 ä��� �˰����� ����*/
void knapsack(int n, int *p, int *w, int W, int *maxprofit)
{
	PRIQUE PQ;//�켱���� ť(����Ʈ)�� ������ ����ü�� ����
	NODE u, v;//�θ���� �ڽ� ��带 �켱���� ť(����Ʈ)�� �ֱ� ���� ��� ���� ����
	int i;

	initialize(&PQ);//�켱���� ť�� �ʱ�ȭ
	v.level = 0;//0�� ���ؿ����� ����� ������ �ʱ�ȭ
	v.profit = 0;
	v.weight = 0;
	*maxprofit = 0;
	v.bound = bound(v);
	insert(&PQ, v);//��带 �켱���� ť�� �������
	while (empty(&PQ) == 0)//�켱���� ť�� ������� �� ���� �ݺ�
	{
		remove1(&PQ, &v);//�켱���� ť���� �Ѱ�ġ�� ���� ���� ��带 ����
		if (v.bound > *maxprofit)
		{
			count = count + 2;
			u.level = v.level + 1;//�ܰ踦 �ϳ� �÷� �� ���� �������� �־��� ���� ���� ��ȯ
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			for (i = 1; i < u.level; i++) //�̶������� ������ ���� ���¸� �ڽ� ��忡�� ������ ����
			{
				u.items[i] = v.items[i];
			}

			u.items[u.level] = 1; //�� �ܰ踦 ������ ���� ��� �̹Ƿ� �������� ���� ���·� �ٲ���
			if (u.weight <= W && u.profit > *maxprofit)
			{
				*maxprofit = u.profit;
				for (i = 1; i <= u.level; i++) //�̶��� ���°� ���� �����ϴٰ� �����Ͽ� bestitems�迭�� ������ ���� ���¸� �Ѱ���
				{
					bestitems[i] = u.items[i];
				}
			}
			u.bound = bound(u);//�Ѱ�ġ�� �ش� ��忡 ����
			if (u.bound > *maxprofit) //�� �ڽ� ��尡 �����ϸ� �켱���� ť�� �������
				insert(&PQ, u);
			u.weight = v.weight;//�� �ܰ踦 ���� ���¿��� �������� ���� �ʾ��� ���� ��� ���·� �ٲ���
			u.profit = v.profit;
			u.bound = bound(u);//�̶��� �Ѱ�ġ�� ��忡 ����
			u.items[u.level] = 0;//�� �ܰ踦 ������ ���� ��� �̹Ƿ� �������� ���� ���� ���·� �ٲ���
			if (u.bound > *maxprofit)//�� �ڽ� ��尡 �����ϸ� �켱���� ť�� �־���
				insert(&PQ, u);
		}
	}
	free(PQ.head); //���� �Ҵ��� ����
	free(PQ.tail);
}

double bound(NODE u)
{
	int j;
	int totweight; // W�� �ѱ��� ���� ������ �ɰ��� ���� �����۵��� �־��� ���� ���Ը� ���� �� �� ����
	double result;//��� ����ġ�� �Ѱ踦 ���� �� �� ����

	if (u.weight >= W)//����� ���԰� W�Ѿ����� �̴� ���̻� �������� �������� ��� �� ���� �ʱ� ���� 0�� ��ȯ
		return 0;
	else
	{
		result = u.profit;//�ش� ����� ����ġ�� �Ѱ��� 
		j = u.level + 1;
		totweight = u.weight; //�ش� ����� ���Ը� �Ѱ���

		while (j <= n && totweight + w[j] <= W) //������ �������� ���� �ѱ��� �ʰ� ���Ը� ������ �� ������ ���� �� �ִ� �ִ� ���Ը� �ѱ��� ���� ������ �۾��� ����
		{
			totweight = totweight + w[j]; //���Ը� ����
			result = result + p[j];//����ġ�� ����
			j++;
		}
		if (j <= n) //���� �������� �� ���� �ʾҴµ� �ݺ����� ������ ���
			result = result + (W - totweight) * p[j] / w[j]; //W�� �������� �־��� ���� ���԰� ���� ����� �ֱ� ���ؼ� �������� ���Դ� ����ġ�� ����Ͽ� ������
		return result;//����ġ�� �Ѱ谪�� ��ȯ
	}
}

/*��ũ�� ����Ʈ�� ���� ���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
void initialize(PRIQUE *PQ)
{
	PQ->head = (NODE*)malloc(sizeof(NODE));
	if (PQ->head == NULL)
	{
		printf("�޸� �Ҵ� ����\n");
		exit(1);
	}
	PQ->head->bound = -1; // �Ӹ� �κп��� ���� ���� ���ġ
	PQ->tail = (NODE*)malloc(sizeof(NODE));
	if (PQ->tail == NULL)
	{
		printf("�޸� �Ҵ� ����\n");
		exit(1);
	}
	PQ->tail->bound = 1000;// ���� �κп��� ���� ū ���ġ
	PQ->head->next = PQ->tail; //�����κа� �Ӹ� �κ��� ���� �̾���
	PQ->head->prev = PQ->head;
	PQ->tail->next = PQ->tail;
	PQ->tail->prev = PQ->head;
	PQ->size = 0;
}

/*���ο� ����� ���� �Լ�(����� �Ѱ谪�� �������� ���� ���� head �κ� ū ���� tail�κ� ������ ����)*/
void insert(PRIQUE *PQ, NODE m)
{	
	int i;
	NODE *np;
	NODE *cur;
	np = (NODE*)malloc(sizeof(NODE));
	cur = (NODE*)malloc(sizeof(NODE));
	if (np == NULL || cur == NULL)
	{
		printf("�޸� �Ҵ� ����\n");
		exit(1);
	}
	np->bound = m.bound; //�ְ��� �ϴ� ������ ��忡 �ִ� �۾�
	np->level = m.level;
	np->weight = m.weight;
	np->profit = m.profit;
	for (i = 1; i <= n; i++)
	{
		np->items[i] = m.items[i];
	}
	cur = PQ->head;
	while (cur->bound <= m.bound) //����� �ִ� �Ѱ谪�� �������� ������ �Ӹ��κ������� 
	{							  //ũ�� ���� �κ������� ������� ��ġ������ Ŀ���� �ű�
		cur = cur->next;
	}
	np->next = cur; //������ ���� �̾���
	np->prev = cur->prev;
	cur->prev->next = np;
	cur->prev = np;
	PQ->size++;
	cur = NULL;
	free(cur); // �����Ҵ��� ��ȿ
}

void remove1(PRIQUE *PQ, NODE *m)
{
	int i;
	NODE *cur;
	cur = (NODE*)malloc(sizeof(NODE));
	if (cur == NULL)
	{
		printf("�޸� �Ҵ� ����\n");
		exit(1);
	}
	cur = PQ->tail->prev;

	m->bound = cur->bound; //�켱���� ť���� �Ѱ谪�� ���� ū ��忡 Ŀ���� �Ű� �� ������ ��忡�� ����
	m->level = cur->level;
	m->profit = cur->profit;
	m->weight = cur->weight;
	for (i = 1; i <= n; i++)
	{
		m->items[i] = cur->items[i];
	}
	cur->prev->next = cur->next; //Ž���� ���� �켱���� ť���� ������Ŵ
	cur->next->prev = cur->prev;
	m->prev = NULL;
	m->next = NULL;
	cur = NULL;
	free(cur);
	PQ->size--;

}

/*����Ʈ�� ��� �ִ����� �˻� ���� - 1�� ��ȯ,  ���� - 0�� ��ȯ*/
int empty(PRIQUE *PQ)
{
	if (PQ->size <= 0) //�켱���� ť�� ����� 0���� ������ ��� ����
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
	//�Ǻ� ������ ���� ������ ����
	int pivotpoint = 0;

	if (high > low)
	{
		//�ش� �迭�� ���Ͽ� �� ���� ���� �Ǻ� ����Ʈ�� ���ϰ�
		//������ �� ��ģ����
		//�Ǻ��� �� ���� �ش� �ڸ��� �־��ش�
		partition(low, high, &pivotpoint, S);
		//ó���κп��� �Ǻ��� �� �κб����� �ٽ� ���� ���ķ� ���� 
		quicksort(low, pivotpoint - 1, S);
		//�Ǻ��� ���� �κк��� �� �κб��� �ٽ� ���� ���ķ� ����
		quicksort(pivotpoint + 1, high, S);
	}
}

void partition(int low, int high, int *pivotpoint, double *S)
{
	int i, j, wtemp, ptemp;
	double pivotitem;
	double temp;

	//�Ǻ��� �����ϰ��� �ϴ� �迭�� ù �κ����� ����
	pivotitem = S[low];
	//�Ǻ����� ���� �����Ͱ� ���� ��� �ڸ��� �ٲ��ֱ� ����
	//��ġ�� ��� ���� ������ ����
	j = low;
	//�Ǻ����� ���� ���� �����ͺ��� �迭�� �� �κ� ������ ������ ������ ����
	for (i = low + 1; i <= high; i++)
	{
		//���� �ش� �����Ͱ� �Ǻ� �����ۺ��� ū ��� ��ġ�� �� �κ����� �ű�
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
	//������ �� ��ġ�� �� �Ŀ� �ش� �Ǻ��� �Ǻ�����
	//���� �����Ϳ� ū ������ ���̿� ��ġ��Ŵ
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