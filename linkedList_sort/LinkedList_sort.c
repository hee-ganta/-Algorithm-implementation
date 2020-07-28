#include "LinkedList_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int *buff;// ���� ������ ���� �ӽ� ���� �迭�� ����
Dnode *cur;// ����Ʈ Ž���� ���� Ŀ�� ����

/*���� ���Ḯ��Ʈ�� ���� �� �ʱ�ȭ*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_create(Dlist *dlp)
{
	int node_count;
	int i;
	srand((int)time(NULL));
	/*�Ӹ� �κ��� ����� ����*/
	dlp->head = (Dnode*)malloc(sizeof(Dnode));
	if (dlp->head == NULL)
	{
		return 0;
	}
	/*���� �κ��� ����� ����*/
	dlp->tail = (Dnode*)malloc(sizeof(Dnode));
	if (dlp->tail == NULL)
	{
		return 0;
	}
	dlp->head->next = dlp->tail;
	dlp->head->prev = NULL;
	dlp->tail->next = NULL;
	dlp->tail->prev = dlp->head;

	printf("����� ���� ������ �Է��� �ּ���:");
	scanf("%d", &node_count);

	for (i = 0; i < node_count; i++)
	{
		list_insert_head(dlp, rand());
	}

	return 1;

}

/*�� ����� ������ ��ȯ*/
int list_cnt(Dlist *dlp)
{
	return dlp->size;
}

/*����Ʈ ���ۿ� ��� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_insert_head(Dlist *dlp,int data)
{
	Dnode *dnp; // ���ο� ����� ����
	dnp = (Dnode*)malloc(sizeof(Dnode));
	if (dnp == NULL)
	{
		return 0;
	}

	/*����� �Ӹ� �κ��� ���� ���� �� ����̰� ������� ���� ���� �Ӹ��� ���� ����̴�.*/
	dnp->data = data;
	dnp->next = dlp->head->next;
	dnp->prev = dlp->head;
	dlp->head->next->prev = dnp;
	dlp->head->next = dnp;
	dlp->size++;

	return 1;
}

/*����Ʈ ���� ��� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_insert_tail(Dlist *dlp, int data)
{
	Dnode *dnp;//���ο� ����� ����
	dnp = (Dnode*)malloc(sizeof(Dnode));
	if (dnp == NULL)
	{
		return 0;
	}

	/*����� ���� �κ��� ���� ���� �� ����̰� �� ����� ���� ���� ������ ���� ����̴�.*/
	dnp->data = data;
	dnp->next = dlp->tail;
	dnp->prev = dlp->tail->prev;
	dlp->tail->prev->next = dnp;
	dlp->tail->prev = dnp;
	dlp->size++;

	return 1;
}

/*�ε��� ��ġ�� ��� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_insert_index(Dlist *dlp, int data, int index)
{
	Dnode *dnp;//���ο� ����� ����
	int count=2;
	dnp = (Dnode*)malloc(sizeof(Dnode));
	if (dnp == NULL)
	{
		return 0;
	}
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}

	if (dlp->size < index)
	{
		return 0;
	}

	cur = dlp->head->next;
	/*index�� ��ġ�� Ŀ���� ����*/
	while (count <= index)
	{
		cur = cur->next;
		count++;
	}

	/*�ش� �ε����� Ŀ���� ���� ���� ���� ����� ���� �κа� ���� �κ��� ���� ��尡 �� ��尡 �ǵ��� ���ش�*/
	dnp->data = data;
	dnp->prev = cur->prev;
	dnp->next = cur;
	cur->prev->next = dnp;
	cur->prev = dnp;

	dlp->size++;
	cur = NULL;
	free(cur);
	return 1;
}

/*����Ʈ ���ۿ� �ִ� ��带 ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_delete_head(Dlist *dlp)
{
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->head->next;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur);
	dlp->size--;
	return 1;
}

/*����Ʈ ���� �ִ� ��带 ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_delete_tail(Dlist *dlp)
{
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->tail->prev;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur);
	dlp->size--;
	return 1;
}
/*�����Ϳ� ���� ��� ����*/
/*���� - 1�� ����, ���� - 0 �� ����*/
/*���� �����Ͱ� ����Ʈ�� ���� �ÿ��� �� �տ� �ִ� ��带 ����*/
int list_delete_data(Dlist *dlp, int data)
{
	int count = 0;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->head->next;
	//�ش� �����ͱ��� Ŀ���� �ű�
	while (count <= dlp->size)
	{
		if (cur->data == data)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			dlp->size--;
			break;
		}
		count++;
		cur = cur->next;
	}

	if (count == dlp->size + 1)
	{
		printf("�ش� �����ʹ� �������� �ʽ��ϴ�!\n");
		cur = NULL;
		free(cur);
		return 0;
	}
	return 1;
}

