#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 100
/*Ʈ�� ��� �������� ����*/
typedef struct {
	char  key[10];
	double  p;
}Member;

/*Ʈ���� ���*/
typedef struct node {
	char key[10];
	struct node *left;
	struct node *right;
}nodetype;
typedef nodetype* node_pointer;	//��� ������ ����ü

Member key[MAX + 1];// �Է¹��� Ű ����� ����ü�� ����
double A[MAX + 1][MAX];//�ּ� ���� Ʈ�������� Ȯ���� �ּҰ��� ���� ����� ����
int R[MAX + 1][MAX];//�ּ� ���� Ʈ������ ��� �ε����� �Ѹ��� �� ���� �ּҰ� �Ǵ��� Ű���� ���� ����� ����
double p[MAX] = { 0, }; //�ּ� ���� Ʈ������ Ȯ���� ���� �迭�� ����
node_pointer root;//��Ʈ�� ����Ű�� �������� ����

void input_data(int n);    //Ʈ���� ���� ������ �����͸� �־��ִ� �Լ�
double iSum(int i, int j);  //i���� j������ Ȯ���� ������ ���� ��ȯ�ϴ� �Լ�
void optsearchtree(int n, double p[], double A[][MAX], double *minavg, int R[][MAX]);  //��� A�� ��� R�� ���ϴ� �˰���
int minimum(int i, int j, int k);  //�ּҰ��� ��ȯ���ִ� �Լ��� ����(�ּ� ���� Ʈ������ ���)
void make_root(int n);  //��Ʈ�� �������ִ� �Լ�
node_pointer tree(int i, int j); //���� ���� Ž�� Ʈ���� �����ϴ� �Լ�
void print_root();    //���� ���� Ž�� Ʈ�� ��Ʈ�� ���
void print_tree(node_pointer root); //���� ǥ������� Ʈ���� ������ ǥ��

int main()
{
	int num = 0;
	double minavg = 0.0;
	printf("***********���� �̺а˻�Ʈ���� �۾��� �����ϰڽ��ϴ�***********\n");
	printf("�Է¹��� Ű�� ������ �Է��� �ּ���: ");
	scanf("%d", &num);
	input_data(num);
	optsearchtree(num, p, A, &minavg, R);
	printf("�ּ� ��հ˻� �ð� -> %.3lf\n\n", minavg);
	make_root(num);
	print_root();
	printf("���� �̺а˻� Ʈ���� ���(���� ǥ���) -> ");
	print_tree(root);
	printf("\n");
	return 0;
}

/*Ʈ���� ���� ������ �����͸� �־��ִ� �Լ�*/
void input_data(int num)
{
	int i;
	double per = 0.0;
	char name[20];
	/*Ʈ�� ��� �������� �Է�*/
	for (i = 1; i <= num; i++)
	{
		printf("--------------------------\n");
		printf("Ű���� �Է��ϼ��� : ");
		scanf("%s", name);
		strcpy(key[i].key, name);
		printf("Ȯ���� �Է��ϼ��� : ");
		scanf("%lf", &per);
		key[i].p = per;
	}
	printf("\n");
	/*��� �����Ϳ� ��� �ִ� Ȯ���� �迭�� ����*/
	for (i = 1; i <= num; i++)
	{
		p[i] = key[i].p;
	}
}

