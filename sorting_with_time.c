#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

inline__; void printArr(int *arr, int l, int r) {for (int i=l; i<=r; i++) printf("%d ", arr[i]);}

void shuffle(int *arr, int n){
	srand(time(NULL));
	for (int i=0; i<n-1; i++){
		int rn = rand() % (n-i) + i;
		swap(&arr[i], &arr[rn]);
	}
}

int count;
//---------------------------------------------------------------------------------------------------- Bubble Sort

void bubbleSort(int *arr, int n){
	for (int i=0; i<n-1; i++) for (int k=0; k<n-i-1; k++) if (arr[k] > arr[k+1]) swap(&arr[k], &arr[k+1]);
}

//---------------------------------------------------------------------------------------------------- Bubble Sort 2 (improved)

void bubbleSort_2(int *arr, int n){
	int i = n-1;
	while(i != 0){
		int last = 0;
		for (int k=0; k<i; k++){
			if (arr[k] > arr[k+1]){
				swap(&arr[k], &arr[k+1]);
				last = k;
			}
		}
		i = last;
	}
}

//---------------------------------------------------------------------------------------------------- Cocktail Shaker Sort

void shakerSort(int *arr, int n){
	int l = 0;
	int r = n-1;
	int last = r;
	while (l < r){
		for (int k=r; k>l; k--){
			if (arr[k] < arr[k-1]){
				swap(&arr[k], &arr[k-1]);
				last = k;
			}
		}
		l = last;
		
		if (l == r) break;
		for (int k=l; k<r; k++){
			if (arr[k] > arr[k+1]){
				swap(&arr[k], &arr[k+1]);
				last = k;
			}
		}
		r = last;
	}
}

//---------------------------------------------------------------------------------------------------- Selection Sort

void selectionSort(int *arr, int n){
	for (int i=0; i<n-1; i++){
		int min = i;
		for (int k=i+1; k<n; k++) if (arr[min] > arr[k]) min = k;
		swap(&arr[i], &arr[min]);
	}
}

//---------------------------------------------------------------------------------------------------- Double Selection Sort

void double_selection_Sort(int *arr, int n){
	for (int i=0; i<n/2; i++){
		int min = i;
		int max = n-i-1;
		for (int k=i; k<n-i; k++){
			if (arr[min] > arr[k]) min = k;
			if (arr[max] < arr[k]) max = k;
		}
		if (max == i) max = min;
		swap(&arr[i], &arr[min]); 
		swap(&arr[n-i-1], &arr[max]);
	}
}

//---------------------------------------------------------------------------------------------------- Insertion Sort

void insertionSort(int *arr, int l, int r){
	for (int i=l+1; i<=r; i++){
		int key = arr[i];
		int k = i-1;
		while (k>=l && arr[k]>key){
			arr[k+1] = arr[k];
			k--;
		}
		arr[k+1] = key;
	}
}

//---------------------------------------------------------------------------------------------------- Binary Insertion Sort

void binary_insertionSort(int *arr, int l, int r){
	for (int i=l+1; i<=r; i++){
		int key = arr[i];
		int left=l, right=i-1;
		int mid = (left+right)/2;

		for (int a=right-left+1; a>0; a/=2){
			if (key < arr[mid]){
				right = mid-1;
			} else {
				left = mid+1;
			}
			if (right == -1){
				mid = -1;
				break;
			}
			mid = (left+right)/2;
		}

		int k;
    for (k=i; k>mid+1; k--) arr[k] = arr[k-1];
		arr[k] = key;
	}
}

//---------------------------------------------------------------------------------------------------- Shell's Sort