/*�ش� �ε����� �ִ� ����� ����*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_delete_index(Dlist *dlp, int index)
{
	int count = 1;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	if (index > dlp->size)
	{
		printf("�ش� ��ġ�� �������� �ʽ��ϴ�.\n");
		cur = NULL;
		free(cur);
		return 0;
	}
	cur = dlp->head->next;
	//�ش� �ε������� Ŀ���� �ű�
	while (count < index)
	{
		cur = cur->next;
		count++;
	}
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur);
	dlp->size--;

	return 1;
}

/*�����Ϳ� ���� ��� Ž��*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int list_search_data(Dlist *dlp, int search)
{
	int count = 1;
	int i = 0;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->head->next;
	//ã���� �ϴ� �����ͱ��� Ŀ���� �ű�
	while (count <= dlp->size)
	{
		if (cur->data == search)
		{
			printf("%d�� ��忡 �����մϴ�!\n", count);
			i++;
		}
		cur = cur->next;
		count++;
	}

	if (i == 0)
	{
		printf("�ش� �����ʹ� ����Ʈ�� �������� �ʽ��ϴ�.\n");
		return 0;
	}
	cur = NULL;
	free(cur);
	return 1;
}

/*����Ʈ ��ü ����*/
void list_clear(Dlist *dlp)
{
	int count = 1;
	while (count <= dlp->size)
	{
		list_delete_head(dlp);
	}
	free(dlp->head);
	free(dlp->tail);
	dlp->size = 0;

	return;

}
/*����Ʈ�� ī��*/
Dlist* list_copy(Dlist *dlp)
{
	Dlist *cdlp = dlp;
	return cdlp;
}

/*Exchange Sort �Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int exchange_sort_asc(Dlist *dlp)
{
	Dnode *mCur;
	int i,j,temp;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	mCur = (Dnode*)malloc(sizeof(Dnode));
	if (mCur == NULL)
	{
		return 0;
	}

	cur = dlp->head->next;
	//���� ����
	for (i = 1; i <= dlp->size-1; i++)
	{
		mCur = cur->next;
		for (j = i + 1; j <= dlp->size; j++)
		{
			if (cur->data > mCur->data)
			{
				temp = cur->data;
				cur->data = mCur->data;
				mCur->data = temp;
			}
			mCur = mCur->next;
		}
		cur = cur->next;
	}
	mCur = NULL;
	cur = NULL;
	free(mCur);
	free(cur);
	return 1;
}

/*Exchange Sort �Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int exchange_sort_dec(Dlist *dlp)
{
	Dnode *mCur;
	int i, j, temp;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	mCur = (Dnode*)malloc(sizeof(Dnode));
	if (mCur == NULL)
	{
		return 0;
	}

	cur = dlp->head->next;
	//���ı���
	for (i = 1; i <= dlp->size - 1; i++)
	{
		mCur = cur->next;
		for (j = i + 1; j <= dlp->size; j++)
		{
			if (cur->data < mCur->data)
			{
				temp = cur->data;
				cur->data = mCur->data;
				mCur->data = temp;
			}
			mCur = mCur->next;
		}
		cur = cur->next;
	}
	mCur = NULL;
	cur = NULL;
	free(mCur);
	free(cur);
	return 1;
}


/*Exchange Sort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_asc_excangeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = exchange_sort_asc(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}

/*Exchange Sort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_dec_excangeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = exchange_sort_dec(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}

/*������ ���� ����� �����͸� �迭�� �ű�� �Լ�*/
int array(Dlist *dlp, int *arr)
{
	int i;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->head->next;
	for (i = 0; i < dlp->size; i++)
	{
		arr[i] = cur->data;
		cur = cur->next;
	}
	cur = NULL;
	free(cur);
	return 1;
}


/*�迭 �ȿ����� MergeSort ����(��������)*/
void merge_sort_a(int a[],int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		int p = 0;
		int i;
		int j = 0;
		int k = left;
		merge_sort_a(a, left, mid);
		merge_sort_a(a, mid+1, right);
		for (i = left; i <= mid; i++)
		{
			buff[p++] = a[i];
		}
		while (i <= right && j < p)
			a[k++] = (buff[j] <= a[i]) ? buff[j++] : a[i++];
		while (j < p)
			a[k++] = buff[j++];
	}
	return;
}

/*Merge sort�Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int merge_sort_asc(Dlist *dlp)
{
	Dnode *mCur;
	int *arr;
	int i;
	mCur = (Dnode*)malloc(sizeof(Dnode));
	if (mCur == NULL)
	{
		return 0;
	}
	buff = calloc(dlp->size, sizeof(int));
	if (buff == NULL)
	{
		return 0;
	}
	arr = calloc(dlp->size, sizeof(int));
	if (arr == NULL)
	{
		return 0;
	}
	mCur = dlp->head->next;
	if (array(dlp, arr) == 0)
	{
		return 0;
	}
	merge_sort_a(arr, 0, dlp->size - 1,buff);
	for (i = 0; i < dlp->size; i++)
	{
		mCur->data = arr[i];
		mCur = mCur->next;
	}
	free(buff);
	free(arr);
	mCur = NULL;
	free(mCur);

	return 1;
}

/*�迭 �ȿ����� MergeSort ����(��������)*/
void merge_sort_d(int a[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		int p = 0;
		int i;
		int j = 0;
		int k = left;
		merge_sort_d(a, left, mid);
		merge_sort_d(a, mid + 1, right);
		for (i = left; i <= mid; i++)
		{
			buff[p++] = a[i];
		}
		while (i <= right && j < p)
			a[k++] = (buff[j] >= a[i]) ? buff[j++] : a[i++];
		while (j < p)
			a[k++] = buff[j++];
	}
	return;
}

