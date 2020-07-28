#pragma once

/*��� ����ü*/
typedef struct d_node {
	int data;
	struct d_node *prev;
	struct d_node *next;
}Dnode;

/*���� ��ũ�帮��Ʈ ���� ����ü*/
typedef struct d_list {
	Dnode *head;
	Dnode *tail;
	int size;
}Dlist;


/*���� ����Ʈ �ʱ�ȭ*/
int list_create(Dlist *dlp);

/*�� ����� ������ ����*/
int list_cnt(Dlist *dlp);

/*����Ʈ ���ۿ� ��� ����*/
int list_insert_head(Dlist *dlp, int data);

/*����Ʈ ���� ��� ����*/
int list_inset_tail(Dlist *dlp, int data);

/*�ε��� ��ġ�� ��� ����*/
int list_insert_index(Dlist *dlp, int data, int index);

/*����Ʈ ���ۿ� ���� ��� ����*/
int list_delete_head(Dlist *dlp);

/*����Ʈ ���� ���� ��� ����*/
int list_delete_tail(Dlist *dlp);

/*�����Ϳ� ���� ��� ����*/
int list_delete_data(Dlist *dlp,int data);

/*�ε����� ���� ��� ����*/
int list_delete_index(Dlist *dlp, int index);

/*�����Ϳ� ���� ��� Ž��*/
int list_search_data(Dlist *dlp, int search);

/*����Ʈ ��ü ����*/
void list_clear(Dlist *dlp);

/*����Ʈ ī��*/
Dlist* list_copy(Dlist *dlp);

/*����Ʈ�� ���*/
void list_display(Dlist *dlp);

/*�������� ����(Exchange)*/
void list_sort_asc_excangeSort(Dlist *dlp);

/*�������� ����(Exchange)*/
void list_sort_dec_excangeSort(Dlist *dlp);

/*�������� ����(Merge)*/
void list_sort_asc_mergeSort(Dlist *dlp);

/*�������� ����(Merge)*/
void list_sort_dec_mergeSort(Dlist *dlp);

/*�������� ����(Quick)*/
void list_sort_asc_quickSort(Dlist *dlp);

/*�������� ����(Quick)*/
void list_sort_dec_quickSort(Dlist *dlp);


