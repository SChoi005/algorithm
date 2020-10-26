#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, count=0;
    vector<int>num;

    cin>>n;
    
    for(int i=0; i<n;i++){
        int k;
        cin>>k;
        num.push_back(k-1);
    }

    for(int i=0; i<num.size(); i++){
        //자기 자리에 앉았을 경우 넘어감
        if(i==num[i])
            continue;

        int j=i;
        
        while(1){
            int temp=num[j];
            //자기자리에 배치 됐을때 break
            if(j==temp)
                break;
            //루프를 돌때마다 꼬리를 물듯이 바꿔줌
            int k=num[temp];
            num[temp]=num[j];
            num[j]=k;
            j=k;
            count++;    
        }
    }
    
    cout<<count;
}