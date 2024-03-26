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
    srand(time(NULL)); // ���� �߻��� �ʱ�ȭ

    //����ڿ��� ũ��, size�� �Է¹���
    printf("�Է� ũ�⸦ �Է��ϼ��� : ");
    scanf("%d", &size);

    // �迭 ���� �� ���� ������ �ʱ�ȭ
    int* array_merge = (int*)malloc(sizeof(int) * size);
    int* array_insertion = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        array_merge[i] = rand();
        array_insertion[i] = array_merge[i];
    }

    // ���� ���, �Է¹��� ��ŭ ������. 
    /*
    printf("random array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    */


    // Merge Sort ����, �ð� ����
    start = clock();
    merge_sort(array_merge, 0, size - 1);
    end = clock();
    cpu_time_used_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Insertion Sort ����, �ð� ����
    start = clock();
    insertionSort(array_insertion, size - 1);
    end = clock();
    cpu_time_used_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n\n*****Sorted array****\n\n");

    // ���� ���ĵ� �迭 ���, �ش� ������ �ɸ� �ð� ��� 
    printf("time required : %f\n", cpu_time_used_merge);
    /*
    printf("merge array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    printf("\n");
    */

    // ���� ���ĵ� �迭 ���, �ش� ������ �ɸ� �ð� ���
    printf("time required : %f\n", cpu_time_used_insertion);
    /*
    printf("insertion array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_insertion[i]);
    }
    printf("\n");
    */

    // ���� �Ҵ�� �޸� ����
    free(array_merge);
    free(array_insertion);
    return 0;
}