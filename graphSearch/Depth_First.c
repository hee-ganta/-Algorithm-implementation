#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // �������� ���� 100���� ���� 
int promising(int i, int weight, int profit);
void knapsack(int i, int profit, int weight);//�賶 ä��� ���縦 �ذ��ϴ� �˰���(Depth_First)
void quicksort(int low, int high, double *S); //���Դ� ����ġ�� ������������ �迭
void partition(int low, int high, int *pivotpoint, double *S);

/*�ʿ��� �������� ���������� ����*/
int W;
int n; //�������� ������ ���� �� ����
int maxprofit = 0;
int numbest = 0;
int w[MAX] = { 0. }; //�������� ���Ը� ������ �迭
int p[MAX] = { 0, }; //�������� ����ġ�� ������ �迭
double pw[MAX] = { 0, }; //�������� ���Դ� ����ġ�� ������ �迭
int include[MAX] = { 0, };  //1�� ���̸� �ش� �������� �ִ´ٴ� ���̰� 0 �̸� �ش� �������� ���� �ʴ´ٴ� ���̴�.
int bestset[MAX] = { 0, };
int weight = 0;  //������� ���� �������� ����(�ʱ⿡�� ��� ���� �������� 0)
int profit = 0; //����� ���� �������� ����ġ(�ʱ⿡�� ��� ���� �������� 0)
int count = 1; // Ž���� ����� ���� ���ִ� ����

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

	printf("\n\n**********************Depth-First �˰����� ������ ����Դϴ�**********************\n\n");
	knapsack(0, weight, profit);
	printf("���� �� �ִ� �ִ� ����ġ�� %d�Դϴ�.\n", maxprofit);
	printf("���� �������� ������ ������ �����ϴ� ->");
	for (i = 1; i <= n; i++)
	{
		if (bestset[i] == 1)
		{
			printf("w%d ", i);
		}
	}
	printf("\n\n");
	printf("Ž���� ����� ���� %d�� �Դϴ�\n\n", count);
	return 0;
}

/*������ ������� �ƴ��� �Ǻ��� �� �ִ� �Լ�
�����ϸ� 1�� ��ȯ, �������� ������ 0�� ��ȯ*/
int promising(int i, int weight, int profit)
{
	int j;
	int totweight;
	double bound;

	if (weight >= W) //���� ������� ���԰� ä����� �ϴ� ���Ժ��� ũ�ٸ� �� ���� �������� �ʴ�
	{
		return 0;
	}
	else
	{
		j = i + 1; //Ʈ���� �ܰ踦 �ϳ� �÷� �ش�
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) // ���̰� n�� �ʰ��ϰų� ������ ���� �� �� �ִ� ������ �ʰ��ϸ� �ݺ��� ���� 
		{
			totweight = totweight + w[j]; //ä�� ���Ը� ���� 
			bound = bound + p[j]; //ä�� �����ۿ� ���� ����ġ�� ����
			j++;
		}
		if (j <= n)
		{
			bound = bound + (W - totweight) * (double)p[j] / (double)w[j]; // ���� �������� �� ä���� �ʾҴµ� ������ ���Ը� �ʰ��ߴٸ�
																		   // ���Դ� ����ġ�� ������ �������� �κ������� ä���� ����� ��밪�� ����
		}
		if (bound > maxprofit) // �� ����ġ�� ���� ���� �ִ� ����ġ ���� ũ�� �� ���� ����
			return 1;
		else
			return 0;

	}
}

/*�賶ä��� ������ �ذ��ϴ� �˰���*/
void knapsack(int i, int profit, int weight)
{
	int j;
	if (weight <= W && profit > maxprofit) //�賶���� ���԰� ä����� �ϴ� ���� ���� �۰� ���� ������ ���س��� �������� ũ�ٸ�
	{
		maxprofit = profit;
		numbest = i;
		for (j = 1; j <= n; j++)
		{
			bestset[j] = include[j]; //���� � �������� ��� �ִ� ��Ȳ������ ����
		}
	}

	if (promising(i, weight, profit)) //���� �ܰ迡�� ��尡 ���� �ϴٸ�
	{
		include[i + 1] = 1; //������ �������� �־��� ���� ���
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		count++;
		include[i + 1] = 0; //������ �������� ���� �ʾ��� ���� ���
		knapsack(i + 1, profit, weight);
		count++;

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