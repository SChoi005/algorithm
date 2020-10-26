#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int temp[100001];

void merge(vector<int> &num, int first, int mid, int last)
{
    int i = first;
    int j = mid + 1;
    int k = first;

    while (i <= mid && j <= last)
    {
        if (num[i] <= num[j])
        {
            temp[k] = num[i];
            i++;
        }
        else
        {
            temp[k] = num[j];
            j++;
        }
        k++;
    }

    if (i > mid)
    {
        for (int t = j; t <= last; t++)
        {
            temp[k] = num[t];
            k++;
        }
    }
    else
    {
        for (int t = i; t <= mid; t++)
        {
            temp[k] = num[t];
            k++;
        }
    }

    for (int t = first; t <= last; t++)
        num[t] = temp[t];

}

void mergeSort(vector<int> &num, int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergeSort(num, first, mid);
        mergeSort(num, mid + 1, last);
        merge(num, first, mid, last);
    }
}

int binarySearch(vector<int> k, int first, int last, int key, int *check)
{
    last= last-1;
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
    int n, s;
    int f = 0, l = 0;
    long long sum = -9223372036854775807;

    // fstream fin;
    // fin.open("C:/Users/82105/Desktop/Algorithm/testcase10000.txt");

    vector<int> num;

    // fin >>n;
    // for (int i = 0; i < n; i++)
    // {
    //     int k;
    //     fin >> k;
    //     num.push_back(k);
    // }
    
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        num.push_back(k);
    }

    cin >> s;

    mergeSort(num, 0, num.size() - 1);

    //O(n)알고리즘
    int first=0, last=num.size()-1;

    while(first<last){
        long long sumTemp=(long long)(num[first]+num[last]);
        if(sumTemp>s){//s보다 클때 -> last--를 해줘서 범위를 좁힘
            last--;
        }
        else if(sumTemp==s){ //s와 같을때 -> f, l을 갱신해줌, first++을 해주고 범위를 좁힘
            f=num[first];
            l=num[last];
            sum=sumTemp;
            first++;
        }
        else if(sumTemp<s){ //s보다 작을때 -> first++을 해주고 범위를 좁힘
            if(sumTemp>=sum){ //두수의 합이 sum보다 같거나 크면 f,l을 저장해줌
                f=num[first];
                l=num[last];
                sum=sumTemp;
            }
            first++;
        }
    }

    // O(nlogn)알고리즘

    // for (int i = 0; i< num.size(); i++)
    // {
    //     int check = 0;
         
    //     binarySearch(num, 0, num.size(), s - num[i], &check); //이진탐색을 이용하여 s-num[i]과 가장 근접한수를 찾음
        

    //     if (num[check] > s - num[i]) //찾았으나 크기가 크다면 인덱스를 줄여줌
    //     {
    //         check--;
    //     }

    //     if(num[check]<num[i]) //교차가 되는 시점에서는 브레이크를 걸고 나감
    //         break;
        
    //     long long sumTemp = (long long)(num[i] + num[check]);

    //     if (sumTemp <= s && sumTemp >= sum) //조건을 만족할때 두 수를 저장해줌
    //     {
    //         f = num[i];
    //         l = num[check];
    //         sum = sumTemp;
    //     }
    // }

    cout << f << ' ' << l;
}