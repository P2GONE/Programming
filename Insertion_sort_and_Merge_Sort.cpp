#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

int size;
clock_t start, end;
double cpu_time_used_merge;
double cpu_time_used_insertion;

//Merge �˰��� (����)
void merge(int* array, int left_start, int left_end, int right_start, int right_end) {
    //array �κ��� array_merge�迭, left_start, left_end�� ���� �κ� �迭�� ���۰� ��, right_start, right_end�� ������ �迭�� ���۰� ����
    int left_size = left_end - left_start + 1;
    // ���� �κ� �迭�� ũ�⸦ �����
    int right_size = right_end - right_start + 1;
    // ������ �κ� �迭�� ũ�⸦ ������
    int merged_size = left_size + right_size;
    // ���յ� �迭�� ũ�⸦ �����. �̴� ������ �κ� �迭�� ���� �κ� �迭�� ũ���� �հ� ����
    int* merged_array = (int*)malloc(sizeof(int) * merged_size);
    // ���յ� �迭�� ������ �޸𸮸� ���� �Ҵ���
    int i = left_start, j = right_start, k = 0;
    // i�� ���� �κ� �迭�� ������, j�� ������ �κФ� �迭�� ��������
    while (i <= left_end && j <= right_end) {
        //�� �κ� �迭�� ���ϸ鼭 ���� ���� ���յ� �迭�� ����. ���� �κ� �迭�� ������ �κ� �迭�� ���ÿ� ��ȸ�ϸ鼭 ���� ���� merged_array�� �ְ�, �ش� �κ� �迭�� �ε����� ������Ŵ
        if (array[i] <= array[j]) {
            merged_array[k++] = array[i++];
        }
        else {
            merged_array[k++] = array[j++];
        }
    }
    // ���� �κ� �迭�� ���� ��쿡�� ���� ���ҵ��� ���������� merged_array�� ����
    while (i <= left_end) {
        merged_array[k++] = array[i++];
    }
    // ������ �κ� �迭�� ���� ��쿡�� ���� ���ҵ��� ���������� merged_array�� ����
    while (j <= right_end) {
        merged_array[k++] = array[j++];
    }
    // ���յ� �迭�� ���� �迭�� array�� ������. �̸� ���� array�� ���ĵ� ������
    for (int m = 0; m < merged_size; m++) {
        array[left_start + m] = merged_array[m];
    }
    // ���տ� ���� ���� �Ҵ�� �޸𸮸� ������ 
    free(merged_array);
}

//Merge sort �˰���
void merge_sort(int* array, int start, int end) {
    // ���� ������ �����ϴ� �Լ��� array�� array_merge �迭�� 
    // start�κ��� ������, end�� ������ 
    if (start < end) {
        // ��� ȣ���� ������ ������ ������. ���� �ε����� start�� ���� �ε��� end ���� ���� ��쿡�� �迭�� ������
        int mid = (start + end) / 2;
        //�迭�� ������ ������ ���� �߰� ������ �����. �� ������ �������� ���� �κа� ������ �κ� �迭�� ����
        merge_sort(array, start, mid);
        // �迭�� ���� �κ� �迭�� ��������� ������. ���� �ε����� �״���̰�, ���� �ε����� �߰� ������ mid�� ������
        merge_sort(array, mid + 1, end);
        // �迭�� ������ �κ� �迭�� ��������� ������. ���� �ε����� �߰� ������ ���� ������ 'mid + 1'�� �����ǰ�, ���� �ε����� �״����.
        merge(array, start, mid, mid + 1, end);
        // ���ĵ� ���� �κ� �迭�� ������ �κ� �迭�� ������. �̸� ���� merge �Լ��� ȣ����. �� �Լ��� ���ĵ� �� �κ� �迭�� �޾Ƽ� �ϳ��� ���ĵ� �迭�� ������
    }
}

