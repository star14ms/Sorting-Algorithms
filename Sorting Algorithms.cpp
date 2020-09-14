#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void printArr(int arr[], int l, int r) {
	printf("-> ");
	for (int a=l; a<r; a++) { /// 'a<r-1' -> 'a<r'
		printf("%d ", arr[a]);
	}
}

void shuffle(int *arr, int n) { 
	srand(time(NULL)); 
	int temp, rn;
	for (int i=0; i<n-1; i++) { 
		rn = rand() % (n-i) + i; // i 부터 num-1 사이에 임의의 정수 생성 
		swap(&arr[i], &arr[rn]); 
	} 
} 

int i, j, comparisons;
//---------------------------------------------------------------------------------------------------- Bubble Sort

void bubbleSort(int arr[], int n) {
	for (i=0; i<n-1; i++) { 
		printf("\n처음으로! (%d번째까지 비교)\n", n-i-1);
		for (j=0; j<n-i-1; j++) {
			if (arr[j] > arr[j+1]) { /// '<' -> '>' 
				swap(&arr[j], &arr[j+1]);
	    	    
				printArr(arr, 0, n);
				printf("(%d, %d) 교체\n", arr[j], arr[j+1]);
			} else {
				printArr(arr, 0, n);
				printf("(%d, %d)\n", arr[j], arr[j+1]);
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------- Bubble Sort 2 (improved)

void bubbleSort_v2(int arr[], int n) {
	i = n-1; /// n -> n-1
	int last;
	while(i != 0) {
		printf("\n처음으로! (%d번째까지 비교)\n", i+1);
		last = 0;
		for (j=0; j<i; j++) { /// i-1 -> i
			if (arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
				last = j; /// j+1 -> j
				
				printArr(arr, 0, n);
				printf("(%d, %d) 교체\n", arr[j], arr[j+1]);
			} else {
				printArr(arr, 0, n);
				printf("(%d, %d)\n", arr[j], arr[j+1]);
			}
			comparisons++;
 		}
		i = last; /// for문 안에 있음
 	}
}

//---------------------------------------------------------------------------------------------------- Bubble Sort 3 (Cocktail Shaker Sort)

void shakerSort(int arr[], int n) {
	int l = 0;
	int r = n-1;
	int last = r;
	while (l < r) {
		printf("\n방향 전환! (%d~%d번째까지 비교)\n", r+1, l+1);
		for (int j=r; j>l; j--) {
			if (arr[j] < arr[j-1]) {
				swap(&arr[j], &arr[j-1]);
				last = j;
				
				printArr(arr, 0, n);
				printf("(%d, %d) 교체\n", arr[j-1], arr[j]);
			} else {
				printArr(arr, 0, n);
				printf("(%d, %d)\n", arr[j-1], arr[j]);
			}
			comparisons++;
		}
		l = last;
		if (l == r) {
			break;
		}
		printf("\n방향 전환! (%d~%d번째까지 비교)\n", l+1, r+1);
		for (int j=l; j<r; j++) {
			if (arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
				last = j;
				
				printArr(arr, 0, n);
				printf("(%d, %d) 교체\n", arr[j], arr[j+1]);
			} else {
				printArr(arr, 0, n);
				printf("(%d, %d)\n", arr[j], arr[j+1]);
			}
			comparisons++;
		}
		r = last;
	}
}

//---------------------------------------------------------------------------------------------------- Selection Sort

void selectionSort(int arr[], int n) {
	for (i=0; i<n-1; i++) {
		int min = i;
		for (j=i+1; j<n; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		swap(&arr[i], &arr[min]);
		
		printArr(arr, 0, n);
		printf("(선택 숫자: %d)\n", arr[i]);
	}
}

//---------------------------------------------------------------------------------------------------- Insertion Sort

void insertionSort(int arr[], int n) {
	for (i=1; i<n; i++) {
		int key = arr[i];
		j = i-1;
		while (j>=0 && arr[j]>key) {
			arr[j+1] = arr[j];
			j--;
		}	
		arr[j+1] = key; 
		
		printArr(arr, 0, n);
		printf("(삽입 숫자: %d)\n", key);
	}
}

//---------------------------------------------------------------------------------------------------- Merge Sort

void merge(int a[], int l, int m, int r) {
	int b[r-l+1], i=l, j=m+1, k=0; /// 'k=l' -> 'k=0' /// b[r] -> b[r+1] -> b[r-l+1]
	while (i<=m && j<=r) {
		if (a[i] <= a[j]) {
			b[k++] = a[i++];
		} else {
			b[k++] = a[j++];
		}
	}
	while (i<=m) {
		b[k++] = a[i++];
	}
	while (j<=r) {
		b[k++] = a[j++];
	}
	for (k-=1; k>=0; k--) { /// k=0 -> k!=0 -> k>=0
		a[l+k] = b[k];
	}
}

void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = (l+r)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		
		if (l+1 == m+1) {
			printf("\n%d번째 vs ", l+1);
		} else {
			printf("\n%d~%d번째 vs ", l+1, m+1);
		}
		if (m+2 == r+1) {
			printf("%d번째\n", m+2);
		} else {
			printf("%d~%d번째\n", m+2, r+1);
		}
		
		merge(arr, l, m, r);
		
		printArr(arr, l, r+1); /// 'r' -> 'r+1'
		printf("\n");
	}
}

//---------------------------------------------------------------------------------------------------- Quick Sort

int partition(int arr[], int l, int r) {
	
	srand(time(NULL));
	int rng = l + (rand()%(r-l+1));
	swap(&arr[rng], &arr[r]);
	int pivot = arr[r];
	
	int i = l-1;
	for (j=l; j<=r-1; j++) {
		if (arr[j] <= pivot) {
			swap(&arr[++i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[r]);
	
	printf("\n기준 %d\n", pivot);
	printArr(arr, l, r+1);
	printf("\n");
	
	return (i+1);
}

void quickSort(int arr[], int l, int r) {
	if (l < r) {
		int p = partition(arr, l, r);
		quickSort(arr, l, p-1);
		quickSort(arr, p+1, r);
	}
}

//---------------------------------------------------------------------------------------------------- main fucntion

int main(void) {
	int n, m, o, p;
	printf("\n여러 종류의 정렬 알고리즘 체험하기!\n");
	printf("--------------------------------\n");
	while(1) 
	{
		printf("정렬할 숫자 개수는? : ");
		scanf("%d", &n);
		if (n==0) {
			break;
		}
		int *arr, *brr;
		arr = (int *)malloc(sizeof(int) * n); // 입력받은 배열의 크기만큼 메모리 할당 
		brr = (int *)malloc(sizeof(int) * n);
					
		printf("\n정렬할 숫자들은? 1~~%d (1)/사용자 지정(other num) : ", n);
		scanf("%d", &o);
		if (o==1) {
			for (i=0; i<n; i++) {
				arr[i] = i + 1; // 배열을 1부터 num 까지의 요소로 초기화 
			}
		} else {
    		printf("정렬시킬 숫자들 : ");
    		for (i=0; i<n; i++) {
    			scanf("%d", &arr[i]);
			}	
		}
		printf("\n");
		printArr(arr, 0, n);
		
		printf("\n\n순서를 섞을까? Yes(1)/No(other num) : ");
		scanf("%d", &p);
		if (p==1) {
			shuffle(arr, n);
		}
		
		for (i=0; i<n; i++) {
			brr[i] = arr[i];
		}
		
		printf("\n");
		printArr(arr, 0, n);
		printf("\n--------------------------------\n");
		
		
		while(1) 
		{
			printf("정렬 방법 선택\n");
			printf("버블(1)/선택(2)/삽입(3)/병합(4)/퀵(5)/버블++(6)/캌퉤일(7)/숫자 재설정(other num) : ");
			scanf("%d", &m);
		
			printf("\n");
			printArr(arr, 0, n);
			printf("\n");

			if (m==1) { 
				bubbleSort(arr, n);
				printf("\n버블 정렬 (Bubble Sort) : 차례로 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복\n");
				
			} else if (m==2) {
				selectionSort(arr, n);
				printf("\n선택 정렬 (Selection Sort) : 제일 작은 숫자부터 차례로 선택하여, 맨 앞쪽부터 차례로 교체하기\n");
    			
			} else if (m==3) { 
				insertionSort(arr, n);
				printf("\n삽입 정렬 (Insertion Sort) : 차례로 하나씩 선택하여, 정리된 앞쪽 배열의 알맞은 위치에 삽입하기\n");
    			
			} else if (m==4) {
				mergeSort(arr, 0, n-1); /// 'n' -> 'n-1'
				printf("\n병합 정렬 (Merge Sort) : 반씩 나누기를 반복하여 잘게 쪼갠 후, 다시 합치면서 정렬\n");
    			
			} else if (m==5) {
				quickSort(arr, 0, n-1);
				printf("\n"); 
				printArr(arr, 0, n);
				printf("\n\n퀵 정렬 (Quick Sort) : 랜덤으로 하나씩 선택한 것을 기준으로 같거나 더 작은건 왼쪽, 더 큰건 오른쪽으로 보내기\n");
				
			} else if (m==6) {
				bubbleSort_v2(arr, n);
				printf("\n개선 버블정렬 : 한 바퀴 돌 때마다 범위를 교환이 일어나지 않기 시작하는 부분의 전까지로 한정 (%d번 비교)\n", comparisons);
				printf("\n기존 버블정렬 : 한 바퀴 돌 때마다 범위를 뒤에서부터 하나씩 줄임 (%d번 비교)\n", n*(n-1)/2);
        		
			} else if (m==7) {
				shakerSort(arr, n);
				printf("\n양방향 버블정렬 : 양쪽 끝의 정렬 완료된 부분에 도달할 때마다 진행 방향 뒤집기 (Cocktail Shaker Sort) (%d번 비교)\n", comparisons);
				printf("\n기존 버블정렬 : 선택 위치를 한칸씩 옮기면서, 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복 (%d번 비교)\n", n*(n-1)/2);

			} else {
				break;
			}
			
			for (i=0; i<n; i++) {
				arr[i] = brr[i];
			}
			comparisons=0;
			printf("--------------------------------\n");
		}
		free(arr);
		free(brr);
		printf("\n숫자 설정 단계로 돌아가기\n--------------------------------\n");
	}
	printf("\n나가기");
}
