#include <stdio.h>
#define  INF 100
#define MAX 100

void travel(int n, int W[][6], int P[][MAX], int* minlength); // ���ǿ� �˰����� �����ϴ� �Լ�
int ver_to_bin(int a);		//���D�� ��ﶧ �ش� �������� ���� ������ ǥ������� �ٲ��ֱ� ���� �Լ�
int bin(int a);			//������ �ְ� 1�� �� �ֿ� �ش� ���� �ڸ����� ����� �ִ� �ִ밪�� ���ϱ� ���� �Լ�
void print_path(int P[][MAX], int a, int b, int* n);	 //��θ� ����� �ֱ� ���� �Լ�
int city_count(int l, int n, int check[]);			//��� �������� ��ġ���� Ȯ���ϴ� �۾�


int main()
{
	int W[6][6] = { {0,0,0,0,0,0},{0,0,8,13,18,20},{0,3,0,7,8,10},{0,4,11,0,10,7},{0,6,6,7,0,11},{0,10,6,2,1,0} };
	int P[6][MAX] = { 0, }; // ��ο� ���� ������ ��� ���� �迭 ����
	int minlength = 0;		//�ִ� ��� ���̸� ��� ���� ������ ����
	int i, j;
	int totn = bin(5) - 2;

	/*�������� ���� ���¸� ���*/
	printf("�������� ���� ���¸� ����մϴ�\n");
	for (i = 1; i < 6; i++)
	{
		for (j = 1; j < 6; j++)
		{
			printf("%1d ", W[i][j]);
		}
		printf("\n\n");
	}
	travel(5, W, P, &minlength);

	printf("\n�ִ� ����� ���̴� %d �Դϴ�.\n\n", minlength);

	/*�������� ������ v1 �����̰� �������� �ִ� ��δ� print_path�Լ��� �̿��Ͽ� ���*/
	printf("�ִ� ��δ� ������ �����ϴ�.\n");
	printf("v1->");
	print_path(P, 1, bin(5) - 2, &totn);
	printf("v1\n");
	return 0;
}


/*���D�� ��ﶧ �ش� �������� ���� ������ ǥ������� �ٲ��ֱ� ���� �Լ�*/
int ver_to_bin(int a)
{
	int result = 1;
	int i;
	for (i = 0; i < a - 1; i++)
	{
		result = result * 2;
	}
	return result;
}

/*������ �ְ� 1�� �� �ֿ� �ش� ���� �ڸ����� ����� �ִ� �ִ밪�� ���ϱ� ���� �Լ�*/
int bin(int a)
{
	int result = 1;
	int i;
	for (i = 0; i < a; i++)
	{
		result = result * 2;
	}
	return result;
}


/*��� �������� ��ġ���� Ȯ���ϴ� �۾�(��Ʈ����ŷ ����� �̿�)*/
int city_count(int l, int n, int check[])
{
	int count = 0;		//���� ��� �������� ��ġ���� �����ϱ� ���� ����
	int j;


	for (j = 0; j < n; j++)
	{
		if (j == 0)		//ù��° �������� ī��Ʈ ���� �ʴ´�
		{
			if (l % 2 == 1)
			{
				check[j + 1] = 1;
			}
		}
		else		//�ι�° ���������ʹ� ī��Ʈ�� ���ش�
		{
			if (l % 2 == 1)
			{
				count++;
				check[j + 1] = 1;
			}
		}
		l = l >> 1;  //shiftright �۾� ����
	}

	return count;

}

/*���ǿ� �˰����� ����
 (�Է�)
  n -> �������� ����
  W -> �������� �������
  P -> �ּҰ� �Ǵ� ������ ����
  minlength -> �ּ� ���� ��ġ
  */

void travel(int n, int W[][6], int P[][MAX], int* minlength)
{
	int i, j, k, l;
	int D[6][MAX];
	int count = 0;
	int check[MAX] = { 0, }; // ���� ��� ���ø� ����ġ�� ��츦 ����ϴ��� �����ϴ� �迭 (1�̸� ����ġ�� ���, 0 �̸� �� ����ġ�� ���)

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			D[i][j] = INF;
		}
	}


	/*�� ���������� �ٷ� ���������� ���� ���*/
	for (i = 2; i <= 5; i++)
	{
		D[i][0] = W[i][1];
	}

	/*Traveling Sales Preson �˰��� ����*/
	/*������1�� ������ ������ ���������� �������� ���İ��� �������� ���������� ������1�� ���� ��츦 ���D�� �����ϴ� �˰���*/
	for (k = 1; k <= n - 2; k++) // ���İ��� �������� ������ n-2���� �ִ��̴�.
	{
		for (l = 1; l <= bin(n) - 1; l++)  //���� ���� ��� ����� ���� ���
		{
			count = city_count(l, n, check); //�ش� ���� ���� �������� ���� ���� 

			if (count == k)		//Ž���ϰ����ϴ� �������� ���� ��ġ�ϸ� ����� ����
			{
				for (i = 2; i <= n; i++)	//������1 ������ ������� ����
				{
					for (j = 2; j <= n; j++)
					{
						if ((check[1] != 1) && (check[i] != 1) && (check[j] == 1) && (D[i][l] > W[i][j] + D[j][l - ver_to_bin(j)]))
						{
							D[i][l] = W[i][j] + D[j][l - ver_to_bin(j)];	//�ּҰ��� ���� ������ ���� �����Ͽ� �迭�� ����
							P[i][l] = j;		//�̶��� ��θ� �迭�� ���� 			
						}
					}
				}
			}

			/*üũ �迭�� ���¸� �ʱ�ȭ �����ش�*/
			for (i = 0; i <= n; i++)
			{
				check[i] = 0;
			}

		}
	}

	/*�������� ������1�� �Ͽ� ��ȸ�ϴ� ��츦 ����*/
	for (j = 2; j <= n; j++)
	{
		if (D[1][bin(n) - 2] > W[1][j] + D[j][(bin(n) - 2) - ver_to_bin(j)])
		{
			D[1][bin(n) - 2] = W[1][j] + D[j][(bin(n) - 2) - ver_to_bin(j)];	//�ּҰ��� ���� ������ ���� �����Ͽ� �迭�� ���� 
			P[1][bin(n) - 2] = j;		//�̶��� ��θ� �迭�� ����
			*minlength = D[1][bin(n) - 2];  //�ּ� ����� ���̸� �迭�� ���� 
		}
	}


	/*��� D�� ���*/
	printf("D����� ����մϴ�\n\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < bin(n) - 1; j++)
		{
			printf("%3d ", D[i][j]);
		}
		printf("\n");
	}

	/*��� P�� ���*/
	printf("\n\nP����� ����մϴ�\n\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < bin(n) - 1; j++)
		{
			printf("%3d ", P[i][j]);
		}
		printf("\n");
	}
}


/*��θ� ����� �ֱ� ���� �Լ�*/
void print_path(int P[][MAX], int a, int b, int* n)
{
	if (*n == 0)	//��� ��θ� ���������� ��� �Լ��� Ż��
	{
		return;
	}
	else	//��� �Լ��� ���Ͽ� ��θ� ��� 
	{
		printf("v%d->", P[a][b]);
		*n = *n - ver_to_bin(P[a][b]);
		print_path(P, P[a][b], *n, n);
	}
}
