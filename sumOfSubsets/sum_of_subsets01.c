#include <stdio.h>

int promising(int i, int weight, int total);		//������ ��带 �Ǻ��ϱ� ���� �Լ�
void sum_of_subsets(int i, int weight, int total);		//�κ������� �� ���ϴ� �˰����� ����

 /*���� 13�� ���� ������ ���� ����*/
int w[7] = { 0,2,10,13,17,22,42 };		//������ ����
int W = 52;		// ���� �Ǵ� ����
int n = 6;		//������ ����
int include[7] = { 0, }; // w[i]�� �����ϴ��� ���ϴ����� ����
int total = 0; // ���� �������� �� ���Ը� �����ϴ� ����
int weight = 0;		// ���� i�� ��������� ���Ե� ������ ��


int main()
{
	int i;

	/*ó�� total�� �ʱⰪ�� ��� ������ �հ� ����*/
	for (i = 1; i < 7; i++)
	{
		total += w[i];
	}

	printf("\n******************�κ������� �� ���ϱ� �˰����� �����մϴ�.******************\n\n");
	printf("******************���� 14�� ���� ����Դϴ�******************\n\n");
	printf("���� ������ ���� ���� ����մϴ�\n\n");
	sum_of_subsets(0, weight, total);
	printf("\n");
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

/*�κ������� �� ���ϴ� �˰����� ����*/
void sum_of_subsets(int i, int weight, int total)
{
	int j;
	if (promising(i, weight, total)) //�����ϸ� ���� �۾��� ����
	{
		printf("Ʈ������ : %d, weight : %d, total : %d\n", i, weight, total);
		if (weight == W)	//���ϰ��� �ϴ� ���Ը� ä��� ����� ����
		{
			printf("\nW�� �����ϴ� ������ ������ �����ϴ� ->");
			for (j = 1; j <= 6; j++)
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
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;		//w[i+1]�� �������� �ʴ� ���
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}

