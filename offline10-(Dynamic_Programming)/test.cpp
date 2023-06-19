#include<iostream>
#include<cstring>

using namespace std;

int main()
{
    char *s;
    char *c;

    int n, m;
    cin>>n;
    cin>>m;

    s = new char[n];
    c = new char[m];


    cout<<"hello world: ";
    cin.getline(s, n);
    cout<<"mara"<<endl;
    cin.getline(c, m);

    cout<<s<<endl;
    cout<<c<<endl;
    return 0;
}
