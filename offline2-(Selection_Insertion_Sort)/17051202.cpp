#include<iostream>
#include<cstdlib>
#include<ctime>
#include<unordered_set>
#include<cmath>

using namespace std;

bool isUnique(char ar[], int n)
{
        unordered_set<char> s;
        for(int i = 0; i <= n; i++)  s.insert(ar[i]);

        return (s.size() == n+1);
}

void PowerSet(char ar[], int setsize)
{
    for(int i=0; i<pow(2, setsize); i++) {
        for(int j=0; j<setsize; j++) {
            if(i&(1<<j))    cout<<ar[j];
        }
        cout<<endl;
    }
}

int main()
{
    int n, i=0;
    char c;
    cin>>n;
    clock_t tgen, talgo;
    char Set[n+1];
    srand(time(NULL));

    tgen = clock();
    while(i<n) {
        int rnd = rand()%120;
        if(rnd <= 40)
           c = '0' + rand()%10;
        if(rnd > 40 && rnd <= 80)
            c = 'a' + rand()%26;
        if(rnd > 80 && rnd <= 120)
            c = 'A' + rand()%26;
        Set[i] = c;

        if(i==0)    i++;
        else if(isUnique(Set, i))  i++;
    }
    tgen = clock() - tgen;

    cout<<"{";
    for(i=0; i<n; i++) {
        if(i==n-1)  cout<<Set[i];
        else
        cout<<Set[i]<<", ";
    }
    cout<<"}"<<endl;
    cout<<"The time needed for generating the set is: "<<(float)tgen/CLOCKS_PER_SEC * pow(10, 3)<<" millisecond"<<endl;

    cout<<endl<<"The powerset of the above set is: ";
    talgo = clock();
    PowerSet(Set, n);
    talgo = clock() - talgo;
    cout<<endl<<"The time needed for the powerset algorithm: "<<(float)talgo/CLOCKS_PER_SEC <<" second"<<endl;
    return 0;
}