/*Merge sort�Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int merge_sort_dec(Dlist *dlp)
{
	Dnode *mCur;
	int *arr;
	int i;
	mCur = (Dnode*)malloc(sizeof(Dnode));
	if (mCur == NULL)
	{
		return 0;
	}
	buff = calloc(dlp->size, sizeof(int));
	if (buff == NULL)
	{
		return 0;
	}
	arr = calloc(dlp->size, sizeof(int));
	if (arr == NULL)
	{
		return 0;
	}
	mCur = dlp->head->next;
	if (array(dlp, arr) == 0)
	{
		return 0;
	}
	merge_sort_d(arr, 0, dlp->size - 1, buff);
	for (i = 0; i < dlp->size; i++)
	{
		mCur->data = arr[i];
		mCur = mCur->next;
	}
	free(buff);
	free(arr);
	mCur = NULL;
	free(mCur);

	return 1;
}

/*mergeSort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_asc_mergeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = merge_sort_asc(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}

/*mergeSort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_dec_mergeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = merge_sort_dec(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}

/*�迭 �ȿ����� quickSort ����(��������)*/
void quick_sort_a(int *arr, int left, int right)
{
	int pl = left;
	int pr = right;
	int x = arr[(pl + pr) / 2];
	int temp;

	do
	{
		while (arr[pl] < x) pl++;
		while (arr[pr] > x) pr--;
		if (pl <= pr)
		{
			temp = arr[pl];
			arr[pl] = arr[pr];
			arr[pr] = temp;
			pl++;
			pr--;
		}
	} while (pl <= pr);

	if (left < pr) quick_sort_a(arr, left, pr);
	if (pl < right) quick_sort_a(arr, pl, right);
}

/*Quick sort�Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int quick_sort_asc(Dlist *dlp)
{
	Dnode *qCur;
	int *arr;
	int i;
	arr = calloc(dlp->size, sizeof(int));
	if (arr == NULL)
	{
		return 0;
	}
	qCur = (Dnode*)malloc(sizeof(Dnode));
	if (qCur == NULL)
	{
		return 0;
	}
	qCur = dlp->head->next;
	if (array(dlp, arr) == 0)
	{
		return 0;
	}
	quick_sort_a(arr, 0, dlp->size - 1);
	for (i = 0; i < dlp->size; i++)
	{
		qCur->data = arr[i];
		qCur = qCur->next;
	}
	free(arr);
	qCur = NULL;
	free(qCur);
	return 1;
}

/*�迭 �ȿ����� quickSort ����(��������)*/
void quick_sort_d(int *arr, int left, int right)
{
	int pl = left;
	int pr = right;
	int x = arr[(pl + pr) / 2];
	int temp;

	do
	{
		while (arr[pl] > x) pl++;
		while (arr[pr] < x) pr--;
		if (pl <= pr)
		{
			temp = arr[pl];
			arr[pl] = arr[pr];
			arr[pr] = temp;
			pl++;
			pr--;
		}
	} while (pl <= pr);

	if (left < pr) quick_sort_d(arr, left, pr);
	if (pl < right) quick_sort_d(arr, pl, right);
}

/*Quick sort�Լ��� ����*/
/*��������*/
/*���� - 1�� ��ȯ, ���� - 0�� ��ȯ*/
int quick_sort_dec(Dlist *dlp)
{
	Dnode *qCur;
	int *arr;
	int i;
	arr = calloc(dlp->size, sizeof(int));
	if (arr == NULL)
	{
		return 0;
	}
	qCur = (Dnode*)malloc(sizeof(Dnode));
	if (qCur == NULL)
	{
		return 0;
	}
	qCur = dlp->head->next;
	if (array(dlp, arr) == 0)
	{
		return 0;
	}
	quick_sort_d(arr, 0, dlp->size - 1);
	for (i = 0; i < dlp->size; i++)
	{
		qCur->data = arr[i];
		qCur = qCur->next;
	}
	free(arr);
	qCur = NULL;
	free(qCur);
	return 1;
}


/*quickSort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_asc_quickSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = quick_sort_asc(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}

/*quickSort�� �̿��� �������� ����*/
/*clock_t �� �̿��Ͽ� ���Ŀ� �ɸ� �ð��� ����Ʈ��*/
void list_sort_dec_quickSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = quick_sort_dec(dlp);
	end = clock();
	printf("���Ľ� �ɸ� �ð�%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ ���� ����!\n");
	else
		printf("@ ���� ����!\n");
	return;
}


/*���� ����Ʈ�� �ִ� ������ ������*/
void list_display(Dlist *dlp)
{
	Dnode *dtp;
	dtp = dlp->head->next;
	while (dtp != dlp->tail) {
		printf("%d ", dtp->data);
		dtp = dtp->next;
	}
	printf("\n");
	return;
}