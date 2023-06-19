#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

void GenBest(int ar[], int n)
{

    ar[0] = rand() % 10;
    for(unsigned int i=1; i<n; i++)
    {
        ar[i] = ar[i-1] + rand() % 1000;
    }
}

void GenAvg(int ar[], int n)
{
    for(unsigned int i=0; i<n; i++)
    {
        ar[i] = rand()*10000+rand();
    }
}

void GenWrst(int ar[], int n)
{
    ar[0] = rand();
    for(unsigned int i=1; i<n; i++)
    {
        ar[i] = ar[i-1] - rand()%500;
    }
}

//Merge sort
void Merge(int ar[], int in, int mid, int fin)
{
    int nL = mid-in+1;
    int nR = fin-mid;
    int p = 0, q = 0;

    int *Left, *Right;
    Left = new int[nL];
    Right = new int[nR];

    for (unsigned int i = 0; i < nL; i++)
        Left[i] = ar[in + i];
    for (unsigned int j = 0; j < nR; j++)
        Right[j] = ar[mid + 1+ j];

    int r = in;
    while(p < nL && q < nR)
    {
        if(Left[p] <= Right[q])
        {
            ar[r] = Left[p];
            p++;
        }
        else
        {
            ar[r] = Right[q];
            q++;
        }
        r++;
    }

    while (p < nL)
    {
        ar[r] = Left[p];
        r++;
        p++;
    }

    while (q < nR)
    {
        ar[r] = Right[q];
        r++;
        q++;
    }
}

void MergeSort(int ar[], int ini, int fin)
{
    if(ini < fin)
    {
        int mid = ini + (fin-ini)/2;
        MergeSort(ar, ini, mid);
        MergeSort(ar, mid+1, fin);

        Merge(ar, ini, mid, fin);
    }
}

//Quick Sort
int Partition(int ar[], int s, int e)
{
    int piv = ar[e];
    int i = s, j, tem;

    for(j = s; j<e; j++) {
        if(ar[j] <= piv)
        {
            tem = ar[i];
            ar[i] = ar[j];
            ar[j] = tem;

            i++;
        }
    }

    tem = ar[i];
    ar[i] = ar[e];
    ar[e] = tem;

    return i;
}

void QuickSort(int ar[], int s, int e)
{
    int p;
    if(s < e)
    {
        p = Partition(ar, s, e);
        QuickSort(ar, s, p-1);
        QuickSort(ar, p+1, e);
    }
}

void Print(int ar[], int n)
{
    for(int i=0; i<n; i++) {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int choice, n;
    int *arQ, *arM, flg = 0;
    clock_t t1, t2;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            {
            printf("Number of elements: ");
            scanf("%d", &n);
            arM = new int[n];
            arQ = new int[n];
            GenAvg(arM, n);
            for(int i=0; i<n; i++) {
                arQ[i] = arM[i];
            }
            break;
            }

        case 2:
            {
            printf("Number of elements: ");
            scanf("%d", &n);
            arM = new int[n];
            arQ = new int[n];
            GenBest(arM, n);
            for(int i=0; i<n; i++)
                arQ[i] = arM[i];
            break;
            }

        case 3:
            {
            printf("Number of elements: ");
            scanf("%d", &n);
            arM = new int[n];
            arQ = new int[n];
            GenWrst(arM, n);
            for(int i=0; i<n; i++)
                arQ[i] = arM[i];
            break;
            }

        case 4:
            {
            flg = -1;
            printf("Applying merge sort\n");
            t1 = clock();
            MergeSort(arM, 0, n-1);
            t1 = clock() - t1;
            // do yourself
            // this should transform the given array into a sorted array
            double tm=((double)t1)/CLOCKS_PER_SEC * pow(10, 3);
            printf("Time taken to finish: %lf millisecond\n", tm);
            break;
            }

        case 5:
            {
            flg = 1;
            printf("Applying quicksort\n");
            t2 = clock();
            QuickSort(arQ, 0, n-1);
            t2 = clock() - t2;
            // do yourself
            // this should transform the given array into a sorted array
            double tm =((double)t2)/CLOCKS_PER_SEC * pow(10, 3);
            printf("Time taken to finish: %lf millisecond\n", tm);
            break;
            }

        case 6:
            {
            printf("Array\n");
            if(flg == -1)
                Print(arM, n);
            else if(flg == 1)
                Print(arQ, n);
            else
                Print(arM, n);
            flg = 0;
            break;
            }
        }
    }
    return 0;
}

