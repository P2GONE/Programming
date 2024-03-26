#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

int size;
clock_t start, end;
double cpu_time_used_merge;
double cpu_time_used_insertion;

void merge(int* array, int left_start, int left_end, int right_start, int right_end) {
    int left_size = left_end - left_start + 1;
    int right_size = right_end - right_start + 1;
    int merged_size = left_size + right_size;

    int* merged_array = (int*)malloc(sizeof(int) * merged_size);

    int i = left_start, j = right_start, k = 0;
    while (i <= left_end && j <= right_end) {
        if (array[i] <= array[j]) {
            merged_array[k++] = array[i++];
        }
        else {
            merged_array[k++] = array[j++];
        }
    }

    while (i <= left_end) {
        merged_array[k++] = array[i++];
    }

    while (j <= right_end) {
        merged_array[k++] = array[j++];
    }

    for (int m = 0; m < merged_size; m++) {
        array[left_start + m] = merged_array[m];
    }

    free(merged_array);
}

void merge_sort(int* array, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);
        merge(array, start, mid, mid + 1, end);
    }
}


void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL)); // 난수 발생기 초기화

    //사용자에게 크기, size를 입력받음
    printf("입력 크기를 입력하세요 : ");
    scanf("%d", &size);

    // 배열 생성 및 랜덤 값으로 초기화
    int* array_merge = (int*)malloc(sizeof(int) * size);
    int* array_insertion = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        array_merge[i] = rand();
        array_insertion[i] = array_merge[i];
    }

    // 난수 출력, 입력받은 만큼 생성함. 
    /*
    printf("random array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    */


    // Merge Sort 적용, 시간 측정
    start = clock();
    merge_sort(array_merge, 0, size - 1);
    end = clock();
    cpu_time_used_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Insertion Sort 적용, 시간 측정
    start = clock();
    insertionSort(array_insertion, size - 1);
    end = clock();
    cpu_time_used_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n\n*****Sorted array****\n\n");

    // 병합 정렬된 배열 출력, 해당 정렬이 걸린 시간 출력 
    printf("time required : %f\n", cpu_time_used_merge);
    /*
    printf("merge array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    printf("\n");
    */

    // 삽입 정렬된 배열 출력, 해당 정렬이 걸린 시간 출력
    printf("time required : %f\n", cpu_time_used_insertion);
    /*
    printf("insertion array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_insertion[i]);
    }
    printf("\n");
    */

    // 동적 할당된 메모리 해제
    free(array_merge);
    free(array_insertion);
    return 0;
}