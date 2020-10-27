#include<iostream>
#include<queue>

using namespace std;
int temp[10001];
void selectionSort(int arr[], int n){
    for(int i=n-1; i>=0 ; i--){
        int max = 0;
        for(int j=0; j<=i; j++){
            if(arr[max] < arr[j])
                max = j;
        }
        int temp = arr[max];
        arr[max] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int arr[], int n){
    int sorted = 1;
    for(int i=n-1; i>0; i--){
        for(int j=0; j<i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                sorted = 0;
            }
        }
        if(sorted == 1)
            break;
    }
}

void insertSort(int arr[], int n){
    for(int i=1; i<n; i++){
        int temp = arr[i];
        int index = 0;
        for(int j=i-1; j>=0; j--){
            if(arr[j] > temp){
                arr[j+1] = arr[j];
            }
            else{
                index = j+1;
                break;
            }
        }
        arr[index] = temp;
    }
}

int maxReturn(int a[], int first, int last){
    if(first<last){
        int mid = (first+last)/2;
        int lmax = maxReturn(a, first, mid);
        int rmax = maxReturn(a, mid+1, last);
        if(lmax > rmax)
            return lmax;
        else
            return rmax;        
    }
    else
        return a[first];
    
}

void merge(int a[], int first, int mid, int last)
{
    int i = first;
    int j = mid + 1;
    int k = first;

    while (i <= mid && j <= last){
        if (a[i] <= a[j]){
            temp[k] = a[i];
            i++;
        }
        else{
            temp[k] = a[j];
            j++;
        }
        k++;
    }

    if (i > mid){
        for (int t = j; t <= last; t++){
            temp[k] = a[t];
            k++;
        }
    }
    else{
        for (int t = i; t <= mid; t++){
            temp[k] = a[t];
            k++;
        }
    }

    for (int t = first; t <= last; t++)
        a[t] = temp[t];
}

void mergeSort(int a[], int first, int last){
    if(first<last){
        int mid = (first+last)/2;
        mergeSort(a, first, mid);
        mergeSort(a, mid+1, last);
        merge(a, first, mid, last);
    }

}

int partition(int num[], int left, int right){
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

void quickSort(int num[], int left, int right){
    if(left<=right){
        int pivot=partition(num,left,right);
        quickSort(num,left,pivot-1);
        quickSort(num,pivot+1,right);
    }
}

int kthSmallest(int a[], int first, int last, int k){
    if(k>0 && k<=last-first+1){
        int pos = partition(a, first, last);
        cout<< pos<<endl;
        if(pos-first == k-1)
            return a[pos];
        else if(pos-first > k-1)
            return kthSmallest(a, first, pos-1, k);
        else
            return kthSmallest(a, pos+1, last, k-pos+first-1);
    }
    return INT32_MAX;
}

void rebuildHeap(int a[], int root, int n){

    int current = root;
    
    while(2 * current + 1 < n){
        int leftChild = 2 * current + 1;
        int rightChild = leftChild + 1;
        int largerChild;

        if(rightChild < n){
            if(a[rightChild] > a[leftChild])
                largerChild = rightChild;
            else
                largerChild = leftChild;
        }
        else
            largerChild = leftChild;

        if(a[largerChild] > a[current]){
            int temp = a[largerChild];
            a[largerChild] = a[current];
            a[current] = temp;
        }
        else
            break;
        current = largerChild;
    }

}

void heapSort(int a[], int n){
    int heap_size = n;
    for(int last = n-1; last > 0; last--){
        int temp = a[0];// 최댓값
        a[0] = a[last];
        a[last] = temp;
        heap_size--;
        rebuildHeap(a, 0, heap_size);
    }
}

void insertHeap(int a[], int &n, int key){
    a[n] = key;
    n++;
    int i = n-1;
    int parent = (i-1)/2;

    while(i>0){
        if(a[parent] < a[i]){
            int temp = a[parent];
            a[parent] = a[i];
            a[i] = temp;
            i = parent;
            parent = (i-1)/2;
        }
        else
            break;            
    }
}

void deleteHeap(int a[], int &n){
    int temp = a[n-1];
    a[n-1] = a[0];
    a[0] = temp;
    n--;
    rebuildHeap(a, 0, n);
}

void radixSort(int a[], int n){
    queue<int>Q[10];
    int max = a[0], radix = 1;

    for(int i=0; i<n; i++){
        if(max < a[i])
            max = a[i];
    }

    while(1){//최댓값찾기
        if(radix >= max)
            break;
        radix *= 10;
    }

    for(int i=1; i<=radix; i*=10){
        //분할
        for(int j=0; j<n; j++){
            int k;
            if(a[j]<i)
                k=0;
            else
                k=(a[j]/i)%10;
            Q[k].push(a[j]);            
        }
        //모으기
        int idx = 0;
        for(int j=0; j<10; j++){
            while(Q[j].empty()==0){
                a[idx] = Q[j].front();
                Q[j].pop();
                idx++;
            }
        }
    }  
}

int c[10000];
int* countingSort(int a[], int n, int k){
    int* b = new int[n];
    for(int i=0; i<=k; i++)
        c[i] = 0;
    for(int i=0; i<n; i++)
        c[a[i]] += 1;
    for(int i=0; i<=k; i++)
        c[i] += c[i-1];
    for(int i = n-1; i>=0; i--){
        b[c[a[i]]-1] = a[i];
        c[a[i]] -= 1;
    } 
    return b;
}

int main(){
    
    int n;
    int arr[100];

    cin >> n;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n);

    cout<< kthSmallest(arr, 1, n, 1);
}
