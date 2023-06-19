#include<iostream>
#define garbage -999999

using namespace std;

class disSet
{
    int *p;
    int *r;
    int *siz;
public:
    disSet()
    {
        p = new int[10000000];
        r = new int[10000000];
        siz = new int[10000000];
        for(unsigned int i=0; i<=10000000; i++) {
            p[i] = garbage;
            r[i] = garbage;
            siz[i] = garbage;
        }
    }
    void makeSet(int x);
    int findSet(int x);
    void Union(int u, int v);
    void Print(int u);
};

void disSet::makeSet(int x)
{
    p[x] = x;
    r[x] = 0;
    siz[x] = 1;
    cout<<endl;
}

int disSet::findSet(int x)
{
    if(p[x]==garbage) return garbage;
    if(x != p[x])
        p[x] = findSet(p[x]);
    return p[x];
}

void disSet::Union(int u, int v)
{
    int x = findSet(u);
    int y = findSet(v);

    if(x == y)
    {
        cout<<"Both "<<u<<" and "<<v<<" belong to the same set."<<endl<<endl;
        return;
    }
    else if(x == garbage || y == garbage)
    {
        if(x == garbage)
            cout<<"Error: "<<u<<" is not a set element."<<endl<<endl;
        else if(y == garbage)
            cout<<"Error: "<<v<<" is not a set element."<<endl<<endl;
        return;
    }
    else if(r[x] > r[y])
    {
        p[y] = x;
        siz[x] = siz[y] + siz[x];
    }
    else if(r[x] < r[y])
    {
        p[x] = y;
        siz[y] = siz[x] + siz[y];
    }
    else
    {
        p[y] = x;
        r[x] = r[x] + 1;
        siz[x] = siz[y] + siz[x];
    }
    cout<<endl;
}

void disSet::Print(int u)
{
    int x = findSet(u);
    int Size = siz[x];
    if(x == garbage)
        cout<<u<<" does not belong to any set."<<endl<<endl;
    else
    {
        cout<<"{";
        for(unsigned int i=0; i<=1000000; i++)
        {
            int root = findSet(i);
            if(root == x)
            {
                if(Size != 1) {
                    cout<<i<<", ";
                    Size--;
                }
                else {
                    cout<<i;
                    Size--;
                }
            }
        }
        cout<<"}"<<endl<<endl;
    }
}

int main()
{
    int choice, x, y, flg = 0;
    disSet s;

    while(1)
    {
        cout<<"1. Make-Set"<<endl;
        cout<<"2. Find-Set"<<endl;
        cout<<"3. Union"<<endl;
        cout<<"4. Print"<<endl;
        cout<<"5. Quit"<<endl;
        cout<<"Choose any of the given options"<<endl;

        cin>>choice;

        switch(choice)
        {
        case 1:
            {
                cout<<"Enter a number: ";
                cin>>x;
                s.makeSet(x);
                break;
            }

        case 2:
            {
                cout<<"Enter a number: ";
                cin>>x;
                int pr = s.findSet(x);
                cout<<"the root of "<<x<<" is: "<<pr<<endl;
                break;
            }

        case 3:
            {
                cout<<"Enter two numbers"<<endl;
                cout<<"1st number: ";
                cin>>x;
                cout<<"2nd number: ";
                cin>>y;
                s.Union(x, y);
                break;
            }

        case 4:
            {
                cout<<"Enter a number: ";
                cin>>x;
                s.Print(x);
                break;
            }

        case 5:
            {
                flg = 1;
                break;
            }
        }
        if(flg == 1)
            break;
    }
    return 0;
}
