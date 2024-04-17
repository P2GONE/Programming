#include <stdio.h>
#include <stdlib.h> 
#pragma warning(disable : 4996)

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    // 랜덤한 피벗 선택
    int pivotIndex = low + rand() % (high - low + 1);
    int pivot = arr[pivotIndex];

    // 피벗을 배열의 맨 앞으로 이동
    swap(&arr[pivotIndex], &arr[low]);

    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && arr[i] <= pivot) {
            i++;
        }
        while (j >= low + 1 && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // 피벗의 위치를 바꿔줌
    swap(&arr[low], &arr[j]);

    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

int main() {
    int total_num = 0;
    int* arr;

    //저장할 총 갯수를 입력받음
    scanf("%d", &total_num);

    // 동적으로 배열 할당
    arr = (int*)malloc(total_num * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.");
        return -1; // indicate failure
    }

    //입력들을 배열에 저장함
    for (int i = 0; i < total_num; i++) {
        scanf("%d", &arr[i]);
    }

    // calling quickSort() to sort the given array 
    quickSort(arr, 0, total_num - 1);

    // 입력된 값 출력
    for (int i = 0; i < total_num; i++) {
        printf("%d\n", arr[i]);
    }

    // 동적으로 할당한 메모리 해제
    free(arr);

    return 0;
}
