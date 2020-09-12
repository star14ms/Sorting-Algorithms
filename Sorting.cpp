# include <stdio.h>

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
				printf("(%d, %d ��ü)\n", arr[j], arr[j+1]);
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
		printf("(���� ����: %d)\n", arr[i]);
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
		printf("(���� ����: %d)\n", key);
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
			printf("\n%d��° vs ", l+1);
		} else {
			printf("\n%d~%d��° vs ", l+1, m+1);
		}
		if (m+2 == r+1) {
			printf("%d��°\n", m+2);
		} else {
			printf("%d~%d��°\n", m+2, r+1);
		}
		printArr(arr, l, r+1); /// 'r' -> 'r+1'
		printf("\n");
	}
}


int partition(int arr[], int l, int r) {
	int pivot = arr[r];
	int i = l - 1;
	for (j=l; j<=r-1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[r]);
	
	printf("\n�߽��� %d\n", pivot);
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
		printf("������ ���� ���� : ");
    	scanf("%d", &n);
		
    	int arr[n];
    	printf("���Ľ�ų ���ڵ� : ");
    	for (i=0; i<n; i++) {
    		scanf("%d", &arr[i]);
		}
		
		printf("\n���� ��� ����\n");
		printf("����(1)/����(2)/����(3)/����(4)/��(5) : ");
		scanf("%d", &m); 
		
		printf("\n");
		printArr(arr, 0, n);
		printf("\n");
        
		if (m==1) { 
			bubbleSort(arr, n);
			printf("\n���� ���� (Bubble Sort) : �ٷ� ���� ���� �� ũ�� ��ü�ϱ�\n");
		} else if (m==2) {
    		selectionSort(arr, n);
    		printf("\n���� ���� (Selection Sort) : ���� ���� ���� ������ �տ������� ���ʴ�� ��ü�ϱ�\n");
		} else if (m==3) {
    		insertionSort(arr, n);
    		printf("\n���� ���� (Insertion Sort) : �տ������� �ϳ��� �����ϸ鼭 �˸��� ��ġ�� �����ϱ�\n");
    	} else if (m==4) {
    		mergeSort(arr, 0, n-1); /// 'n' -> 'n-1'
    		printf("\n���� ���� (Merge Sort) : �߰� �ɰ� �� �����ϸ� ��ġ��\n");
		} else {
			quickSort(arr, 0, n-1);
			printf("\n");
			printArr(arr, 0, n);
			printf("\n\n�� ���� (Quick Sort) : �ϳ��� �����ϸ鼭 �׺��� ������ ����, ū�� ���������� �̵���Ű��\n");
		}
		printf("--------------------------------\n");
	}
}
