#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int> k, int first, int last, int key, int *check)
{

    while (first <= last)
    {
        int mid = (first + last) / 2;
        *check = mid;
        if (k[mid] > key)
        {
            last = mid - 1;
        }
        else if (k[mid] < key)
        {
            first = mid + 1;
        }
        else
            return mid;
    }
    return -1;
}

int main()
{
    int n, x;
    vector<int> key;

    cin >> n >> x;

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        key.push_back(k);
    }

    int check;
    int bs = binarySearch(key, 0, key.size(), x, &check);

    if (bs == -1)
    {
        if (key[key.size() - 1] < x)
            cout << key[key.size() - 1] << ' ' << key.size() - 1;
        else if (key[0] > x)
            cout << key[0] << ' ' << 0;
        else
        {
            if (key[check] - x >= x - key[check - 1])
                cout << key[check - 1] << ' ' << check - 1;
            else
                cout << key[check] << ' ' << check;
        }
    }
    else
        cout << bs;
}