void shellSort(int *arr, int n){
	for (int k=n/2; k!=0; k/=2){
		if ((k % 2 == 1) && (k-1 != 0)) k += 1;
		for (int i=0; i+k<n; i++){
			for (int a=i; arr[a]>arr[a+k]; a-=k){
				if (a < 0) break;
				swap (&arr[a], &arr[a+k]);
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------- Merge Sort

void merge(int *arr, int l, int m, int r){
	int brr[r-l+1], i=l, j=m+1;
	int k = 0;
	while (i<=m && j<=r){
		if (arr[i] <= arr[j]){
			brr[k++] = arr[i++];
		} else {
			brr[k++] = arr[j++];
		}
	}
	while (i<=m){
		brr[k++] = arr[i++];
	}
	while (j<=r){
		brr[k++] = arr[j++];
	}
	for (k-=1; k>=0; k--) arr[l+k] = brr[k];
}

void mergeSort(int *arr, int l, int r){
	if (l < r){
		int m = (l+r)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

//---------------------------------------------------------------------------------------------------- Tim Sort

void timSort(int *arr, int l, int r){
	if (r-l+1 <= 16) insertionSort(arr, l, r);
	else {
		int m = (l+r)/2;
		timSort(arr, l, m);
		timSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

//---------------------------------------------------------------------------------------------------- Quick Sort

int partition(int *arr, int l, int r){
	srand(time(NULL));
	int rng = l + (rand()%(r-l+1));
	swap(&arr[rng], &arr[r]);
	int pivot = arr[r];
	
	int i = l-1;
	for (int k=l; k<=r-1; k++) if (arr[k] <= pivot) swap(&arr[++i], &arr[k]);
	swap(&arr[i+1], &arr[r]);
	return (i+1);
}

void quickSort(int *arr, int l, int r){
	if (l < r){
		int p = partition(arr, l, r);
		quickSort(arr, l, p-1);
		quickSort(arr, p+1, r);
	}
}

//---------------------------------------------------------------------------------------------------- Heap Sort

void heapSort(int *arr, int n){
	for (int i=n; i!=0; i--){
		for (int key=n-i+1; key-1!=0; key/=2){
			if (arr[key-1] > arr[key/2-1]) swap(&arr[key-1], &arr[key/2-1]);
			else break;
		}
	}
	int win;
	int r = n-1;
	while (r != 0){
		swap(&arr[0], &arr[r--]);
		for (int key=1; key*2<=r+1; key=win){
			if ((key*2 == r+1) || (arr[key*2-1] > arr[key*2]))
				win = key*2;
			else
				win = key*2+1;
			if (arr[key-1] < arr[win-1]) swap(&arr[key-1], &arr[win-1]);
			else break;
		}
	}
}

//---------------------------------------------------------------------------------------------------- Intro Sort

void heapSort_intro(int *arr, int l, int r){
	for (int i=r-l+1; i!=0; i--){
		for (int key=r-l+1-i+1; key-1!=0; key/=2){
			if (arr[l+key-1] > arr[l+key/2-1]) swap(&arr[l+key-1], &arr[l+key/2-1]);
			else break;
		}
	}
	int win;
	int end = r;
	while (end != l){
		swap(&arr[l], &arr[end--]);
		for (int key=1; l+key*2<=end+1; key=win){
			if ((l+key*2 == end+1) || (arr[l+key*2-1] > arr[l+key*2]))
				win = key*2;
			else
				win = key*2+1;
			if (arr[l+key-1] < arr[l+win-1]) swap(&arr[l+key-1], &arr[l+win-1]);
			else break;
		}
	}
}

void introSort(int *arr, int l, int r){
	count++;
	if (l < r){
		if (count > 4) heapSort_intro(arr, l, r);
		else {
  	int p = partition(arr, l, r);
		introSort(arr, l, p-1);
		introSort(arr, p+1, r);
		}
	}
	count--;
}

//---------------------------------------------------------------------------------------------------- Bogo(stupid) Sort

void bogoSort(int *arr, int n){
	while (1){
		char isSorted = 'O';
		for (int i=n-1; i!=0; i--){
			if (arr[i] < arr[i-1]){
				isSorted = 'X';
				break;
			}
		}
		if (isSorted == 'O') break;
		shuffle(arr, n);
		count++;
		printf("%d\n", count);
	}
}

//---------------------------------------------------------------------------------------------------- main fucntion

int main(void){
	int n, m;
	int start, elapsed;
	printf("\n각 정렬 알고리즘의 정렬 소요시간 측정하기!\n");
	printf("--------------------------------\n");
	while(1){
		printf("정렬할 숫자 개수는? : ");
		scanf("%d", &n);
		if (n==0) break;
		int *arr, *brr;
		arr = (int *)malloc(sizeof(int) * n);
		brr = (int *)malloc(sizeof(int) * n);


		printf("\n정렬할 숫자들 1~~%d (1)/사용자 지정(other num) : ", n);
		scanf("%d", &m);
		if (m==1)
			for (int i=0; i<n; i++) arr[i] = i + 1;
		else {
			printf("정렬시킬 숫자들 : ");
    	for (int i=0; i<n; i++) scanf("%d", &arr[i]);
		}


		printf("\n순서를 섞을까? Yes(1)/No(other num) : ");
		scanf("%d", &m);
		for (int i=0; i<n; i++) brr[i] = arr[i];
		if (m==1){
			shuffle(arr, n);
			printf("\n섞인 숫자 보기 skip(1)/show(other num) : ");
			scanf("%d", &m);
			if (m!=1){
				printArr(arr, 0, n-1);
				printf("\n");
			}
		}
		printf("--------------------------------\n");

  
		while(1){
			printf("정렬 방법 선택\n");
			printf("버블(1)/선택(2)/삽입(3)/병합(4)/퀵(5)/힙(6)/\n버블++(11)/쉐이크(111)/이중 선택(22)/이진 삽입(33)/셸(333)/Tim(43)/인트로(56)/보고(0)/숫자 재설정(other num): ");
			scanf("%d", &m);
			printf("\n");

			if (m==1){
				start = clock();
				bubbleSort(arr, n);
				elapsed = clock();
				printf("버블 정렬 (Bubble Sort) : 차례로 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복\n");	
			}
			else if (m==2){
				start = clock();
				selectionSort(arr, n);
				elapsed = clock();
				printf("선택 정렬 (Selection Sort) : 제일 작은 숫자부터 차례로 선택하여, 맨 앞쪽부터 차례로 교체하기\n");		
			}
			else if (m==3){
				start = clock(); 
				insertionSort(arr, 0, n-1);
				elapsed = clock();
				printf("삽입 정렬 (Insertion Sort) : 차례로 하나씩 선택하여, 정리된 앞쪽 배열의 알맞은 위치에 삽입하기\n");		
			}
			else if (m==4){
				start = clock();
				mergeSort(arr, 0, n-1);
				elapsed = clock();
				printf("병합 정렬 (Merge Sort) : 반씩 나누기를 반복하여 잘게 쪼갠 후, 다시 합치면서 정렬\n");		
			}
			else if (m==5){
				start = clock();
				quickSort(arr, 0, n-1);
				elapsed = clock();
				printf("퀵 정렬 (Quick Sort) : 랜덤으로 하나씩 선택한 것을 기준으로 더 작거나 같은건 왼쪽, 더 큰건 오른쪽으로 보내기\n");	
			}
			else if (m==11){
				start = clock();
				bubbleSort_2(arr, n);
				elapsed = clock();
				printf("개선 버블정렬 : 한 바퀴 돌 때마다 범위를 교환이 일어나지 않기 시작하는 부분의 전까지로 한정\n\n");
				printf("기존 버블정렬 : 한 바퀴 돌 때마다 범위를 뒤에서부터 하나씩 줄임\n");  		
			}
			else if (m==111){
				start = clock();
				shakerSort(arr, n);
				elapsed = clock();
				printf("양방향 버블정렬 (Cocktail Shaker Sort) : 양쪽 끝의 정렬 완료된 부분에 도달할 때마다 진행 방향 뒤집기\n\n");
				printf("기존 버블정렬 : 선택 위치를 한칸씩 옮기면서, 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복\n");
			}
			else if (m==22){
				start = clock();
				double_selection_Sort(arr, n);
				elapsed = clock();
				printf("이중 선택 정렬 (Double Selection Sort) : 최솟값, 최댓값을 선택해 그 부분의 양 끝과 바꾸기를 반복\n\n");
				printf("(선택 정렬 : 최솟값만 찾아 바꿈)\n");
			}
			else if (m==43){
				start = clock();
				timSort(arr, 0, n-1);
				elapsed = clock();
				printf("Tim 정렬 (Tim Sort) : 병합 정렬에서 숫자 갯수가 16 이하인 구역에선 삽입 정렬\n");
			}
			else if (m==33){
				start = clock();
				binary_insertionSort(arr, 0, n-1);
				elapsed = clock();
				printf("이진 삽입 정렬 (Binary Insertion Sort) : 알맞은 위치를 정렬된 부분을 반씩 나누며 찾음\n\n");
				printf("(삽입 정렬 : 정렬된 부분의 맨 뒤부터 한 칸씩 앞으로 오며 비교함)\n");
			}
			else if (m==6){
				start = clock();
				heapSort(arr, n);
				elapsed = clock();
				printf("힙 정렬 (Heap Sort) : 부모의 값이 항상 자식들의 값보다 크도록 유지하며 첫번째 값을 뒤에서부터 교환하기를 반복\n");
			}
			else if (m==333){
				start = clock();
				shellSort(arr, n);
				elapsed = clock();
				printf("셸 정렬 (Shell's Sort) : 띄엄띄엄한 간격으로 삽입 정렬을 하며, 매 바퀴마다 그 간격을 반씩 줄여나간다.\n");
			}
			else if (m==0){
				start = clock();
				bogoSort(arr, n);
				elapsed = clock();
				printf("가짜 정렬 (Bogo(stupid) Sort) : 정렬이 안되있다면 랜덤으로 데이터를 재배열하고 다시 검사 (다시 섞은 횟수: %d)\n", count);
			}
			else if (m==56){
				start = clock();
				introSort(arr, 0, n-1);
				elapsed = clock();
				printf("인트로 정렬 (Intro Sort) : 퀵 정렬에서 재귀 횟수가 많아지면 힙 정렬\n");
			} else break;

			printf("\n정렬 시간 : %.4f sec\n", (double)(elapsed - start)/CLOCKS_PER_SEC);

			printf("\n정렬된 숫자 보기 skip(1)/show(other num) : ");
			scanf("%d", &m);
			if (m!=1){
				printArr(arr, 0, n-1);
		  	printf("\n");
			}

			for (int i=0; i<n; i++) arr[i] = brr[i];
			count=0;
			printf("--------------------------------\n");
		}
		free(arr);
		free(brr);
		printf("\n숫자 설정 단계로 돌아가기\n--------------------------------\n");
	}
	printf("\n나가기");
}
