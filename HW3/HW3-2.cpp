#include<iostream>
#include<vector>

using namespace std;

int partition(vector<int>&num, int left, int right){
    int pivot=num[left];
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

int upperbound(vector<int> num, int key){

    int first = 0;
    int last = num.size();
    int mid;

    while(first < last){
        mid = (first + last) / 2;
        //mid의 값이 key값보다 작거나 같다면 시작점을 mid+1
        //같은값을 찾았다고 해도 상한선을 찾아야하기 때문에 mid+1
        if (num[mid] <= key){
            first = mid + 1;
        }//mid값이 작다면 end를 mid
        else{
            last = mid;
        }
    }
    return first;
}

int main(){
    int n, d, max=1;
    vector<int>num;
    
    cin>>n;

    for(int i=0; i<n;i++){
        int k;
        cin>>k;
        num.push_back(k);
    }

    cin>>d;

    //정렬 -> O(nlogn)
    quickSort(num, 0, num.size()-1);

    //O(nlogn)
    for(int i=0; i<num.size(); i++){
        //상한선 인덱스를 찾는다
        int temp = upperbound(num, num[i]+d);

        if(max<temp-i)
            max=temp-i;
    }
    cout<<max;
}