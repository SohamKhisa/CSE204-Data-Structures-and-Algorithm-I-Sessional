#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int LinearSearch(int ar[], int n, int x)
{
    for(int i=0; i<n; i++)
        if(ar[i]==x)
            return i;
    return -1;
}

int BinarySearch(int ar[], int n, int x)
{
    int first=0, last=n-1, mid, idx=-1;
    mid=(first+last)/2;
    while(last>=first)
    {
        if(ar[mid]==x)
        {
            idx=mid;
            break;
        }
        else if(ar[mid]>x)
            last=mid-1;

        else    first=mid+1;

        mid=(first+last)/2;
    }
    return idx;
}

//QuickSort
void Swap(int &a, int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

int Partition(int ar[], int low, int high)
{
    int piv=ar[high];
    int i=low-1;
    for(unsigned int j=low; j<high; j++) {
        if(ar[j]<=piv) {
            i++;
            Swap(ar[i], ar[j]);
        }
    }
    Swap(ar[i+1], ar[high]);
    return i+1;
}

void quickSort(int ar[], int low, int high)
{
    if(low<high)
    {
        int piv=Partition(ar, low, high);
        quickSort(ar, low, piv-1);
        quickSort(ar, piv+1, high);
    }
}

int main()
{
    clock_t t;
    int n, x;
    cin>>n;
    int arr[n];
    for(unsigned int i=0; i<n; i++)
    {
        arr[i]=rand();
    }
    x=rand();
    quickSort(arr, 0, n-1);

    for(unsigned int i=0; i<n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    t=clock();
    int indx=BinarySearch(arr, n, x);
    cout<<indx<<endl;
    t=clock()-t;
    double time_binary=((double)t)/CLOCKS_PER_SEC;

    t=clock();
    indx=LinearSearch(arr, n, x);
    cout<<indx<<endl;
    t=clock()-t;
    double time_linear=((double)t)/CLOCKS_PER_SEC;

    cout<<"for linear search the time consumed is: "<<time_linear<<endl;
    cout<<"for binary search the time consumed is: "<<time_binary<<endl;
    return 0;
}
