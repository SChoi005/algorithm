#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct SeatLength
{
    int sIndex;
    int eIndex;
};

struct Person
{
    int num;
    char prefer;
};

void rebuildHeap(vector<SeatLength> &len){
    int i;
    int current = 0;
    int n = len.size();

    while (2 * current + 1 < n){
        int leftChild = 2 * current + 1;
        int rightChild = leftChild + 1;
        int largerChild;

        int rLen = len[rightChild].eIndex - len[rightChild].sIndex;
        int lLen = len[leftChild].eIndex - len[leftChild].sIndex;
        int cLen = len[current].eIndex - len[current].sIndex;

        //더 큰 우선순위의 자식노드를 찾는다
        if (rightChild < n && rLen > lLen)
            largerChild = rightChild;
        else if (rightChild < n && rLen == lLen){
            if (len[leftChild].sIndex < len[rightChild].sIndex)
                largerChild = leftChild;
            else
                largerChild = rightChild;
        }
        else
            largerChild = leftChild;

        //자식노드와 현재부모노드를 비교하여 교환 판별
        if (cLen < (len[largerChild].eIndex - len[largerChild].sIndex)){
            SeatLength temp = len[current];
            len[current] = len[largerChild];
            len[largerChild] = temp;
        }
        else if (cLen == (len[largerChild].eIndex - len[largerChild].sIndex)){
            if (len[current].sIndex > len[largerChild].sIndex){
                SeatLength temp = len[current];
                len[current] = len[largerChild];
                len[largerChild] = temp;
            }
            else
                break;
        }
        else
            break;
        current = largerChild;
    }
}

void insertHeap(vector<SeatLength> &len, SeatLength k){
    //맨끝에 값을 삽입
    len.push_back(k);
    int kLen = k.eIndex - k.sIndex;
    int i = len.size() - 1;
    int parent = (i - 1) / 2;

    //부모와 비교하여 우선순위 조건을 만족하면 스왑
    while (i > 0){
        if (kLen > len[parent].eIndex - len[parent].sIndex){
            SeatLength temp = len[parent];
            len[parent] = len[i];
            len[i] = temp;
            i = parent;
            parent = (i - 1) / 2;
        }
        else if (kLen == len[parent].eIndex - len[parent].sIndex){
            if (k.sIndex < len[parent].sIndex){
                SeatLength temp = len[parent];
                len[parent] = len[i];
                len[i] = temp;
                i = parent;
                parent = (i - 1) / 2;
            }
            else
                break;
        }
        else
            break;
    }
}

void deleteHeap(vector<SeatLength> &len){
    //맨끝과 최댓값을 스왑해줌
    SeatLength temp = len[len.size() - 1];
    len[len.size() - 1] = len[0];
    len[0] = temp;

    //맨끝을 pop해주고 rebuildHeap로 재배열해줌
    len.pop_back();
    rebuildHeap(len);
}

int main(){
    //좌석수, 사람수, 좌석위치
    int n, k, q;
    string pf;             //선호도
    vector<int> seat;      //좌석
    vector<Person> p;       //사람
    vector<SeatLength> len; //자리길이(최대힙 이용)
    vector<int>query;       //출력할 좌석


    cin >> n >> k >> pf >> q;

    //사람 번호, 선호도 설정
    for (int i = 0; i < k; i++){
        Person t;
        t.num = i + 1;
        t.prefer = pf[i];
        p.push_back(t);
    }

    //사람 번호 초기화
    for (int i = 0; i < n; i++){
        int t;
        t = -1;
        seat.push_back(t);
    }
    //좌석 번호 설정
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        query.push_back(t-1);
    }

    //초기 len최댓값을 만들어서 넣어줌
    SeatLength f;
    f.sIndex = -1;
    f.eIndex = n;
    len.push_back(f);

    //좌석 앉히는 부분 -> O(nlogn)
    for (int i = 0; i < k; i++){
        int l = len[0].sIndex + len[0].eIndex; //최댓값 연산 O(1)

        //선호도에 따라 좌석 조정
        if (l % 2 == 0)
            l /= 2;
        else{
            if (p[i].prefer == 'R'){
                l = l / 2 + 1;
            }
            else
                l /= 2;
        }

        seat[l] = p[i].num;

        //len의 최댓값을 분할해줌
        SeatLength tempL, tempR;
        tempL.sIndex = len[0].sIndex;
        tempL.eIndex = l;
        tempR.sIndex = l;
        tempR.eIndex = len[0].eIndex;

        //힙 삽입연산 O(logn)
        if (tempL.eIndex - tempL.sIndex > 1)
            insertHeap(len, tempL);
        if (tempR.eIndex - tempR.sIndex > 1)
            insertHeap(len, tempR);
        //힙 root삭제연산 O(logn)
        deleteHeap(len);
    }

    //출력부분
    for (auto i : query)
        cout << seat[i] << ' ';
}