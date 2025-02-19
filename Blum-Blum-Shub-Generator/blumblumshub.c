#include<stdio.h>

int main() {
	long long int P = 401, Q = 677, S = 192035;
	long long int X[11];
	long int bit[11];

	long int N = P*Q;
	X[0] = (S*S)%N;
	bit[0] = X[0]%2;
	printf("Value of bit[%ld] = %d\n", 0 , bit[0]);
	for (int i = 1; i<11	; i++) {
		X[i] = (X[i-1]*X[i-1])%N;
		if(X[i]<0) {
			X[i] += N;
		}
		bit[i] = X[i] % 2;
		printf("Value of bit[%ld] = %d\n", i, bit[i]);
	}

	for (int i = 0; i < 11; i++) {
		printf("Value of X[%lld] = %d\n", i , X[i]);
	}
}
