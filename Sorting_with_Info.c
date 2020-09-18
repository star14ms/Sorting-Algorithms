#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

inline__; void printArr(int arr[], int l, int r) {for (int i=l; i<=r; i++) printf("%d ", arr[i]);} /// 'a<r-1' -> 'a<r'

void shuffle(int *arr, int n){ 
	srand(time(NULL)); 
	for (int i=0; i<n-1; i++){ 
		int rn = rand() % (n-i) + i; // i 부터 num-1 사이에 임의의 정수 생성 
		swap(&arr[i], &arr[rn]); 
	} 
}

int comparisons;
//---------------------------------------------------------------------------------------------------- Bubble Sort

void bubbleSort(int arr[], int n){
	for (int i=0; i<n-1; i++){ 
		printf("\n처음으로! (%d번째까지 비교)\n", n-i-1);
		for (int k=0; k<n-i-1; k++){
			if (arr[k] > arr[k+1]){ /// '<' -> '>' 
				swap(&arr[k], &arr[k+1]);
				printArr(arr, 0, n-1);
				printf("(%d, %d) 교체\n", arr[k], arr[k+1]);
			} else {
				printArr(arr, 0, n-1);
				printf("(%d, %d)\n", arr[k], arr[k+1]);
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------- Bubble Sort 2 (improved)

void bubbleSort_2(int arr[], int n){
	int i = n-1; /// n -> n-1
	while(i != 0){
		printf("\n처음으로! (%d번째까지 비교)\n", i+1);
		int last = 0;
		for (int k=0; k<i; k++){ /// i-1 -> i
			if (arr[k] > arr[k+1]){
				swap(&arr[k], &arr[k+1]);
				last = k; /// k+1 -> k
				
				printArr(arr, 0, n-1);
				printf("(%d, %d) 교체\n", arr[k], arr[k+1]);
			} else {
				printArr(arr, 0, n-1);
				printf("(%d, %d)\n", arr[k], arr[k+1]);
			}
			comparisons++;
 		}
		i = last; /// for문 안에 있음
 	}
}

//---------------------------------------------------------------------------------------------------- Cocktail Shaker Sort

void shakerSort(int arr[], int n){
	int l = 0;
	int r = n-1;
	int last = r;
	while (l < r){
		printf("\n방향 전환! (%d~%d번째까지 비교)\n", r+1, l+1);
		for (int k=r; k>l; k--){
			if (arr[k] < arr[k-1]){
				swap(&arr[k], &arr[k-1]);
				last = k;
				
				printArr(arr, 0, n-1);
				printf("(%d, %d) 교체\n", arr[k-1], arr[k]);
			} else {
				printArr(arr, 0, n-1);
				printf("(%d, %d)\n", arr[k-1], arr[k]);
			}
			comparisons++;
		}
		l = last;
		
		if (l == r) break;

		printf("\n방향 전환! (%d~%d번째까지 비교)\n", l+1, r+1);
		for (int k=l; k<r; k++){
			if (arr[k] > arr[k+1]){
				swap(&arr[k], &arr[k+1]);
				last = k;
				
				printArr(arr, 0, n-1);
				printf("(%d, %d) 교체\n", arr[k], arr[k+1]);
			} else {
				printArr(arr, 0, n-1);
				printf("(%d, %d)\n", arr[k], arr[k+1]);
			}
			comparisons++;
		}
		r = last;
	}
}

//---------------------------------------------------------------------------------------------------- Selection Sort

void selectionSort(int arr[], int n){
	for (int i=0; i<n-1; i++){
		int min = i;
		for (int k=i+1; k<n; k++) if (arr[min] > arr[k]) min = k;
		swap(&arr[i], &arr[min]);
		
		printArr(arr, 0, n-1);
		printf("(선택 숫자: %d)\n", arr[i]);
	}
}

//---------------------------------------------------------------------------------------------------- Double Selection Sort

void double_selection_Sort(int arr[], int n){
	for (int i=0; i<n/2; i++){ /// n -> n/2
		int min = i;
		int max = n-i-1;
		for (int k=i; k<n-i; k++){ /// k<n -> k<n-i
			if (arr[min] > arr[k]) min = k;
			if (arr[max] < arr[k]) max = k;
		}
		swap(&arr[i], &arr[min]); 
		if (max == i) max = min;
		swap(&arr[n-i-1], &arr[max]);
		
		printArr(arr, 0, n-1);
		printf("(선택 숫자: %d, %d)\n", arr[i], arr[n-i-1]);
	}
}

//---------------------------------------------------------------------------------------------------- Insertion Sort

void insertionSort(int arr[], int l, int r){
	for (int i=l+1; i<=r; i++){
		int key = arr[i];
		int k = i-1;
		while (k>=l && arr[k]>key){
			arr[k+1] = arr[k];
			k--;
		}
		arr[k+1] = key; 
		
		printArr(arr, l, r);
		printf("(삽입 숫자: %d)\n", key);
	}
}

//---------------------------------------------------------------------------------------------------- Binary Insertion Sort

void binary_insertionSort(int arr[], int l, int r){
	for (int i=l+1; i<=r; i++){
		int key = arr[i];
		int left=l, right=i-1;
		int mid = (left+right)/2;
		
		for (int a=right-left+1; a>0; a/=2){ /// while은 끝나지 않음, 항상 key가 mid보다 작거나 크기 때문에 /// i -> a
			if (left==l) printf("(%c < ", '?'); 
			else if (left==mid || right==mid) printf("(%d=< ", arr[left-1]); // && -> || 
			else printf("(%d < ", arr[left]);
			printf("%d=< ", arr[mid]);
			if (right==i-1) printf("%c)\n", '?');
			else if (right==mid) printf("%d)\n", arr[right+1]);
			else printf("%d)\n", arr[right]);
			// printf("%d < %d <= %d\n", left+1, mid+1, right+1);

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
    for (k=i; k>mid+1; k--){
			arr[k] = arr[k-1];
		}
		arr[k] = key;

		printArr(arr, l, r);
		printf("(삽입 숫자: %d)\n", key);
	}
}

//---------------------------------------------------------------------------------------------------- Merge Sort

void merge(int a[], int l, int m, int r){
	int b[r-l+1], i=l, j=m+1;
	int k = 0; /// 'k=l' -> 'k=0' /// b[r] -> b[r+1] -> b[r-l+1]
	while (i<=m && j<=r){
		if (a[i] <= a[j]){
			b[k++] = a[i++];
		} else {
			b[k++] = a[j++];
		}
	}
	while (i<=m){
		b[k++] = a[i++];
	}
	while (j<=r){
		b[k++] = a[j++];
	}
	for (k-=1; k>=0; k--) a[l+k] = b[k]; /// k=0 -> k!=0 -> k>=0
}

void mergeSort(int arr[], int l, int r){
	if (l < r){
		int m = (l+r)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		
		if (l+1 == m+1){
			printf("\n%d번째 vs ", l+1);
		} else {
			printf("\n%d~%d번째 vs ", l+1, m+1);
		}
		if (m+2 == r+1){
			printf("%d번째\n", m+2);
		} else {
			printf("%d~%d번째\n", m+2, r+1);
		}
		
		merge(arr, l, m, r);
		
		printArr(arr, l, r); /// 'r' -> 'r+1'
		printf("\n");
	}
}

//---------------------------------------------------------------------------------------------------- Tim Sort

void timSort(int arr[], int l, int r){
	if (r-l+1 <= 16){
		printf("\n%d~%d번째 삽입정렬\n", l+1, r+1);
		insertionSort(arr, l, r);
	} else {
		int m = (l+r)/2;
		timSort(arr, l, m);
		timSort(arr, m+1, r);
		
		if (l+1 == m+1){
			printf("\n%d번째 vs ", l+1);
		} else {
			printf("\n%d~%d번째 vs ", l+1, m+1);
		}
		if (m+2 == r+1){
			printf("%d번째 병합정렬\n", m+2);
		} else {
			printf("%d~%d번째 병합정렬\n", m+2, r+1);
		}
		
		merge(arr, l, m, r);
		
		printArr(arr, l, r);
		printf("\n");
	}
}

//---------------------------------------------------------------------------------------------------- Quick Sort

int partition(int arr[], int l, int r){
	srand(time(NULL));
	int rng = l + (rand()%(r-l+1));
	swap(&arr[rng], &arr[r]);
	int pivot = arr[r];
	
	int i = l-1;
	for (int k=l; k<=r-1; k++) if (arr[k] <= pivot) swap(&arr[++i], &arr[k]);
	swap(&arr[i+1], &arr[r]);
	
	printf("\n기준 %d\n", pivot);
	printArr(arr, l, r);
	printf("\n");
	
	return (i+1);
}

void quickSort(int arr[], int l, int r){
	if (l < r){
		int p = partition(arr, l, r);
		quickSort(arr, l, p-1);
		quickSort(arr, p+1, r);
	}
}

//---------------------------------------------------------------------------------------------------- main fucntion

int main(void){
	int n, m, o, p;
	printf("\n여러 종류의 정렬 알고리즘 체험하기!\n");
	printf("--------------------------------\n");
	while(1){
		printf("정렬할 숫자 개수는? : ");
		scanf("%d", &n);
		if (n==0) break;
		int *arr, *brr;
		arr = (int *)malloc(sizeof(int) * n); // 입력받은 배열의 크기만큼 메모리 할당 
		brr = (int *)malloc(sizeof(int) * n);


		printf("\n정렬할 숫자들은? 1~~%d (1)/사용자 지정(other num) : ", n);
		scanf("%d", &m);
		if (m==1) for (int i=0; i<n; i++) arr[i] = i + 1; // 배열을 1부터 num 까지의 요소로 초기화 
		else {
			printf("정렬시킬 숫자들 : ");
    	for (int i=0; i<n; i++) scanf("%d", &arr[i]);
		}
		printf("\n");
		printArr(arr, 0, n-1);


		printf("\n\n순서를 섞을까? Yes(1)/No(other num) : ");
		scanf("%d", &o);
		if (o==1) shuffle(arr, n);

		
		for (int i=0; i<n; i++) brr[i] = arr[i];
		printf("\n");
		printArr(arr, 0, n-1);
		printf("\n--------------------------------\n");

		
		while(1){
			printf("정렬 방법 선택\n");
			printf("버블(1)/선택(2)/삽입(3)/병합(4)/퀵(5)/버블++(6)/캌퉤일(7)/\n이중 선택(8)/Tim(9)/이진 삽입(0)/숫자 재설정(other num): ");
			scanf("%d", &p);
		
			printf("\n");
			printArr(arr, 0, n-1);
			printf("\n");

			if (p==1){
				bubbleSort(arr, n);
				printf("\n버블 정렬 (Bubble Sort) : 차례로 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복\n");
			}
			else if (p==2){
				printf("\n");
				selectionSort(arr, n);
				printf("\n선택 정렬 (Selection Sort) : 제일 작은 숫자부터 차례로 선택하여, 맨 앞쪽부터 차례로 교체하기\n");
			}
			else if (p==3){
				printf("\n");
				insertionSort(arr, 0, n-1);
				printf("\n삽입 정렬 (Insertion Sort) : 차례로 하나씩 선택하여, 정리된 앞쪽 배열의 알맞은 위치에 삽입하기\n");
			}
			else if (p==4){
				mergeSort(arr, 0, n-1); /// 'n' -> 'n-1'
				printf("\n병합 정렬 (Merge Sort) : 반씩 나누기를 반복하여 잘게 쪼갠 후, 다시 합치면서 정렬\n");
			}
			else if (p==5){
				quickSort(arr, 0, n-1);
				printf("\n"); 
				printArr(arr, 0, n-1);
				printf("\n\n퀵 정렬 (Quick Sort) : 랜덤으로 하나씩 선택한 것을 기준으로 더 작거나 같은건 왼쪽, 더 큰건 오른쪽으로 보내기\n");
			}
			else if (p==6){
				bubbleSort_2(arr, n);
				printf("\n개선 버블정렬 : 한 바퀴 돌 때마다 범위를 교환이 일어나지 않기 시작하는 부분의 전까지로 한정 (비교 횟수: %d)\n", comparisons);
				printf("\n기존 버블정렬 : 한 바퀴 돌 때마다 범위를 뒤에서부터 하나씩 줄임 (비교 횟수: %d))\n", n*(n-1)/2);
			}
			else if (p==7){
				shakerSort(arr, n);
				printf("\n양방향 버블정렬 (Cocktail Shaker Sort) : 양쪽 끝의 정렬 완료된 부분에 도달할 때마다 진행 방향 뒤집기 (비교 횟수: %d)\n", comparisons);
				printf("\n기존 버블정렬 : 선택 위치를 한칸씩 옮기면서, 이웃한 두 수를 선택하여, 앞의 수가 더 크면 교체하기를 반복 (비교 횟수: %d)\n", n*(n-1)/2);
			} 
			else if (p==8){
				double_selection_Sort(arr, n);
				printf("\n이중 선택 정렬 (Double Selection Sort) :\n\n정렬이 안 된 부분을 쭉 훑으며 최솟값과 최댓값을 선택해 그 부분의 양 끝과 바꾸기를 반복 ");
				printf("(선택 정렬 : 최솟값만 찾아 바꿈)\n");
			}
			else if (p==9){
				timSort(arr, 0, n-1);
				printf("\nTim 정렬 (Tim Sort) : 병합 정렬에서 숫자 갯수가 16 이하인 구역에선 삽입 정렬\n");
				printf("\n병합 정렬 (Merge Sort) : 반씩 나누기를 반복하여 잘게 쪼갠 후, 다시 합치면서 정렬\n");
			}
			else if (p==0){
				binary_insertionSort(arr, 0, n-1);
				printf("\n이진 삽입 정렬 (Binary Insertion Sort) : \n\n알맞은 위치를 정렬된 부분을 반씩 나누며 찾음 ");
				printf("(삽입 정렬 : 정렬된 부분의 맨 뒤부터 한 칸씩 앞으로 오며 비교함)\n");
			} else break;
			
			for (int i=0; i<n; i++) arr[i] = brr[i];
			comparisons=0;
			printf("--------------------------------\n");
		}
		free(arr);
		free(brr);
		printf("\n숫자 설정 단계로 돌아가기\n--------------------------------\n");
	}
	printf("\n나가기");
}