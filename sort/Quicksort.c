#include <stdio.h>
void quicksort(int low, int high);
void partition(int low, int high, int *pivotpoint);

//�����ϰ��� �ϴ� �迭�� ���������� �����Ѵ�.
int S3[8] = { 123,34,189,56,150,12,9,240 };

int main()
{
	int i;
	printf("�������� ���� ���� �迭�� ���� ����!\n");
	printf("--------------------------------\n");
	printf("���� �� �迭->");
	//�����ϱ��� �迭�� �����ش�
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");
	quicksort(0, 7);
	printf("�������� ������ �迭(quicksort) ->");
	//������ �迭�� �����ش�
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");

	return 0;
}

//���� ������ ����
void quicksort(int low, int high)
{
	//�Ǻ� ������ ���� ������ ����
	int pivotpoint = 0;

	if (high > low)
	{
		//�ش� �迭�� ���Ͽ� �� ���� ���� �Ǻ� ����Ʈ�� ���ϰ�
		//������ �� ��ģ����
		//�Ǻ��� �� ���� �ش� �ڸ��� �־��ش�
		partition(low, high, &pivotpoint);
		//ó���κп��� �Ǻ��� �� �κб����� �ٽ� ���� ���ķ� ���� 
		quicksort(low, pivotpoint - 1);
		//�Ǻ��� ���� �κк��� �� �κб��� �ٽ� ���� ���ķ� ����
		quicksort(pivotpoint + 1, high);
	}
}

void partition(int low, int high, int *pivotpoint)
{
	int i, j, temp;
	int pivotitem;

	//�Ǻ��� �����ϰ��� �ϴ� �迭�� ù �κ����� ����
	pivotitem = S3[low];
	//�Ǻ����� ���� �����Ͱ� ���� ��� �ڸ��� �ٲ��ֱ� ����
	//��ġ�� ��� ���� ������ ����
	j = low;
	//�Ǻ����� ���� ���� �����ͺ��� �迭�� �� �κ� ������ ������ ������ ����
	for (i = low + 1; i <= high; i++)
	{
		//���� �ش� �����Ͱ� �Ǻ� �����ۺ��� ���� ��� ��ġ�� �� �κ����� �ű�
		if (S3[i] < pivotitem)
		{
			j++;
			temp = S3[i];
			S3[i] = S3[j];
			S3[j] = temp;
		}
	}
	//������ �� ��ġ�� �� �Ŀ� �ش� �Ǻ��� �Ǻ�����
	//���� �����Ϳ� ū ������ ���̿� ��ġ��Ŵ
	*pivotpoint = j;
	temp = S3[low];
	S3[low] = S3[*pivotpoint];
	S3[*pivotpoint] = temp;
	//�����ϴ� ������ ������
	printf("������ ���� ->");
	for (i = 0; i <= 7; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");
}