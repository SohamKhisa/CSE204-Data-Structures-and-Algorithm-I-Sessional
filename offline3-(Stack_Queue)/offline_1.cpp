#include<iostream>

using namespace std;


template<class X>
class stack
{
    X *stck;
    int t;
    int s;
public:
    stack() {
        stck = new X[10];
        t = 0;
        s = 10;
    }

    bool empty() {
        if(t==0)  return true;
        else    false;
    }

    int size() {
        return s;
    }

    int& top()
    {
        t++;
        return stck[t-1];
    }

    void push(X n) {

        stck[t] = n;

        if(t==s-1) {
            X *temp = new X[s];
            for(unsigned int i=0; i<s; i++)
                temp[i] = stck[i];

            stck = new X[s + 10];
            s += 10;
            for(unsigned int i=0; i<s; i++)
                stck[i] = temp[i];
        }

        t++;
    }

    X pop() {

        if(t==0) {
            cout<<"the stack is empty"<<endl;
            return 0;
        }
        else {
        t--;
        X x = stck[t];
        if(t==s-10-1 && t!=0) {
            X *temp = new X[s-10];
            for(unsigned int i=0; i<=t; i++)
                temp[i] = stck[i];

            stck = new X[s - 10];
            s -= 10;
            for(unsigned int i=0; i<=t; i++)
                stck[i] = temp[i];
            }
            return x;
        }
    }

};

int main()
{
    stack<int> st;
    int n;
    cin>>n;
    for(int i=0; i<n; i++) {
        st.push(i);
    }
    cout<<"size: "<<st.size()<<endl;
    cout<<"poping: "<<endl;
    for(int i=0; i<5; i++) {
        cout<<st.pop()<<endl;
    }
    cout<<"size after poping out: "<<st.size()<<endl;
    st.push(10);
    cout<<"size after pushing 10: "<<st.size()<<endl;

    return 0;
}
