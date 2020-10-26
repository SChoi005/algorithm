#include <iostream>

using namespace std;

long long mod(int a, int n, int m, int* count)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
    {
        (*count)++;
        long long temp=mod(a, n / 2, m, count);
        return temp * temp % m;
    }
    else
    {
        (*count)++;
        return (long long)(a * mod(a, n - 1, m, count)) % m;
    }
}

int main()
{
    //양의정수 a, 음이아닌정수 n, 양의정수 m
    int a, n, m;

    cin >> a >> n >> m;

    int count = 0;

    long long mo = mod(a, n, m, &count);
    cout << count << endl << mo;
}