/*�ּҰ��� ��ȯ���ִ� �Լ��� ����(�ּ� ���� Ʈ������ ���)*/
int minimum(int i, int j, int k)
{
	/*���� ��ľȿ� �ʱ�ȭ �Ǿ� �������� ù��° �� ����� ��Ŀ� �־��ش�.*/
	if (k == i)
	{
		/*k�� ��Ʈ���ٰ� �ΰ� Ȯ���� ���Ͽ������� ��Ͱ�����̴�.*/
		A[i][j] = A[i][k - 1] + A[k + 1][j] + iSum(i, j);
		/*�̶��� k���� ��ȯ */
		return k;
	}

	if (k != i)
	{
		/*���� ���ο� k�� �߽����� �ɰ��� ������ ���� �Ͽ����� �� ���� �� ������ ������ ���� �����Ͽ� �ش�.*/
		if (A[i][j] >A[i][k - 1] + A[k + 1][j] + iSum(i, j))
		{
			/*k�� ��Ʈ���ٰ� �ΰ� Ȯ���� ���Ͽ������� ��Ͱ�����̴�.*/
			A[i][j] = A[i][k - 1] + A[k + 1][j] + iSum(i, j);
			/*�̶��� k���� ��ȯ */
			return k;
		}
	}
	return R[i][j];  //k�϶� �ش����� ������ ������ ���� ����
}

/*i���� j������ Ȯ���� ������ ���� ��ȯ�ϴ� �Լ�*/
double iSum(int i, int j)
{
	double sum = 0;
	int k;

	/*�ε��� i���� j������ �� ���ϱ�*/
	for (k = i; k <= j; k++)
	{
		sum += key[k].p;
	}
	return sum;
}

/*��� A�� ��� R�� ���ϴ� �˰���*/
void optsearchtree(int n, double p[], double A[][MAX], double *minavg, int R[][MAX])
{
	int i, j, k, diagonal,knum;
	/*�迭 A�� �迭 D�� �ʱ�ȭ �۾�*/
	for (i = 0; i <= n; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}

	A[n + 1][n] = 0;
	R[n + 1][n] = 0;
	/*�밢���� ������� Ȯ���� ���� ��ȹ������ ����*/
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;
			for (k = i; k <= j; k++)
			{
				knum = minimum(i, j, k);
				R[i][j] = knum;    //k�� ��Ʈ�̸� ���� �����ϰ� �׷��� ������ ������ ���� �����Ѵ�.
			}
		}
	}
	*minavg = A[1][n]; //key1���� keyn���� �ּ� ���� Ʈ���� ����µ� �ּ� Ȯ���� ��갪

	/*��� A�� ���*/
	printf("\n--------------------------------\n");
	printf("���� �̺а˻�Ʈ�� �˰��� ���A ���ϱ�!\n");
	for (i = 1; i <= n+1; i++)
	{
		for (j = 0; j <= n; j++)
		{
			printf("%.3lf ", A[i][j]);
		}
		printf("\n");
	}

	/*���R�� ���*/
	printf("\n--------------------------------\n");
	printf("���� �̺а˻�Ʈ�� �˰��� ���R ���ϱ�!\n");
	for (i = 1; i <= n + 1; i++)
	{
		for (j = 0; j <= n; j++)
		{
			printf("%2d ", R[i][j]);
		}
		printf("\n");
	}
}

/*��Ʈ�� �������ִ� �Լ�*/
void make_root(int n)
{
	root = tree(1, n); // n�� ����� �����̴�.
}

/*���� ���� Ž�� Ʈ���� �����ϴ� �Լ�*/
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
		p = (node_pointer)malloc(sizeof(nodetype)); //���ο� ��� ������ ���� �޸� �Ҵ�
		strcpy(p->key, key[k].key);                 //key ���� ���� ����
		p->left = tree(i, k - 1);                   //���� ���� Ʈ���� ����
		p->right = tree(k + 1, j);                  //������ ���� Ʈ���� ����
		return p;                                   //����� ������ ��ȯ
	}
}

/*���� ���� Ž�� Ʈ�� ��Ʈ�� ���*/
void print_root()
{
	node_pointer p;
	p = root;
	printf("���� ���� Ž�� Ʈ�� �ֻ��� ���->%s\n", p->key);
}

/*���� ǥ������� Ʈ���� ������ ǥ��*/
void print_tree(node_pointer root)
{
	if (root != NULL)
	{
		print_tree(root->left);
		printf(" %s ", root->key);
		print_tree(root->right);
	}
}