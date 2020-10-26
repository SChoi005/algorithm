#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

int partition(vector<int>&num, int left, int right){
    //피봇을 랜덤하게 선택
    int pivotIndex = rand()%(right+1-left)+left;
    int pivot=num[pivotIndex];

    //피봇을 맨 왼쪽과 교환한다.
    int tmp = num[pivotIndex];
    num[pivotIndex] = num[left];
    num[left] = tmp;

    int low=left+1;
    int high=right;

    while(low<=high){
        //pivot보다 큰 low인덱스를 찾음
        while(low<=right && pivot>=num[low]){
            low++;
        }
        //pivot보다 작은 high인덱스를 찾음
        while(high>=left+1 && pivot<=num[high]){
            high--;
        }
        //low와 high를 바꿈
        if(low<=high){
            int temp=num[low];
            num[low]=num[high];
            num[high]=temp;
        }
    }
    //high가 멈춘곳과 pivot값을 교환함
    int temp=num[left];
    num[left]=num[high];
    num[high]=temp;
    
    //high값을 기준으로 분리해야하므로 high리턴
    return high;
}

void quickSort(vector<int>&num, int left, int right){
    if(left<=right){
        int pivot=partition(num,left,right);
        quickSort(num,left,pivot-1);
        quickSort(num,pivot+1,right);
    }
}

int main(){

    int n;
    vector<int>num;

    cin>>n;

    for(int i=0; i<n; i++){
        int k;
        cin>>k;
        num.push_back(k);
    }
    //퀵정렬 -> O(nlogn)
    quickSort(num, 0, num.size()-1);

    for(auto i : num)
        cout<<i<<' ';
    
}