#include <iostream>

#define maxN 10000000
int a[maxN];
long long sum=0;
void parallel_sum(int a[maxN]) {
    for (int m = maxN; m > 1; m /= 2) { // log(N) steps
        for (int i = 0; i < m / 2; i++) {
            a[i] = a[i * 2] + a[i * 2 + 1]; // sort in front
        }
    }
}

int main() {
    for (int i = 0; i < maxN; i++) {
        a[i]=i;
    }
    int t=50;
    while(t--)
    {
        parallel_sum(a);
        sum+=a[0];
    }
    return 0;
}
