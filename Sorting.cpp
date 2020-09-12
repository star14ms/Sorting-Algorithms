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


int i, j;


void bubbleSort(int arr[], int n) {
	for (i=0; i<n-1; i++) { 
	    for (j=0; j<n-i-1; j++) {
	        if (arr[j] > arr[j+1]) { /// '<' -> '>' 
	    	    swap(&arr[j], &arr[j+1]);
	    	    
	    		printArr(arr, 0, n);
				printf("(%d, %d 교체)\n", arr[j], arr[j+1]);
	     	}
	    }	
	}
}


void selectionSort(int arr[], int n) {
	for (i=0; i<n-1; i++) {
		int min = i;
		for (j=i+1; j<n; j++) {
			if (arr[i] > arr[j]) {
				min = j;
			}
		}
		swap(&arr[i], &arr[min]);
		
		printArr(arr, 0, n);
		printf("(선택 숫자: %d)\n", arr[i]);
	}
}


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


void merge(int a[], int l, int m, int r) {
	int b[r+1], i=l, j=m+1, k=0; /// 'k=l' -> 'k=0' /// b[r] -> b[r+1]
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
		merge(arr, l, m, r);
		
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
		printArr(arr, l, r+1); /// 'r' -> 'r+1'
		printf("\n");
	}
}


int partition(int arr[], int l, int r) {
	
	srand(time(NULL));
	int rng = l + (rand()%(r-l+1));
	swap(&arr[rng], &arr[r]);
	int pivot = arr[r];
	
	int i = l - 1;
	for (j=l; j<=r-1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[r]);
	
	printf("\n중심점 %d\n", pivot);
	printArr(arr, l, r+1);
	printf("\n");
	
	return (i + 1);
}

void quickSort(int arr[], int l, int r) {
	if (l < r) {
		int p = partition(arr, l, r);
		quickSort(arr, l, p-1);
		quickSort(arr, p+1, r);
	}
}


int main(void) {
	int n, m;
	while(1) {
		printf("정렬할 숫자 개수 : ");
    	scanf("%d", &n);
		
    	int arr[n];
    	printf("정렬시킬 숫자들 : ");
    	for (i=0; i<n; i++) {
    		scanf("%d", &arr[i]);
		}
		
		printf("\n정렬 방법 선택\n");
		printf("버블(1)/선택(2)/삽입(3)/병합(4)/퀵(5) : ");
		scanf("%d", &m); 
		
		printf("\n");
		printArr(arr, 0, n);
		printf("\n");
        
		if (m==1) { 
			bubbleSort(arr, n);
			printf("\n버블 정렬 (Bubble Sort) : 바로 앞의 수가 더 크면 교체하기\n");
		} else if (m==2) {
    		selectionSort(arr, n);
    		printf("\n선택 정렬 (Selection Sort) : 제일 작은 수를 선택해 앞에서부터 차례대로 교체하기\n");
		} else if (m==3) {
    		insertionSort(arr, n);
    		printf("\n삽입 정렬 (Insertion Sort) : 앞에서부터 하나씩 선택하면서 알맞은 위치에 삽입하기\n");
    	} else if (m==4) {
    		mergeSort(arr, 0, n-1); /// 'n' -> 'n-1'
    		printf("\n병합 정렬 (Merge Sort) : 잘게 쪼갠 후 정렬하며 합치기\n");
		} else {
			quickSort(arr, 0, n-1);
			printf("\n");
			printArr(arr, 0, n);
			printf("\n\n퀵 정렬 (Quick Sort) : 하나씩 선택하면서 그보다 작은건 왼쪽, 큰건 오른쪽으로 이동시키기\n");
		}
		printf("--------------------------------\n");
	}
}
