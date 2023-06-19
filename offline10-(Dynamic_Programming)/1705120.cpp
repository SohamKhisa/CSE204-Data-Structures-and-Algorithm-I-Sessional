#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;


void LCS(char s1[], char s2[], int p, int q)
{
    int Memo[p+1][q+1];

    for(int i=0; i<p+1; i++) {
        for(int j=0; j<q+1; j++) {
            if(i==0 || j==0)
                Memo[i][j] = 0;
            else if(s1[i-1]==s2[j-1])
                Memo[i][j] = 1 + Memo[i-1][j-1];
            else
                Memo[i][j] = max(Memo[i][j-1], Memo[i-1][j]);
        }
    }

    int siz = Memo[p][q];
    if(siz == 0) {
        cout<<"No Longest Common Subsequence"<<endl;
        return;
    }

    int i = p;
    int j = q;

    char lcs[siz+3];
    lcs[siz] = '\0';
    while(i>0 && j>0)
    {
        if(s1[i-1]==s2[j-1]) {
            siz--;
            i--;
            j--;
            lcs[siz] = s1[i];
        }
        else if(Memo[i-1][j] < Memo[i][j-1])
            j--;
        else
            i--;
    }

    cout<<lcs<<endl<<endl;
}

int main()
{
    int c, n, m, t1=-5, t2=-5;
    char *st1, *st2;

    while(1) {
        cout<<"1. string input"<<endl;
        cout<<"2. print LCS"<<endl;
        cout<<"3. quit"<<endl;


        cin>>c;
        if(c==1)
        {
            cout<<"Enter the size of first string: ";
            cin>>n;
            cout<<"Enter the size of second string: ";
            cin>>m;

            st1 = new char[n];
            char *s = new char[n];
            st2 = new char[m];

            cout<<"Enter string 1: ";
            cin.getline(s, n);
            cin.getline(st1, n);
            cout<<"Enter string 2: ";
            cin.getline(st2, m);

            t1 = strlen(st1);
            t2 = strlen(st2);
            cout<<endl;
        }
        if(c==2)
        {
            int x = strlen(st1);
            int y = strlen(st2);

            if(x==t1 && y==t2)
            {
                LCS(st1, st2, x, y);
            }
            else
                cout<<"Strings do not exist"<<endl;
        }
        if(c==3)
            break;
    }
    return 0;
}
