#include "LinkedList_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int *buff;// 병합 정렬을 위한 임시 저장 배열의 선언
Dnode *cur;// 리스트 탐색을 위한 커서 설정

/*이중 연결리스트의 생성 및 초기화*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
int list_create(Dlist *dlp)
{
	int node_count;
	int i;
	srand((int)time(NULL));
	/*머리 부분의 노드의 생성*/
	dlp->head = (Dnode*)malloc(sizeof(Dnode));
	if (dlp->head == NULL)
	{
		return 0;
	}
	/*꼬리 부분의 노드의 생성*/
	dlp->tail = (Dnode*)malloc(sizeof(Dnode));
	if (dlp->tail == NULL)
	{
		return 0;
	}
	dlp->head->next = dlp->tail;
	dlp->head->prev = NULL;
	dlp->tail->next = NULL;
	dlp->tail->prev = dlp->head;

	printf("노드의 생성 개수를 입력해 주세요:");
	scanf("%d", &node_count);

	for (i = 0; i < node_count; i++)
	{
		list_insert_head(dlp, rand());
	}

	return 1;

}

/*총 노드의 개수를 반환*/
int list_cnt(Dlist *dlp)
{
	return dlp->size;
}

/*리스트 시작에 노드 삽입*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
int list_insert_head(Dlist *dlp,int data)
{
	Dnode *dnp; // 새로운 노드의 생성
	dnp = (Dnode*)malloc(sizeof(Dnode));
	if (dnp == NULL)
	{
		return 0;
	}

	/*노드의 머리 부분의 다음 노드는 새 노드이고 새노드의 다음 노드는 머리의 다음 노드이다.*/
	dnp->data = data;
	dnp->next = dlp->head->next;
	dnp->prev = dlp->head;
	dlp->head->next->prev = dnp;
	dlp->head->next = dnp;
	dlp->size++;

	return 1;
}

/*리스트 끝에 노드 삽입*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
int list_insert_tail(Dlist *dlp, int data)
{
	Dnode *dnp;//새로운 노드의 생성
	dnp = (Dnode*)malloc(sizeof(Dnode));
	if (dnp == NULL)
	{
		return 0;
	}

	/*노드의 꼬리 부분의 이전 노드는 새 노드이고 새 노드의 이전 노드는 꼬리의 이전 노드이다.*/
	dnp->data = data;
	dnp->next = dlp->tail;
	dnp->prev = dlp->tail->prev;
	dlp->tail->prev->next = dnp;
	dlp->tail->prev = dnp;
	dlp->size++;

	return 1;
}

/*인덱스 위치에 노드 삽입*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
int list_insert_index(Dlist *dlp, int data, int index)
{
	Dnode *dnp;//새로운 노드의 생성
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
	/*index의 위치에 커서를 놓기*/
	while (count <= index)
	{
		cur = cur->next;
		count++;
	}

	/*해당 인덱스에 커서를 놓은 다음 이전 노드이 다음 부분과 다음 부분의 이전 노드가 새 노드가 되도록 해준다*/
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

/*리스트 시작에 있는 노드를 삭제*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*리스트 끝에 있는 노드를 삭제*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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
/*데이터에 대한 노드 삭제*/
/*성공 - 1을 리턴, 실패 - 0 을 리턴*/
/*같은 데이터가 리스트에 있을 시에는 맨 앞에 있는 노드를 삭제*/
int list_delete_data(Dlist *dlp, int data)
{
	int count = 0;
	cur = (Dnode*)malloc(sizeof(Dnode));
	if (cur == NULL)
	{
		return 0;
	}
	cur = dlp->head->next;
	//해당 데이터까지 커서를 옮김
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
		printf("해당 데이터는 존재하지 않습니다!\n");
		cur = NULL;
		free(cur);
		return 0;
	}
	return 1;
}

/*해당 인덱스에 있는 노드의 삭제*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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
		printf("해당 위치는 존재하지 않습니다.\n");
		cur = NULL;
		free(cur);
		return 0;
	}
	cur = dlp->head->next;
	//해당 인덱스까지 커서를 옮김
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

/*데이터에 대한 노드 탐색*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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
	//찾고자 하는 데이터까지 커서를 옮김
	while (count <= dlp->size)
	{
		if (cur->data == search)
		{
			printf("%d번 노드에 존재합니다!\n", count);
			i++;
		}
		cur = cur->next;
		count++;
	}

	if (i == 0)
	{
		printf("해당 데이터는 리스트에 존재하지 않습니다.\n");
		return 0;
	}
	cur = NULL;
	free(cur);
	return 1;
}

/*리스트 전체 삭제*/
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
/*리스트의 카피*/
Dlist* list_copy(Dlist *dlp)
{
	Dlist *cdlp = dlp;
	return cdlp;
}

/*Exchange Sort 함수의 구현*/
/*오름차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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
	//정렬 구현
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

/*Exchange Sort 함수의 구현*/
/*내림차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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
	//정렬구현
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


/*Exchange Sort를 이용한 오름차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_asc_excangeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = exchange_sort_asc(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}

/*Exchange Sort를 이용한 내림차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_dec_excangeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = exchange_sort_dec(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}

/*정렬을 위한 노드의 데이터를 배열로 옮기는 함수*/
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


/*배열 안에서의 MergeSort 구현(오름차순)*/
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

/*Merge sort함수의 구현*/
/*오름차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*배열 안에서의 MergeSort 구현(내림차순)*/
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

/*Merge sort함수의 구현*/
/*내림차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*mergeSort를 이용한 오름차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_asc_mergeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = merge_sort_asc(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}

/*mergeSort를 이용한 내림차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_dec_mergeSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = merge_sort_dec(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}

/*배열 안에서의 quickSort 구현(오름차순)*/
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

/*Quick sort함수의 구현*/
/*오름차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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

/*배열 안에서의 quickSort 구현(내림차순)*/
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

/*Quick sort함수의 구현*/
/*내림차순*/
/*성공 - 1을 반환, 실패 - 0을 반환*/
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


/*quickSort를 이용한 오름차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_asc_quickSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = quick_sort_asc(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}

/*quickSort를 이용한 내림차순 정렬*/
/*clock_t 를 이용하여 정렬에 걸린 시간을 프린트함*/
void list_sort_dec_quickSort(Dlist *dlp)
{
	clock_t start, end;
	int bres;
	start = clock();
	bres = quick_sort_dec(dlp);
	end = clock();
	printf("정렬시 걸린 시간%d\n", (int)(end - start));
	if (bres == 1)
		printf("@ 정렬 성공!\n");
	else
		printf("@ 정렬 실패!\n");
	return;
}


/*현재 리스트에 있는 노드들을 보여줌*/
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