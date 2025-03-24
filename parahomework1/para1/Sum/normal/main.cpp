#include<iostream>
using namespace std;
#define maxN 10000000//10 billion
int a[maxN];
long long sum=0;

int main()
{
    int t=50;//50 rounds
    for(int i=0;i<maxN;i++)
    {
        a[i]=i;
    }

    //in normal way
    while(t--){
        for(int i=0;i<maxN;i++)
            sum+=a[i];
    }
    return 0;
}
