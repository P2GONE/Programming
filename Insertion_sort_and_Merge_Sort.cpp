#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

int size;
clock_t start, end;
double cpu_time_used_merge;
double cpu_time_used_insertion;

//Merge 알고리즘 (병합)
void merge(int* array, int left_start, int left_end, int right_start, int right_end) {
    //array 부분은 array_merge배열, left_start, left_end는 왼쪽 부분 배열의 시작과 끝, right_start, right_end는 오른쪽 배열의 시작과 끝임
    int left_size = left_end - left_start + 1;
    // 왼쪽 부분 배열의 크기를 계산함
    int right_size = right_end - right_start + 1;
    // 오른쪽 부분 배열의 크기를 저장함
    int merged_size = left_size + right_size;
    // 병합된 배열의 크기를 계산함. 이는 오른쪽 부분 배열과 왼쪽 부분 배열의 크기의 합과 같음
    int* merged_array = (int*)malloc(sizeof(int) * merged_size);
    // 병합된 배열을 저장할 메모리를 동적 할당함
    int i = left_start, j = right_start, k = 0;
    // i는 왼쪽 부분 배열의 시작점, j는 오른쪽 부분ㄴ 배열의 시작점임
    while (i <= left_end && j <= right_end) {
        //두 부분 배열을 비교하면서 작은 값을 병합된 배열에 넣음. 왼쪽 부분 배열과 오른쪽 부분 배열을 동시에 순회하면서 작은 값을 merged_array에 넣고, 해당 부분 배열의 인덱스를 증가시킴
        if (array[i] <= array[j]) {
            merged_array[k++] = array[i++];
        }
        else {
            merged_array[k++] = array[j++];
        }
    }
    // 왼쪽 부분 배열이 남은 경우에는 남은 원소들을 순차적으로 merged_array에 넣음
    while (i <= left_end) {
        merged_array[k++] = array[i++];
    }
    // 오른쪽 부분 배열이 남은 경우에는 남은 원소들을 순차적으로 merged_array에 넣음
    while (j <= right_end) {
        merged_array[k++] = array[j++];
    }
    // 병합된 배열을 원래 배열인 array에 복사함. 이를 통해 array는 정렬된 상태임
    for (int m = 0; m < merged_size; m++) {
        array[left_start + m] = merged_array[m];
    }
    // 병합에 사용된 동적 할당된 메모리를 해제함 
    free(merged_array);
}

//Merge sort 알고리즘
void merge_sort(int* array, int start, int end) {
    // 병합 정렬을 수행하는 함수임 array는 array_merge 배열임 
    // start부분은 시작점, end는 끝점임 
    if (start < end) {
        // 재귀 호출을 종료할 조건을 설정함. 시작 인덱스가 start가 종료 인덱스 end 보다 작은 경우에만 배열을 정렬함
        int mid = (start + end) / 2;
        //배열을 반으로 나누기 위해 중간 지점을 계산함. 이 지점을 기준으로 왼쪽 부분과 오른쪽 부분 배열로 나눔
        merge_sort(array, start, mid);
        // 배열의 왼쪽 부분 배열을 재귀적으로 정렬함. 시작 인덱스는 그대로이고, 종료 인덱스는 중간 지점인 mid로 설정됨
        merge_sort(array, mid + 1, end);
        // 배열의 오른쪽 부분 배열을 재귀적으로 정렬함. 시작 인덱스는 중간 지점의 다음 지점인 'mid + 1'로 설정되고, 종료 인덱스는 그대로임.
        merge(array, start, mid, mid + 1, end);
        // 정렬된 왼쪽 부분 배열과 오른쪽 부분 배열을 병합함. 이를 통해 merge 함수를 호출함. 이 함수는 정렬된 두 부분 배열을 받아서 하나의 정렬된 배열로 병합함
    }
}

