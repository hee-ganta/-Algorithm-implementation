#include <stdio.h>
#include <stdlib.h>


#define MAX 100 //�ִ� ���� �� �ִ� �������� ����

typedef struct node {
	int level; //����� ���� ����
	int profit;//����� �ش� ����ġ
	int weight;//����� ���� ���� 
	int items[MAX]; // ������ ��� ���¿��� � �������� ��� �ִ��� ������ �������ִ� �迭
					//�ش� �ε����� �������� �� ������ 1�� ����, �� ���� ������ 0�� ���� 
}NODE; //��� ������ ���� ����ü ���� 

typedef struct nodeQueue {
	int max;
	int num;
	int front;
	int rear;
	NODE *que;
}NODEQUEUE; //��带 ������ ť ����ü ����

int initialize(NODEQUEUE *q, int max);//ť�� �ʱ�ȭ
int enque(NODEQUEUE *q, NODE x);//��ť �۾�
int deque(NODEQUEUE *q, NODE x);//��ť �۾�
int empty(NODEQUEUE *q);//ť�� ����ִ��� �˻�
void knapsack(int n,int *p, int *w, int W,int *maxprofit);//�賶 ä��� ���縦 �ذ��ϴ� �˰���(Breath-First)
double bound(int n, NODE u);//�ش� ����� ����ġ �Ѱ谪�� ��ȯ
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
int count = 1; //Ž���� ����� ���� ���ִ� ����

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

	printf("\n\n**********************Breadth-First �˰����� ������ ����Դϴ�**********************\n\n");
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

/*ť �ʱ�ȭ ���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int initialize(NODEQUEUE *q, int max)
{
	q->num = 0; //ť ���� ����ü�� ���� �ʱ�ȭ
	q->rear = 0;
	q->front = 0;
	q->que =(NODE *)calloc(max, sizeof(NODE)); //ť�� ũ�⸦ ����
	if (q->que == NULL) //���н�
	{
		q->max = 0;
		return 0;
	}
	q->max = max; //������
	return 1;
}

/*ť�� �����͸� ���� ���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int enque(NODEQUEUE *q, NODE x)
{
	if (q->num >= q->max) //ť�� ����ִ� ������ ���ġ�� �ʰ��ϸ� �����͸� ���� �� ����
	{
		return 0;
	}
	else
	{
		q->num++; //ť ������ ���� �÷���
		q->que[q->rear] = x; //�����κп� �����͸� �־���
		q->rear++;
		if (q->rear == q->max) //�� ����� ť ����
			q->rear = 0;
		return 1;
	}
}

/*ť�� �����͸� ���� ���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int deque(NODEQUEUE *q, NODE *x)
{
	if (q->num <= 0) //���̻� ������ �����Ͱ� ������ ����
		return 0;
	else
	{
		q->num--; //������ �ٿ���
		*x = q->que[q->front]; //�պκп� �ִ� �����͸� ����
		q->front++;
		if (q->front == q->max) //�� ����� ť ����
			q->front = 0;
		return 1;
	}
}

/*ť�� �����Ͱ� ��� �ִ��� Ȯ���ϴ� �Լ� ���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int empty(NODEQUEUE *q)
{
	if (q->num <= 0) //�ش� ������ 0 �����̸� �������
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void knapsack(int n, int *p, int *w, int W,int *maxprofit)
{
	NODEQUEUE Q;
	NODE u, v;
	int i;
	int quesize = 1; //ť�� ����� ����(i�������� �ִ� �ڽ� ����� ������ 2^n�̴�)
	for (i = 1; i <= n; i++)
	{
		quesize = quesize * 2;
	}


	initialize(&Q, quesize);//ť�� �ʱ�ȭ
	v.level = 0; //0�� ���ؿ����� ����� ������ ����
	v.profit = 0;
	v.weight = 0;
	*maxprofit = 0;
	enque(&Q, v);//��带 ��ť

	while (empty(&Q) == 0) //ť�� ������� �� ���� �ݺ�
	{
		
		deque(&Q, &v); //ť���� �� ��带 ��ť
		count = count + 2; //������ ��忡 ���ؼ� �ڽ� �ΰ��� Ž���� �� ��
		u.level = v.level + 1; //�ܰԸ� �ϳ� �÷��� ���� �������� �־��� ���� ���� ��ȯ
		u.weight = v.weight + w[u.level];
		u.profit = v.profit + p[u.level];
		for (i = 1; i < u.level; i++) //�̶������� ������ ���� ���¸� �ڽ� ��忡�� ������ ����
		{
			u.items[i] = v.items[i];
		}
		
		u.items[u.level] = 1; //�� �ܰ踦 ������ ���� ��� �̹Ƿ� �������� ���� ���·� �ٲ���
		if (u.weight <= W && u.profit > *maxprofit) //�ش� ����� ������ maxprofit�� �ѱ�� ���� 
		{
			*maxprofit = u.profit;
			for (i = 1; i <= u.level; i++) //�̶��� ���°� ���� �����ϴٰ� �����Ͽ� bestitems�迭�� ������ ���� ���¸� �Ѱ���
			{
				bestitems[i] = u.items[i];
			}
		}

		if (bound(n, u) > *maxprofit) //�� �ڽ� ��尡 �����ϸ� ��带 ��ť
		{
			enque(&Q, u);
		}

		u.weight = v.weight; //�� �ܰ踦 ���� ���¿��� �������� ���� �ʾ��� ���� ��� ���·� �ٲ���
		u.profit = v.profit;
		u.items[u.level] = 0;//�� �ܰ踦 ������ ���� ��� �̹Ƿ� �������� ���� ���� ���·� �ٲ���


		if (bound(n, u) > *maxprofit)// �ڽ� ��尡 �����ϸ� ��带 ��ť
		{
			enque(&Q, u);
		}
	}
}

/*�ش� ����� ����ġ �Ѱ谪�� ��ȯ*/
double bound(int n, NODE u)
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

//���� ������ ����
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