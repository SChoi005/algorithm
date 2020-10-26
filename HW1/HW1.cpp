#include<iostream>
#include<fstream>
#include <time.h>

using namespace std;

#define SIZE 100000

int main()
{
    int stockPrice[SIZE];
    int n;
    clock_t start, finish;
    double duration;

    fstream fin;
    fin.open("C:/Users/82105/Desktop/Algorithm/HW1/testcase.txt");

    for (int k = 0; k < 10; k++) {
        start = clock();
        
        fin >> n;

        for (int i = 0; i < n; i++)
            fin >> stockPrice[i];
        int maxLength, currentLength;

        // 알고리즘1 O(n^3)
        maxLength = 0;
        for (int i = 0; i < n; i++) 
           for (int j = i + 1; j < n; j++) {  // -> i에서 어디까지 탐색할지 지정
               currentLength = 0;
               for (int k = i; k < j; k++)    // -> i부터 j까지 길이를 잰다
                   if (stockPrice[k] < stockPrice[k + 1])
                       currentLength++;
                   else
                       break;
               if (maxLength < currentLength)
                   maxLength = currentLength;
           }
        printf("%d\n", maxLength);


        // 알고리즘 2 O(n^2)
        // maxLength = 0;
        // for (int i = 0; i < n; i++) { 
        //    currentLength = 0;
        //    for (int j = i + 1; j < n; j++)  // -> i부터 끝까지 길이를 잰다
        //        if (stockPrice[j - 1] < stockPrice[j])
        //            currentLength++;
        //        else
        //            break;
        //    if (maxLength < currentLength)
        //        maxLength = currentLength;
        // }
        // printf("%d\n", maxLength);

        //알고리즘3 O(n)
        // maxLength = 0;
        // currentLength = 0;
        // for (int i = 1; i < n; i++) {  // -> 루프를 한번돌면서 길이가 끊기면 currentLength=0으로 초기화
        //     if (stockPrice[i] > stockPrice[i - 1]) {
        //         currentLength++;
        //         if (maxLength < currentLength)
        //             maxLength = currentLength;
        //     }
        //     else
        //         currentLength = 0;
        // }

        // printf("%d\n", maxLength);

        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("testcase%d count=%d time = %f\n", k+1,n,duration);
    }

    fin.close();

    return 0;
}