#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Greedy
{
    int *a, *st, *ft;
    int siz;

    int Partition(int ac[], int star[], int fin[], int s, int e)
    {
        int piv = fin[e];
        int i = s, j, tem;

        for(j = s; j<e; j++) {
            if(fin[j] <= piv)
            {
                tem = fin[i];
                fin[i] = fin[j];
                fin[j] = tem;

                tem = star[i];
                star[i] = star[j];
                star[j] = tem;

                tem = ac[i];
                ac[i] = ac[j];
                ac[j] = tem;

                i++;
            }
        }

        tem = fin[i];
        fin[i] = fin[e];
        fin[e] = tem;

        tem = star[i];
        star[i] = star[e];
        star[e] = tem;

        tem = ac[i];
        ac[i] = ac[e];
        ac[e] = tem;

        return i;
    }

    void QuickSort(int ac[], int star[], int fin[], int s, int e)
    {
        int p;
        if(s < e)
        {
            p = Partition(ac, star, fin, s, e);
            QuickSort(ac, star, fin, s, p-1);
            QuickSort(ac, star, fin, p+1, e);
        }
    }

public:
    Greedy()
    {
        a = new int[10];
        st = new int[10];
        ft = new int[10];
        siz = 0;
    }

    void Generate(int n)
    {
        srand(time(0));
        a = new int[n];
        st = new int[n];
        ft = new int[n];
        siz = n;

        for(unsigned int i=0; i<n; i++) {
            a[i] = i+1;
            st[i] = 1 + rand()%24;
            ft[i] = st[i] + 1 + rand()%(24-st[i]+1);
        }
    }

    void Solution()
    {
        int *ac = new int[siz];
        int *star = new int[siz];
        int *fin = new int[siz];

        for(unsigned int i=0; i<siz; i++) {
            ac[i] = a[i];
            star[i] = st[i];
            fin[i] = ft[i];
        }

        QuickSort(ac, star, fin, 0, siz-1);

        int j = 0, i;

        cout<<ac[0]<<"["<<star[0]<<", "<<fin[0]<<")"<<"  ";

        for(i=1; i<siz; i++)
        {
            if(fin[j]<=star[i]) {
                 cout<<ac[i]<<"["<<star[i]<<", "<<fin[i]<<")"<<"  ";
                 j = i;
            }
        }
        cout<<endl<<endl;
     }

    void Acitivities()
    {
        for(int i=0; i<siz; i++) {
            cout<<a[i]<<"["<<st[i]<<", "<<ft[i]<<")"<<"  ";
        }
        cout<<endl<<endl;
    }
};


int main()
{
    Greedy g;
    int choice;
    while(1)
    {
        cout<<"1. Generate Activities."<<endl;
        cout<<"2. Print activities with start and end time."<<endl;
        cout<<"3. Print all possible solutions."<<endl;
        cout<<"4. Quit."<<endl;
        cout<<"choose any of the above options"<<endl;

        cin>>choice;

        if(choice == 1) {
            cout<<"Enter the number of activities: ";
            int actvt;
            cin>>actvt;
            g.Generate(actvt);
            cout<<endl;
        }
        else if(choice == 2) {
            g.Acitivities();
        }
        else if(choice == 3) {
            g.Solution();
        }
        else if(choice == 4) {
            break;
        }
    }
    return 0;
}
