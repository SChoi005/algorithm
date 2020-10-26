#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;

    cin >> n;

    vector<int> stock;

    //주식 삽입
    for (int i = 0; i < n; i++)
    {
        int s;
        cin >> s;
        stock.push_back(s);
    }

    int min1 = stock[0], min2 = -1;
    int max1 = stock[0];
    int count = 0;
    int benefit = max1 - min1;

    //목표 -> n
    for (int i = 0; i < stock.size(); i++)
    {
        if (max1 < stock[i] && min2 == -1)
        {
            max1 = stock[i];
        }
        if (min1 >= stock[i] && min2 == -1)
        {
            min2 = stock[i];
            count++;
        }
        if (count == 1 && min2 > stock[i])
        {
            min2 = stock[i];
        }

        if (count == 1 && (stock[i] - min2) >= benefit)
        {
            count = 0;
            min1 = min2;
            max1 = stock[i];
            min2 = -1;
        }
        benefit = max1 - min1;
    }

    //사는 가격, 파는가격, 최대이득 출력
    if (min1 == max1)
        cout << 0;
    else
        cout << min1 << " " << max1 << " " << benefit;
}