//Insert sort 알고리즘
void insertionSort(int arr[], int n) {
    //arr[]는 array_insertion(난수로 채워진 배열), n은 size(전체 크기)임
    int i, key, j;
    for (i = 1; i < n; i++) {
        //현재 비교할 함수를 key에 저장함
        key = arr[i];
        //현재 요소의 바로 이전 요소부터 시작하여 이미 정렬된 부분과 비교할 수 있도록 j 변수를 초기화함
        j = i - 1;
        //현재 요소를 적절한 위치에 삽입하기 위해, 이미 정렬된 부분을 역순으로 순회하면서 현재 요소 key 보다 큰 값을 가진 요소들을 오른쪽으로 한칸씩 이동시킴
        while (j >= 0 && arr[j] > key) {
            //현재 요소보다 큰 값을 가진 요소들을 오른쪽으로 한 칸씩 이동시킴
            arr[j + 1] = arr[j];
            //j를 한 칸 왼쪽으로 비교하면서 다음 비교를 진행함, 즉 현재 요소보다 큰 값을 가지지 않을 떄 까지 while문으로 비교를 게속 진행함
            j = j - 1;
        }
        //적절한 위치(현재 요소보다 오른쪽 값이 크지 않음)를 찾은 후 현재 요소 'key'를 해당 위치에 삽입함
        arr[j + 1] = key;
    }
}



int main() {
    srand(time(NULL)); // 난수 발생기 초기화

    //사용자에게 크기, size를 입력받음
    printf("입력 크기를 입력하세요 : ");
    scanf("%d", &size);

    // 배열 생성 및 랜덤 값으로 초기화
    // array_merge는 merge sort에서 사용할 배열이고, array_insertion은 insertion sort에서 사용할 배열임
    int* array_merge = (int*)malloc(sizeof(int) * size);
    int* array_insertion = (int*)malloc(sizeof(int) * size);

    // rand()를 통해 array_merge에 난수를 넣음
    // array_merge 배열의 내용을 array_insertion 배열에 복사함 
    for (int i = 0; i < size; i++) {
        array_merge[i] = rand();
        array_insertion[i] = array_merge[i];
    }

    // array_merge 배열의 내용을 출력함
    // array_merge 배열의 내용은 rand()함수로 만들어진 난수들임
    printf("random array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }

    // Merge Sort 적용, 알고리즘 시간 측정
    // start과 end로 알고리즘 시작시간과 종료시간을 측정함
    start = clock();
    // array_merge와 size를 통해 sorting을 진행함
    merge_sort(array_merge, 0, size - 1);
    end = clock();
    // cpu_time_used_merge에 시작시간과 종료시간의 차이로 알고리즘 시간을 구함
    cpu_time_used_merge = ((double)(end - start)) / CLOCKS_PER_SEC;


    // Insertion Sort 적용, 알고리즘 시간 측정
    // start과 end로 알고리즘 시작시간과 종료시간을 측정함
    start = clock();
    // array_insertion와 size를 통해 sorting을 진행함
    insertionSort(array_insertion, size - 1);
    end = clock();
    // cpu_time_used_insertion에 시작시간과 종료시간의 차이로 알고리즘 시간을 구함
    cpu_time_used_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n\n*****Sorted array****\n\n");

    // Merge sort가 걸린 시간 출력함
    printf("Merge sort time required : %f\n", cpu_time_used_merge);
    // Merage sort로 정렬된 배열을 출력함
    printf("Merge sorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_merge[i]);
    }
    printf("\n");


    // Insert sort가 걸린 시간 출력함
    printf("Insert sort time required : %f\n", cpu_time_used_insertion);
    // Insert sort로 정렬된 배열을 출력함 
    printf("Insert sorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array_insertion[i]);
    }
    printf("\n");

    // sorting_result_202235405.txt 파일에 정렬된 배열 저장함
    FILE* sorted_file = fopen("sorting_result_202235405.txt", "w");
    if (sorted_file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return 1;
    }
    //Merge Sort로 정렬된 결과를 sorting_result_202235405.txt에 저장함
    fprintf(sorted_file, "****Merge Sort Result : ****\n");
    for (int i = 0; i < size; i++) {
        fprintf(sorted_file, "%d\n", array_merge[i]);
    }
    //Insert Sort로 정렬된 결과를 sorting_result_202235405.txt에 저장함
    fprintf(sorted_file, "****Insert Sort Result : ****\n");
    for (int i = 0; i < size; i++) {
        fprintf(sorted_file, "%d\n", array_insertion[i]);
    }
    //파일을 종료함 
    fclose(sorted_file);

    // 동적 할당된 메모리 해제함
    free(array_merge);
    free(array_insertion);
    return 0;
}
