#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable : 4996)

// LPS 배열을 생성하는 함수
void computeLPSArray(char* pattern, int M, int* lps) {
    // pattern : 접두사-접미사 일치를 계산할 패턴 문자열
    // M : 패턴 문자열의 길이
    // lps : LPS 배열로, 각 인덱스에 해당 위치까지의 접두사와 접미사의 최대 일치 길이를 저장함.

    int length = 0; // 이전 부분 일치의 길이
    lps[0] = 0; // lps[0]은 항상 0
    int i = 1;

    // 패턴의 끝까지 LPS 배열을 계산
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        // 문자가 일치하는 경우 index를 올리면서 다음 문자로 이동시킴
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            // 이전 일치한 부분이 있는 경우 length를 이전 LPS 값으로 설정하여 계속 비교
            else {
                lps[i] = 0;
                i++;
            }
            // 문자가 일치하하는 부분이 없는 경우 현재 인덱스 i에 대해 LPS 값을 0으로 설정함
        }
    }
}

// KMP 알고리즘을 사용하여 텍스트 내에서 패턴을 검색하는 함수
int KMPSearch(char* pattern, char* text) {
    // pattern : 찾고자 하는 패턴 문자열, 기준 문자열 (정답 문자열)
    // text : 패턴을 찾을 대상, target 문자열
    int M = strlen(pattern);
    int N = strlen(text);

    // 패턴의 각 위치에서 접두사와 접미사의 최대 일치 길이를 저장하는 배열이 LPS
    // 주어진 패턴에 대해 LPS 배열을 계산함
    int* lps = (int*)malloc(M * sizeof(int));
    if (lps == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    computeLPSArray(pattern, M, lps);

    int i = 0; // 텍스트의 인덱스
    int j = 0; // 패턴의 인덱스
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            //printf("패턴이 텍스트의 인덱스 %d에서 발견되었습니다.\n", i - j);
            j = lps[j - 1];
            free(lps);
            return 1;
        }
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    free(lps);
    return 0;
}

int main() {
    int N, Q;
    // N : 과학자의 수, Q : 쿼러의 수
    scanf("%d %d", &N, &Q);

    // N 동적할당, 배열 동적할당
    char** names = (char**)malloc(N * sizeof(char*));
    if (names == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 컴퓨터 과학자의 이름 입력
    for (int i = 0; i < N; i++) {
        names[i] = (char*)malloc(1001 * sizeof(char));
        if (names[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        scanf(" %[^\n]", names[i]);  // 공백을 포함한 문자열 입력

        // 대문자만 추출하여 저장
        int j = 0; // 대문자를 저장할 위치
        for (int k = 0; names[i][k] != '\0'; k++) {
            if (isupper(names[i][k])) {
                names[i][j++] = names[i][k];
            }
        }
        names[i][j] = '\0'; // 문자열의 끝을 나타내는 NULL 문자 추가
    }


    // 쿼리 결과를 저장하는 배열
    int* results = (int*)malloc(Q * sizeof(int));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    // 쿼리 입력 및 결과 저장
    char query[1001];
    for (int i = 0; i < Q; i++) {
        scanf("%s", query);
        int found_flag = 0;

        // 각 컴퓨터 과학자의 이름에 대해 쿼리 문자열을 검색
        for (int j = 0; j < N; j++) {
            if (KMPSearch(query, names[j])) { // 패턴 매칭 수행
                found_flag = 1; // 매칭된 경우 found_flag를 1로 설정
                break;
            }
        }
        // 쿼리에 대한 결과 저장
        results[i] = found_flag;
    }

    // 쿼리 결과 출력
    for (int i = 0; i < Q; i++) {
        if (results[i] == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    // 동적 할당된 메모리를 해제
    for (int i = 0; i < N; i++) {
        free(names[i]);
    }
    free(names);
    free(results);

    return 0;
}
