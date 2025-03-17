#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

void complex_function(int num) {
    char buffer[64];
    int sum = 0;

    for (int i = 0; i < num; i++) {
        sum += i * (i % 7);
        if (i % 15 == 0) printf("Iteration %d, sum: %d\n", i, sum);
    }
    snprintf(buffer, sizeof(buffer), "Final result: %d", sum);
    printf("%s\n", buffer);
}

int main() {
    int buf1[16];
    char buf2[20], buf3[64];

    printf("Enter 16 integers: ");
    for (int i = 0; i < 16; i++) scanf("%d", &buf1[i]);
    getchar();

    scanf("%s", buf2);
    strncpy(buf2, buf3, sizeof(buf2));

    for (int i = 0; i < 16; i++) printf("%d ", buf1[i]);

    complex_function(200);
    return 0;
}
