#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int promising(int i, int weight, int total);	//������ ���� �Ǻ��ϱ� ���� �Լ�(������ ����)
void sum_of_subsets02(int i, int n, int weight, int total);	//�κ������� �� ���ϴ� �Լ�(������ ����)
void sum_of_subsets03(int i, int n, int weight, int total); //�κ������� �� ���ϴ� �Լ�(�ϳ��� �ش丸 ã��)
void quicksort(int low, int high, int *S);	//������ �Լ�
void partition(int low, int high, int *pivotpoint, int *S);

int W;
int n;
int *w;
int *include;
int total = 0; // ���� �������� �� ���Ը� �����ϴ� ����
int weight = 0;		// ���� i�� ��������� ���Ե� ������ ��
int count = 0;


int main()
{
	int i;
	clock_t start, end;

	printf("\n******************�κ������� �� ���ϱ� �˰����� �����մϴ�.******************\n\n");

	printf("�賶�� ������ �� �ִ� �ִ� ���԰��� �Է��� �ּ���:");
	scanf("%d", &W);
	printf("�������� ������ �Է��� �ּ���:");
	scanf("%d", &n);
	w = calloc(n + 1, sizeof(int));
	include = calloc(n + 1, sizeof(int));
	printf("�����۵��� ���Ը� �Է��� �ּ���:");
	for (i = 1; i < n + 1; i++)
	{
		scanf("%d", &w[i]);
	}
	for (i = 1; i < 7; i++)  // ó�� total�� �ʱⰪ�� ��� ������ �հ� ����
	{
		total += w[i];
	}
	quicksort(1, n, w); // �Է¹��� ���Ը� ������������ ����
	printf("������������ ������ �������� ����� ������ �����ϴ�\n");
	for (i = 1; i < n + 1; i++)
	{
		printf("w%d:%d	", i, w[i]);
	}
	printf("\n\n");
	printf("******************�κ����� �˰����� ������ ����Դϴ�******************\n\n");
	start = clock();
	sum_of_subsets02(0, n, weight, total);
	end = clock();
	printf("�ɸ� �ð��� %d �Դϴ�.\n\n", end - start);
	printf("******************���� 16�� ���� ����Դϴ�(�ϳ��� �ش丸 ����)******************\n\n");
	start = clock();
	sum_of_subsets03(0, n, weight, total);
	end = clock();
	printf("�ɸ� �ð��� %d �Դϴ�.\n\n", end - start);
	free(w);
	free(include);
	return 0;
}
/*������ ���� �Ǻ��ϱ� ���� �Լ�
���� ���̸� 1�� ��ȯ, ������ ���̸� 0�� ��ȯ�Ѵ�*/
int promising(int i, int weight, int total)
{
	/*������ �����ϸ� �������� ��ȯ������ �����ش�
	//������ ���Կ� ������ ������ ���� ä�� ������ �պ��� ũ��
	���� ���԰� ��� �����ϰų� Ȥ�� ���� ���Կ� ���� ������ ���� ä����� �ϴ� ���� ���� ������
	�������� �̿��Ѵ�.*/
	if ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*�κ������� �� ���ϴ� �Լ�(������ ����)*/
void sum_of_subsets02(int i, int n, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) /*�����ϸ� ���� �۾��� ����*/
	{
		/*���ϰ��� �ϴ� ���Ը� ä��� ����� ����*/
		if (weight == W)
		{
			printf("W�� �����ϴ� ������ ������ �����ϴ� ->");
			for (j = 1; j <= n; j++)
			{
				if (include[j] == 1)
				{
					printf("w%d ", j);
				}
			}
			printf("\n");
			printf("\n");
		}
		/*�׷��� ������ ���� ���Ը� �������� �������� �����Ͽ� ��������� �۾��� ����*/
		else
		{
			include[i + 1] = 1;		//w[i+1]�� �����ϴ� ���
			sum_of_subsets02(i + 1, n, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;		//w[i+1]�� �������� �ʴ� ���
			sum_of_subsets02(i + 1, n, weight, total - w[i + 1]);
		}
	}
}

/*�κ������� �� ���ϴ� �Լ�(�ϳ��� �ش丸 ã��)*/
void sum_of_subsets03(int i, int n, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) //�����ϸ� ���� �۾��� ����
	{
		if (weight == W)//���ϰ��� �ϴ� ���Ը� ä��� ����� ����
		{
			count++;
			printf("W�� �����ϴ� ������ ������ �����ϴ� ->");
			for (j = 1; j <= n; j++)
			{
				if (include[j] == 1)
				{
					printf("w%d ", j);
				}
			}
			printf("\n");
			printf("\n");
		}
		else //�׷��� ������ ���� ���Ը� �������� �������� �����Ͽ� ��������� �۾��� ����
		{
			if (count == 0)
			{
				include[i + 1] = 1;		//w[i+1]�� �����ϴ� ���
				sum_of_subsets03(i + 1, n, weight + w[i + 1], total - w[i + 1]);
				include[i + 1] = 0;		//w[i+1]�� �������� �ʴ� ���
				sum_of_subsets03(i + 1, n, weight, total - w[i + 1]);
			}
		}
	}
}

//�� ������ ����
void quicksort(int low, int high,int *S)
{
	//�Ǻ� ������ ���� ������ ����
	int pivotpoint = 0;

	if (high > low)
	{
		//�ش� �迭�� ���Ͽ� �� ���� ���� �Ǻ� ����Ʈ�� ���ϰ�
		//������ �� ��ģ����
		//�Ǻ��� �� ���� �ش� �ڸ��� �־��ش�
		partition(low, high, &pivotpoint,S);
		//ó���κп��� �Ǻ��� �� �κб����� �ٽ� ���� ���ķ� ���� 
		quicksort(low, pivotpoint - 1,S);
		//�Ǻ��� ���� �κк��� �� �κб��� �ٽ� ���� ���ķ� ����
		quicksort(pivotpoint + 1, high,S);
	}
}

void partition(int low, int high, int *pivotpoint, int *S)
{
	int i, j, temp;
	int pivotitem;

	//�Ǻ��� �����ϰ��� �ϴ� �迭�� ù �κ����� ����
	pivotitem = S[low];
	//�Ǻ����� ���� �����Ͱ� ���� ��� �ڸ��� �ٲ��ֱ� ����
	//��ġ�� ��� ���� ������ ����
	j = low;
	//�Ǻ����� ���� ���� �����ͺ��� �迭�� �� �κ� ������ ������ ������ ����
	for (i = low + 1; i <= high; i++)
	{
		//���� �ش� �����Ͱ� �Ǻ� �����ۺ��� ���� ��� ��ġ�� �� �κ����� �ű�
		if (S[i] < pivotitem)
		{
			j++;
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
	}
	//������ �� ��ġ�� �� �Ŀ� �ش� �Ǻ��� �Ǻ�����
	//���� �����Ϳ� ū ������ ���̿� ��ġ��Ŵ
	*pivotpoint = j;
	temp = S[low];
	S[low] = S[*pivotpoint];
	S[*pivotpoint] = temp;	
}

