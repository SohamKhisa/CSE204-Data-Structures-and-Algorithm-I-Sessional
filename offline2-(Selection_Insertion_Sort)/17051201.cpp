#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<windows.h>

using namespace std;

void SelectSort(int ar[], int n)
{
    int mini, j, temp;
    for(unsigned int i=0; i<n-1; i++) {
            mini = i;
        for(j=i+1; j<n; j++)
            if(ar[j]<ar[mini]) mini = j;
        temp = ar[mini];
        ar[mini] = ar[i];
        ar[i] = temp;
    }
}

void insertSort(int ar[], int n)
{
    int temp, j;
    for(int i=0; i<n-1; i++) {
        j = i;
        while(ar[i]>ar[i+1])
        {
            temp = ar[i+1];
            ar[i+1] = ar[i];
            ar[i] = temp;
            i--;
            if(i<0) break;
        }
        i = j;
    }
}

int main()
{
    int n;
    cin>>n;
    srand(time(NULL));
    int avc1[n], avc2[n], bc1[n], bc2[n], wc1[n], wc2[n];
    LARGE_INTEGER st, fin, frq;

    bc1[0] = rand() % 10;
    bc2[0] = bc1[0];
    for(unsigned int i=1; i<n; i++) {
        bc1[i] = bc1[i-1] + rand() % 10;
        bc2[i] = bc1[i];
    }

    for(unsigned int i=0; i<n; i++) {
        avc1[i] = rand() % 10;
        avc2[i] = avc1[i];
    }

    wc1[0] = rand();
    wc2[0] = wc1[0];
    for(unsigned int i=1; i<n; i++) {
        wc1[i] = wc1[i-1] - rand()%10;
        wc2[i] = wc1[i];
    }

    cout<<"best case"<<endl;
    for(unsigned int i=0; i<n; i++)
    {
        cout<<bc1[i]<<" ";
    }

    cout<<endl<<endl<<"average case"<<endl;
    for(unsigned int i=0; i<n; i++)
    {
       cout<<avc1[i]<<" ";
    }

    cout<<endl<<endl<<"worst case"<<endl;
    for(unsigned int i=0; i<n; i++)
    {
       cout<<wc1[i]<<" ";
    }
    cout<<endl<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    SelectSort(bc1, n);
    QueryPerformanceCounter(&fin);
    cout<<"time required for best case by selection sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    insertSort(bc2, n);
    QueryPerformanceCounter(&fin);
    cout<<"time required for best case by insertion sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    SelectSort(avc1, n);
    QueryPerformanceCounter(&fin);
    cout<<endl<<"time required for average case by selection sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    insertSort(avc2, n);
    QueryPerformanceCounter(&fin);
    cout<<"time required for average case by insertion sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    SelectSort(wc1, n);
    QueryPerformanceCounter(&fin);
    cout<<endl<<"time required for worst case by selection sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    QueryPerformanceFrequency(&frq);
    QueryPerformanceCounter(&st);
    insertSort(wc2, n);
    QueryPerformanceCounter(&fin);
    cout<<"time required for worst case by insertion sort "<<((fin.QuadPart - st.QuadPart)/(double)frq.QuadPart) * pow(10, 6)<<" microsecond"<<endl;

    return 0;
}
