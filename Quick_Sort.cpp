#include <stdio.h>
#include <stdlib.h> 
#pragma warning(disable : 4996)


// Function to swap two elements 
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high)
{

    // initialize pivot to be the first element 
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {

        // condition 1: find the first element greater than 
        // the pivot (from starting) 
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        // condition 2: find the first element smaller than 
        // the pivot (from last) 
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

// QuickSort function 
void quickSort(int arr[], int low, int high)
{
    if (low < high) {

        // call Partition function to find Partition Index 
        int partitionIndex = partition(arr, low, high);

        // Recursively call quickSort() for left and right 
        // half based on partition Index 
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
    //printf("\nInput values: ");
    for (int i = 0; i < total_num; i++) {
        printf("%d\n", arr[i]);
    }

    // �������� �Ҵ��� �޸� ����
    free(arr);

    return 0;
}
