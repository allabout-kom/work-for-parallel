#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

#define maxN 10000000
int a[maxN];
long long sum=0;

long long tosum(int start, int end) {
    if (end - start <= 45000) { // 直接求和
        long long sum = 0;
        for (int i = start; i <= end; i++) {
            sum += a[i];
        }
        return sum;
    } else { // 递归划分
        int mid = (start + end) / 2;
        return tosum(start, mid) + tosum(mid + 1, end);
    }
}

int main() {
    int t=50;
    for (int i = 0; i < maxN; i++) {
        a[i] = i;
    }

    while(t--)
    {
        sum+=tosum(0, maxN - 1);
    }

    cout << "Total sum: " << sum << endl;

    return 0;
}
