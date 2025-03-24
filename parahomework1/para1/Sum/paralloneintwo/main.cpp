#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

#define maxN 10000000
int a[maxN];
long long sum=0;

void tosum(int start, int end, long long& sum) {
    // it is important to choose a number
    if (end - start <= 450000) {
        for (int i = start; i <= end; i++) {
            sum += a[i];
        }
    }
    else {
        // make it
        int mid = (start + end) / 2;
        long long lsum = 0, rsum = 0;
        thread left_thread([&]() { tosum(start, mid, lsum); });
        thread right_thread([&]() { tosum(mid + 1, end, rsum); });

        // wait
        left_thread.join();
        right_thread.join();

        // add
        sum = lsum + rsum;
    }
}

int main() {
    int t=50;
    for (int i = 0; i < maxN; i++) {
        a[i] = i;
    }

    while(t--)
    {
        tosum(0, maxN - 1, sum);
    }

    cout << "Total sum: " << sum << endl;

    return 0;
}