//Insert sort �˰���
void insertionSort(int arr[], int n) {
    //arr[]�� array_insertion(������ ä���� �迭), n�� size(��ü ũ��)��
    int i, key, j;
    for (i = 1; i < n; i++) {
        //���� ���� �Լ��� key�� ������
        key = arr[i];
        //���� ����� �ٷ� ���� ��Һ��� �����Ͽ� �̹� ���ĵ� �κа� ���� �� �ֵ��� j ������ �ʱ�ȭ��
        j = i - 1;
        //���� ��Ҹ� ������ ��ġ�� �����ϱ� ����, �̹� ���ĵ� �κ��� �������� ��ȸ�ϸ鼭 ���� ��� key ���� ū ���� ���� ��ҵ��� ���������� ��ĭ�� �̵���Ŵ
        while (j >= 0 && arr[j] > key) {
            //���� ��Һ��� ū ���� ���� ��ҵ��� ���������� �� ĭ�� �̵���Ŵ
            arr[j + 1] = arr[j];
            //j�� �� ĭ �������� ���ϸ鼭 ���� �񱳸� ������, �� ���� ��Һ��� ū ���� ������ ���� �� ���� while������ �񱳸� �Լ� ������
            j = j - 1;
        }
        //������ ��ġ(���� ��Һ��� ������ ���� ũ�� ����)�� ã�� �� ���� ��� 'key'�� �ش� ��ġ�� ������
        arr[j + 1] = key;
    }
}



int main() {
    srand(time(NULL)); // ���� �߻��� �ʱ�ȭ

    //����ڿ��� ũ��, size�� �Է¹���
    printf("�Է� ũ�⸦ �Է��ϼ��� : ");
    scanf("%d", &size);

    // �迭 ���� �� ���� ������ �ʱ�ȭ
    // array_merge�� merge sort���� ����� �迭�̰�, array_insertion�� insertion sort���� ����� �迭��
    int* array_merge = (int*)malloc(sizeof(int) * size);
    int* array_insertion = (int*)malloc(sizeof(int) * size);

    // rand()�� ���� array_merge�� ������ ����
    // array_merge �迭�� ������ array_insertion �迭�� ������ 
    for (int i = 0; i < size; i++) {
        array_merge[i] = rand();
        array_insertion[i] = array_merge[i];
    }

    // array_merge �迭�� ������ �����
    // array_merge �迭�� ������ rand()�Լ��� ������� ��������
    printf("random array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }

    // Merge Sort ����, �˰��� �ð� ����
    // start�� end�� �˰��� ���۽ð��� ����ð��� ������
    start = clock();
    // array_merge�� size�� ���� sorting�� ������
    merge_sort(array_merge, 0, size - 1);
    end = clock();
    // cpu_time_used_merge�� ���۽ð��� ����ð��� ���̷� �˰��� �ð��� ����
    cpu_time_used_merge = ((double)(end - start)) / CLOCKS_PER_SEC;


    // Insertion Sort ����, �˰��� �ð� ����
    // start�� end�� �˰��� ���۽ð��� ����ð��� ������
    start = clock();
    // array_insertion�� size�� ���� sorting�� ������
    insertionSort(array_insertion, size - 1);
    end = clock();
    // cpu_time_used_insertion�� ���۽ð��� ����ð��� ���̷� �˰��� �ð��� ����
    cpu_time_used_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n\n*****Sorted array****\n\n");

    // Merge sort�� �ɸ� �ð� �����
    printf("Merge sort time required : %f\n", cpu_time_used_merge);
    // Merage sort�� ���ĵ� �迭�� �����
    printf("Merge sorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    printf("\n");


    // Insert sort�� �ɸ� �ð� �����
    printf("Insert sort time required : %f\n", cpu_time_used_insertion);
    // Insert sort�� ���ĵ� �迭�� ����� 
    printf("Insert sorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_insertion[i]);
    }
    printf("\n");

    // sorting_result_202235405.txt ���Ͽ� ���ĵ� �迭 ������
    FILE* sorted_file = fopen("sorting_result_202235405.txt", "w");
    if (sorted_file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return 1;
    }
    //Merge Sort�� ���ĵ� ����� sorting_result_202235405.txt�� ������
    fprintf(sorted_file, "****Merge Sort Result : ****\n");
    for (int i = 0; i < size; i++) {
        fprintf(sorted_file, "%d\n", array_merge[i]);
    }
    //Insert Sort�� ���ĵ� ����� sorting_result_202235405.txt�� ������
    fprintf(sorted_file, "****Insert Sort Result : ****\n");
    for (int i = 0; i < size; i++) {
        fprintf(sorted_file, "%d\n", array_insertion[i]);
    }
    //������ ������ 
    fclose(sorted_file);

    // ���� �Ҵ�� �޸� ������
    free(array_merge);
    free(array_insertion);
    return 0;
}
