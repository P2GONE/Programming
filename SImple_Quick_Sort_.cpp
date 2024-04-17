#include <stdio.h>
#include <stdlib.h> 
#pragma warning(disable : 4996)

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    // ������ �ǹ� ����
    int pivotIndex = low + rand() % (high - low + 1);
    int pivot = arr[pivotIndex];

    // �ǹ��� �迭�� �� ������ �̵�
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

    // �ǹ��� ��ġ�� �ٲ���
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

    //������ �� ������ �Է¹���
    scanf("%d", &total_num);

    // �������� �迭 �Ҵ�
    arr = (int*)malloc(total_num * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.");
        return -1; // indicate failure
    }

    //�Էµ��� �迭�� ������
    for (int i = 0; i < total_num; i++) {
        scanf("%d", &arr[i]);
    }

    // calling quickSort() to sort the given array 
    quickSort(arr, 0, total_num - 1);

    // �Էµ� �� ���
    for (int i = 0; i < total_num; i++) {
        printf("%d\n", arr[i]);
    }

    // �������� �Ҵ��� �޸� ����
    free(arr);

    return 0;
}
