#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10000
#pragma warning(disable : 4996)

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

int main() {
    srand(time(NULL)); // ���� �߻��� �ʱ�ȭ

    // �迭 ���� �� ���� ������ �ʱ�ȭ
    int* array = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }

    printf("Original array:\n");
    // �迭�� ó�� 30�� ��� ���
    for (int i = 0; i < 30; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // original_array.txt ���Ͽ� ���� �迭 ����
    FILE* original_file = fopen("original_array.txt", "w");
    if (original_file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(original_file, "%d\n", array[i]);
    }
    fclose(original_file);

    // Merge Sort ����
    merge_sort(array, 0, size - 1);

    printf("\nSorted array:\n");
    // ���ĵ� �迭�� ó�� 30�� ��� ���
    for (int i = 0; i < 30; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // sorted_array.txt ���Ͽ� ���ĵ� �迭 ����
    FILE* sorted_file = fopen("sorted_array.txt", "w");
    if (sorted_file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(sorted_file, "%d\n", array[i]);
    }
    fclose(sorted_file);

    // ���� �Ҵ�� �޸� ����
    free(array);

    return 0;
}