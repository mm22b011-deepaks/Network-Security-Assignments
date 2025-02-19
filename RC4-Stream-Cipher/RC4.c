#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256   // 2^8

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(char *key, unsigned char *S) {
    int len = strlen(key);
    int j = 0;

    for (int i = 0; i < N; i++) {
        S[i] = i;  
    }

    for (int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;  
        swap(&S[i], &S[j]);  
    }

    return 0;
}

int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext, int print) {
    int i = 0, j = 0;
    int t;

    for (size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);

        t = (S[i] + S[j]) % N;  
        ciphertext[n] = S[t] ^ plaintext[n];  

        if (print == 1) {
            printf("The value of K[%zu] is %d\n", n, S[t]);
        }
    }

    return 0;
}

int RC4(char *key, char *plaintext, unsigned char *ciphertext, int print) {
    unsigned char S[N];
    KSA(key, S);  
    PRGA(S, plaintext, ciphertext, print);  
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <key> <plaintext>\n", argv[0]);
        return -1;
    }

    int print;
    printf("Do you want to print all the keys generated?\nIf yes, enter 1, or 0: ");
    scanf("%d", &print);

    unsigned char *ciphertext = malloc(sizeof(unsigned char) * strlen(argv[2]));

    char key1[] = "1234";
    printf("\n===============> Key 1 = 1234 <===============\n");
    RC4(key1, argv[2], ciphertext, print);  

    printf("\n");
    for (size_t i = 0; i < 4; i++) {
        int C1 = ciphertext[i] ^ argv[2][i]; 
        printf("The value of C1[%zu] for plaintext P1[%zu] is: %d\n", i, i, C1);
    }
    printf("\n");

    char key2[] = "8765";
    printf("\n===============> Key 2 = 8765 <===============\n");
    RC4(key2, argv[2], ciphertext, print); 

    printf("\n");
    for (size_t i = 0; i < 3; i++) {
        int C2 = ciphertext[i] ^ argv[2][i]; 
        printf("The value of C2[%zu] for plaintext P2[%zu] is: %d\n", i, i, C2);
    }
    printf("\n");

    free(ciphertext);  
    return 0;
}

