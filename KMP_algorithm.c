#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable : 4996)

// LPS �迭�� �����ϴ� �Լ�
void computeLPSArray(char* pattern, int M, int* lps) {
    // pattern : ���λ�-���̻� ��ġ�� ����� ���� ���ڿ�
    // M : ���� ���ڿ��� ����
    // lps : LPS �迭��, �� �ε����� �ش� ��ġ������ ���λ�� ���̻��� �ִ� ��ġ ���̸� ������.

    int length = 0; // ���� �κ� ��ġ�� ����
    lps[0] = 0; // lps[0]�� �׻� 0
    int i = 1;

    // ������ ������ LPS �迭�� ���
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        // ���ڰ� ��ġ�ϴ� ��� index�� �ø��鼭 ���� ���ڷ� �̵���Ŵ
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            // ���� ��ġ�� �κ��� �ִ� ��� length�� ���� LPS ������ �����Ͽ� ��� ��
            else {
                lps[i] = 0;
                i++;
            }
            // ���ڰ� ��ġ���ϴ� �κ��� ���� ��� ���� �ε��� i�� ���� LPS ���� 0���� ������
        }
    }
}

// KMP �˰����� ����Ͽ� �ؽ�Ʈ ������ ������ �˻��ϴ� �Լ�
int KMPSearch(char* pattern, char* text) {
    // pattern : ã���� �ϴ� ���� ���ڿ�, ���� ���ڿ� (���� ���ڿ�)
    // text : ������ ã�� ���, target ���ڿ�
    int M = strlen(pattern);
    int N = strlen(text);

    // ������ �� ��ġ���� ���λ�� ���̻��� �ִ� ��ġ ���̸� �����ϴ� �迭�� LPS
    // �־��� ���Ͽ� ���� LPS �迭�� �����
    int* lps = (int*)malloc(M * sizeof(int));
    if (lps == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    computeLPSArray(pattern, M, lps);

    int i = 0; // �ؽ�Ʈ�� �ε���
    int j = 0; // ������ �ε���
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            //printf("������ �ؽ�Ʈ�� �ε��� %d���� �߰ߵǾ����ϴ�.\n", i - j);
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
    // N : �������� ��, Q : ������ ��
    scanf("%d %d", &N, &Q);

    // N �����Ҵ�, �迭 �����Ҵ�
    char** names = (char**)malloc(N * sizeof(char*));
    if (names == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // ��ǻ�� �������� �̸� �Է�
    for (int i = 0; i < N; i++) {
        names[i] = (char*)malloc(1001 * sizeof(char));
        if (names[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        scanf(" %[^\n]", names[i]);  // ������ ������ ���ڿ� �Է�

        // �빮�ڸ� �����Ͽ� ����
        int j = 0; // �빮�ڸ� ������ ��ġ
        for (int k = 0; names[i][k] != '\0'; k++) {
            if (isupper(names[i][k])) {
                names[i][j++] = names[i][k];
            }
        }
        names[i][j] = '\0'; // ���ڿ��� ���� ��Ÿ���� NULL ���� �߰�
    }


    // ���� ����� �����ϴ� �迭
    int* results = (int*)malloc(Q * sizeof(int));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    // ���� �Է� �� ��� ����
    char query[1001];
    for (int i = 0; i < Q; i++) {
        scanf("%s", query);
        int found_flag = 0;

        // �� ��ǻ�� �������� �̸��� ���� ���� ���ڿ��� �˻�
        for (int j = 0; j < N; j++) {
            if (KMPSearch(query, names[j])) { // ���� ��Ī ����
                found_flag = 1; // ��Ī�� ��� found_flag�� 1�� ����
                break;
            }
        }
        // ������ ���� ��� ����
        results[i] = found_flag;
    }

    // ���� ��� ���
    for (int i = 0; i < Q; i++) {
        if (results[i] == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    // ���� �Ҵ�� �޸𸮸� ����
    for (int i = 0; i < N; i++) {
        free(names[i]);
    }
    free(names);
    free(results);

    return 0;
}
