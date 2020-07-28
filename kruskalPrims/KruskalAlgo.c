#include <stdio.h>
#define NUM 11
#define INF 100

/*������ ���� ������ ������ ���� ������ ������ ����ü�� ����*/
typedef struct Node_data{
	int node1;
	int node2;
	int edge;
}Data; 

void create(Data* data, int a, int b, int c);	//����ü�� �����͸� �־��ִ� �Լ�
void partition(int low, int high, int *pivotpoint,Data data[13]);
void quicksort(int low, int high, Data data[13]);  //���� �����Լ�(������ ������������ �����ϱ� ���Ͽ� ���)
int find(int set[], int x);	//�ش� ������ �θ� ������ ã�� �Լ�
void merge(int set[], int a, int b);	//�θ� ������ ���� ���ִ� �Լ�
void kruskal(int n,Data data[], int *F);	//ũ�罺Į �˰����� ����


int main()
{
	Data data[13];		//�������� ���� ���¸� �������ִ� ����ü �迭�� ����
	int F[12]; // ���õ� ������ ������ �迭�� ���� 
	create(&data[0], 1, 2, 32);		//�׷����� ���� ���¸� ����
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
	printf("\n**************kruskal �˰����� �����մϴ�**************\n\n");
	printf("�׷����� ������� ���� �κ��� ���Ѵ� �����μ� ���Ƿ� 100�� ������ ����\n\n");
	quicksort(0, 12, data);		//�������� ����ġ ������� ������������ ����
	kruskal(NUM,data, F);
	return 0;
}

/*����ü�� �����͸� �־��ִ� �Լ�*/
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

	//�Ǻ��� �����ϰ��� �ϴ� �迭�� ù �κ����� ����
	pivotitem = data[low].edge;
	//�Ǻ����� ���� �����Ͱ� ���� ��� �ڸ��� �ٲ��ֱ� ����
	//��ġ�� ��� ���� ������ ����
	j = low;
	//�Ǻ����� ���� ���� �����ͺ��� �迭�� �� �κ� ������ ������ ������ ����
	for (i = low + 1; i <= high; i++)
	{
		//���� �ش� �����Ͱ� �Ǻ� �����ۺ��� ���� ��� ��ġ�� �� �κ����� �ű�
		if (data[i].edge < pivotitem)
		{
			j++;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	//������ �� ��ġ�� �� �Ŀ� �ش� �Ǻ��� �Ǻ�����
	//���� �����Ϳ� ū ������ ���̿� ��ġ��Ŵ
	*pivotpoint = j;
	temp = data[low];
	data[low] = data[*pivotpoint];
	data[*pivotpoint] = temp;
}


/*���� �����Լ�(������ ������������ �����ϱ� ���Ͽ� ���)*/
void quicksort(int low, int high, Data data[13])
{
	//�Ǻ� ������ ���� ������ ����
	int pivotpoint = 0;

	if (high > low)
	{
		//�ش� �迭�� ���Ͽ� �� ���� ���� �Ǻ� ����Ʈ�� ���ϰ�
		//������ �� ��ģ����
		//�Ǻ��� �� ���� �ش� �ڸ��� �־��ش�
		partition(low, high, &pivotpoint, data);
		//ó���κп��� �Ǻ��� �� �κб����� �ٽ� ���� ���ķ� ���� 
		quicksort(low, pivotpoint - 1,data);
		//�Ǻ��� ���� �κк��� �� �κб��� �ٽ� ���� ���ķ� ����
		quicksort(pivotpoint + 1, high,data);
	}
}
/*������ ������ �� ��ȯ��ΰ� �߻����� �ʵ��� ������ ��������
�θ� ������ ������ ������ �� �ش�*/

/*�ش� ������ �θ� ������ ã�� �Լ�*/
int find(int parent[], int r)
{
	if (parent[r] == r) return r;
	return parent[r] = find(parent, parent[r]);
}

/*�θ� ������ ���� ���ִ� �Լ�*/
void merge(int set[], int a, int b)
{
	a = find(set, a);
	b = find(set, b);
	if (a < b) set[b] = a;
	else set[a] = b;
}

/*ũ�罺Į �˰����� ����*/
void kruskal(int m,Data data[], int *F)
{
	int i, j;	//�ش� ������ �ε����� ������ ����
	int p, q; // �ش� ������ �θ� ������ ����
	int k,n;	//�ݺ��� ���� ������ ���� 
	int l = 0;	//������ ������ �迭�� ���� ������ ����
	int count = 0;	//�������� ������ ������ ���� 
	int dcount = 0; //���� �����Ϳ� �����ϱ� ���� ������ ����
	int e;	//������ ������ ������ ����
	int parent[NUM] = { 0, };  //����Ǿ��ִ� ������ �θ� ������ ã�� ���� �迭�� ����
	int R[NUM][NUM];		//MST�� ������ �迭�� ���� 
	int sum = 0;	//�ּ� ��� ����Ʈ������ ����� �� 

	
	/*F�迭�� �ʱ�ȭ �۾�*/
	for (k = 0; k <= m; k++)
	{
		F[k] = 0;
	}

	/*���� �Ǿ��ִ� �θ� ��Ÿ���� �迭�� �ʱ�ȭ �ϴ� �۾�*/
	for (k = 1; k <= m-1; k++)
	{
		parent[k] = k;
	}

	/*�迭 R�� �ʱ�ȭ �۾�*/
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
		/*������ ������ �������� ������ ������ �����Ͽ� ����ÿ� ��ȯ ��ΰ� �ִ��� Ȯ���� �ִ� �۾�*/
		e = data[dcount].edge;	//��������
		i = data[dcount].node1;	//����1����
		j = data[dcount].node2;	//����2����

		p = find(parent, i);	//����1�� �θ� ������ ã��
		q = find(parent, j);	//����2�� �θ� ������ ã��

		if (p != q)	//���� ���սÿ� ��ȯ ��ΰ� �������� �ʴ´ٸ�
		{
			merge(parent, i, j); //�θ� ������ ���� �� �� 
			F[l] = e;	//���� �迭�� ������ ����
			count++;
			l++;
			R[i][j] = e;	//MST�� ������ ����
			R[j][i] = e;
			sum += e;
		}
		dcount++;
	}

	printf("���� ����� ������ ������ �����ϴ�->");
	for (k = 0; k < m-2; k++)
	{
		printf("%d ", F[k]);
	}
	printf("\n\n");

	printf("�ּ� ��� ���� Ʈ�������� ���� ����ġ�� �� -> %d\n", sum);

	printf("\nkruskal Algorithm�� ����Ͽ� MST�� ����մϴ�(������ķ� ǥ��)\n");
	for (k = 1; k <= m-1; k++)
	{
		for (n = 1; n <= m-1; n++)
		{
			printf("%3d ", R[k][n]);
		}
		printf("\n");
	}

}

