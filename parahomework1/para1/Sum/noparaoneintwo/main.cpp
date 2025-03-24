#include<iostream>
using namespace std;
#define maxN 10000000//from a version
int a[maxN];
int sum=0;
long long tosum(int start, int end) {
    if (start > end) {
        return 0; // nothing in the tuple
    }
    if (start == end) {
        return a[start]; // just one
    }
    int mid = (start + end) / 2;
    long long lsum = tosum(start, mid);
    long long rsum = tosum(mid + 1, end);

    return lsum + rsum; //add them
}
int main()
{
    int t=50;
    for(int i=0;i<maxN;i++)
    {
        a[i]=i;
    }

    //split it into two tasks
    while(t--){
        sum+=tosum(0,maxN-1);//we can not reach maxN
    }


    return 0;
}
