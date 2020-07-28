#pragma once

/*노드 구조체*/
typedef struct d_node {
	int data;
	struct d_node *prev;
	struct d_node *next;
}Dnode;

/*이중 링크드리스트 관리 구조체*/
typedef struct d_list {
	Dnode *head;
	Dnode *tail;
	int size;
}Dlist;


/*연결 리스트 초기화*/
int list_create(Dlist *dlp);

/*총 노드의 개수를 리턴*/
int list_cnt(Dlist *dlp);

/*리스트 시작에 노드 삽입*/
int list_insert_head(Dlist *dlp, int data);

/*리스트 끝에 노드 삽입*/
int list_inset_tail(Dlist *dlp, int data);

/*인덱스 위치에 노드 삽입*/
int list_insert_index(Dlist *dlp, int data, int index);

/*리스트 시작에 대한 노드 삭제*/
int list_delete_head(Dlist *dlp);

/*리스트 끝에 대한 노드 삭제*/
int list_delete_tail(Dlist *dlp);

/*데이터에 대한 노드 삭제*/
int list_delete_data(Dlist *dlp,int data);

/*인덱스에 대한 노드 삭제*/
int list_delete_index(Dlist *dlp, int index);

/*데이터에 대한 노드 탐색*/
int list_search_data(Dlist *dlp, int search);

/*리스트 전체 삭제*/
void list_clear(Dlist *dlp);

/*리스트 카피*/
Dlist* list_copy(Dlist *dlp);

/*리스트의 출력*/
void list_display(Dlist *dlp);

/*오름차순 정렬(Exchange)*/
void list_sort_asc_excangeSort(Dlist *dlp);

/*내림차순 정렬(Exchange)*/
void list_sort_dec_excangeSort(Dlist *dlp);

/*오름차순 정렬(Merge)*/
void list_sort_asc_mergeSort(Dlist *dlp);

/*내림차순 정렬(Merge)*/
void list_sort_dec_mergeSort(Dlist *dlp);

/*오른차순 정렬(Quick)*/
void list_sort_asc_quickSort(Dlist *dlp);

/*내림차순 정렬(Quick)*/
void list_sort_dec_quickSort(Dlist *dlp);


