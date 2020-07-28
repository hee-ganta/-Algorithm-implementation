#include <stdio.h>
void quicksort(int low, int high);
void partition(int low, int high, int *pivotpoint);

//적용하고자 하는 배열을 전역적으로 정의한다.
int S3[8] = { 123,34,189,56,150,12,9,240 };

int main()
{
	int i;
	printf("빠른정렬 과정 으로 배열의 정렬 시작!\n");
	printf("--------------------------------\n");
	printf("정렬 전 배열->");
	//정렬하기전 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");
	quicksort(0, 7);
	printf("최종으로 정렬한 배열(quicksort) ->");
	//정돈한 배열을 보여준다
	for (i = 0; i < 8; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");

	return 0;
}

//빠른 정렬의 구현
void quicksort(int low, int high)
{
	//피봇 정보를 담을 변수의 선언
	int pivotpoint = 0;

	if (high > low)
	{
		//해당 배열에 대하여 맨 앞의 수를 피봇 포인트로 정하고
		//정렬을 다 마친다음
		//피봇이 된 수를 해당 자리에 넣어준다
		partition(low, high, &pivotpoint);
		//처음부분에서 피봇의 전 부분까지를 다시 빠른 정렬로 정리 
		quicksort(low, pivotpoint - 1);
		//피봇의 다음 부분부터 끝 부분까지 다시 빠른 정렬로 정리
		quicksort(pivotpoint + 1, high);
	}
}

void partition(int low, int high, int *pivotpoint)
{
	int i, j, temp;
	int pivotitem;

	//피봇을 정돈하고자 하는 배열의 첫 부분으로 설정
	pivotitem = S3[low];
	//피봇보다 작은 데이터가 나올 경우 자리를 바꿔주기 위한
	//위치를 담기 위한 변수의 설정
	j = low;
	//피봇으로 부터 다음 데이터부터 배열의 끝 부분 데이터 까지의 정렬의 시작
	for (i = low + 1; i <= high; i++)
	{
		//만약 해당 데이터가 피봇 아이템보다 작은 경우 위치를 앞 부분으로 옮김
		if (S3[i] < pivotitem)
		{
			j++;
			temp = S3[i];
			S3[i] = S3[j];
			S3[j] = temp;
		}
	}
	//정렬을 다 마치고 난 후에 해당 피봇을 피봇보다
	//작은 데이터와 큰 데이터 사이에 위치시킴
	*pivotpoint = j;
	temp = S3[low];
	S3[low] = S3[*pivotpoint];
	S3[*pivotpoint] = temp;
	//정돈하는 과정을 보여줌
	printf("정돈의 과정 ->");
	for (i = 0; i <= 7; i++)
	{
		printf(" %d", S3[i]);
	}
	printf("\n");
}