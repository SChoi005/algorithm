#include<iostream>
#include<vector>

using namespace std;

int check[1001];

int main(){
    int n, max=0;
    vector<int>num;

    cin>>n;

    for(int i=0; i<n; i++){
        int k;
        cin >>k;
        num.push_back(k-1);
    }

    for(int i=0; i<num.size(); i++){
        int count=1;

        //이미 지나간 곳이면 continue
        if(check[i]==-1)
            continue;

        int j=i;

        //자기자신을 사이클로하는게 아니라면
        if(num[j]!=j){
            check[j]=-1;
            while(1){
                j=num[j];
                //사이클이 완성되면 break
                if(i==j)
                    break;
                else{
                    check[j]=-1;
                    count++;
                }
            }
        }
        //최댓값 개수 비교
        if(max<count)
            max=count;
    }   
    cout<<max;
}   