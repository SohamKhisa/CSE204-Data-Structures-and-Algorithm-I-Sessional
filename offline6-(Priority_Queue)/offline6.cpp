#include<iostream>

using namespace std;

class MaxPriorityQ
{
    int *node;
    int Hpsize;
    int Hpindex;
public:
    MaxPriorityQ()
    {
        node = new int[10];
        Hpsize = 10;
        Hpindex = 0;
    }

    ~MaxPriorityQ()
    {
        delete[] node;
        node = nullptr;
    }

    void Insert(int x);
    int FindMax();
    int ExtractMax();
    void IncreaseKey(int i, int newKey);
    void DecreaseKey(int i, int newKey);
    void Print();
};

void MaxPriorityQ::Insert(int x)
{
    if(Hpindex%Hpsize==0) {
        int *temp = new int[Hpsize];
        for(int i=0; i<Hpsize; i++) {
            temp[i] = node[i];
        }
        node = new int[Hpsize+10];
        for(int i=0; i<Hpsize; i++) {
            node[i] = temp[i];
        }
        delete []temp;
        temp = nullptr;
        Hpsize += 10;
    }

    node[Hpindex] = x;
    Hpindex += 1;
    IncreaseKey(Hpindex-1, x);
}

int MaxPriorityQ::FindMax()
{
    return node[0];
}

int MaxPriorityQ::ExtractMax()
{
    if(Hpindex == 0)
        return -999999;

    int Max = node[0];
    node[0] = node[Hpindex-1];
    Hpindex--;

    int i = 0;
    while(i<Hpindex/2) {
        int Left = 2*i + 1;
        int Right = 2*i + 2;
        int L = i;
        if(node[Left] > node[i])
            L = Left;
        if(node[Right] > node[L])
            L = Right;
        if(L != i) {
            int temp = node[L];
            node[L] = node[i];
            node[i] = temp;

            i = L;
        }
        else
            break;
    }

    if(Hpindex == Hpsize-11)
    {
        cout<<"working"<<endl;

        int *temp = new int[Hpsize-11];
        for(int i=0; i<Hpsize-11; i++) {
            temp[i] = node[i];
        }
        node = new int[Hpsize-10];
        for(int i=0; i<Hpsize-11; i++) {
            node[i] = temp[i];
        }
        delete []temp;
        temp = nullptr;
        Hpsize -= 10;
    }

    return Max;
}

void MaxPriorityQ::IncreaseKey(int i, int newkey)
{
    if(i >= Hpindex)    cout<<"the index is out of bound"<<endl;
    else if(node[i] > newkey)    cout<<"the new value is less than the current value"<<endl;
    else {
        node[i] = newkey;
        int x = i;
        while(x > 0)
        {
            int P = (x+1)/2 - 1;
            if(node[x] > node[P]) {
                int t = node[x];
                node[x] = node[P];
                node[P] = t;
                x = P;
            }
            else {
                break;
            }
        }
    }
}

void MaxPriorityQ::DecreaseKey(int i, int newkey)
{
    if(i >= Hpindex)    cout<<"Index is out of bound"<<endl;
    else if(node[i] < newkey)    cout<<"the new value is larger than the current value"<<endl;
    else {
        node[i] = newkey;
        while(i > 0)
        {
            int P = (i+1)/2 - 1;
            if(node[i] > node[P]) {
                int t = node[i];
                node[i] = node[P];
                node[P] = t;
                i = P;
            }
            else
                break;
        }
    }
}

void MaxPriorityQ::Print()
{
    for(int i=0; i<Hpindex; i++) {
        cout<<node[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    MaxPriorityQ mq;

    while(1)
    {

        cout<<"1. Insert"<<endl;
        cout<<"2. FindMax"<<endl;
        cout<<"3. ExtractMax"<<endl;
        cout<<"4. IncreaseKey"<<endl;
        cout<<"5. DecreaseKey"<<endl;
        cout<<"6. Print"<<endl;
        cout<<"7. Quit"<<endl;

        int com;
        cin>>com;

        if(com == 1) {
            cout<<"Enter a value to insert: ";
            int val;
            cin>>val;
            mq.Insert(val);
        }
        if(com == 2) {
            int Max = mq.FindMax();
            cout<<Max<<endl;
        }
        if(com == 3) {
            int Max = mq.ExtractMax();
            if(Max == -999999)
                cout<<"No element in the heap"<<endl;
            else
                cout<<Max<<endl;
        }
        if(com == 4) {
            cout<<"Enter the index of the heap: ";
            int ind;
            cin>>ind;
            cout<<"\nEnter the new value: ";
            int val;
            cin>>val;
            cout<<endl;
            mq.IncreaseKey(ind-1, val);
        }
        if(com == 5) {
            cout<<"Enter the index of the heap: ";
            int ind;
            cin>>ind;
            cout<<"\nEnter the new value: ";
            int val;
            cin>>val;
            cout<<endl;
            mq.DecreaseKey(ind-1, val);
        }
        if(com == 6) {
            mq.Print();
        }
        if(com == 7) {
            break;
        }
    }

    return 0;
}
