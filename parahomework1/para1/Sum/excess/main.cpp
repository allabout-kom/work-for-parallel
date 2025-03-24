#include<iostream>
using namespace std;
#define maxN 10000000
int a[maxN];
long long sum,sum1=0,sum2=0;

int main()
{
    int t=50;
    for(int i=0;i<maxN;i++)
    {
        a[i]=i;
    }

    //split it into two tasks
    while(t--){
        for(int i=0;i<maxN;i+=2){
            sum1+=a[i];
            sum2+=a[i+1];
        }
    }
    sum=sum1+sum2;

    return 0;
}
