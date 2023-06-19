#include<iostream>

using namespace std;

template<class Q>
class Queue
{
    Q *que;
    int top, bot, s;
public:
    Queue() {
        que = new Q[10];
        top = 0;
        bot = 0;
        s = 10;
    }

    bool empty() {
        if(top==0)  return true;
        else    return false;
    }

    int size() {
        return s;
    }

    int& front() {
        return que[bot];
    }

    int& rear() {
        return que[top];
    }

    void enqueue(Q x) {
        que[bot] = x;
        int c=0;
        if(bot == s-1) {
            Q *temp = new Q[s];
            for(unsigned int i=0, j=top; j<=bot; i++, j++) {
                temp[i] = que[j];
                c++;
            }

            if(bot-top+1 == s) {        ///If the diff between bot and top is equal to size-1
                que = new Q[s + 10];
                s += 10;
            }
            for(unsigned int i=0; i<c; i++)
                que[i] = temp[i];

            bot = bot-top;
            top = 0;
        }
        bot++;
    }

    Q dequeue() {
        Q t = que[top];
        int c=0;
        if(top==bot) {
            cout<<"the queue is empty"<<endl;
            return 0;
        }
        else if(s>10 && bot-top < s-10-1) {
            Q *temp = new Q[s-10];
            for(unsigned int i=0, j=top+1; j<bot; i++, j++) {
                temp[i] = que[j];
                c++;
            }

            que = new Q[s - 10];
            s -= 10;
            for(unsigned int i=0; i<c; i++)
                que[i] = temp[i];

            bot = bot-top-1;
            top = 0;
        }
        else
            top++;
        return t;
    }

};

int main()
{
    Queue<int> q;

    for(int i=0; i<15; i++) {
        q.enqueue(i);
    }
    cout<<"size before dequeue: "<<q.size()<<endl;
    for(int i=0; i<15; i++) {
        cout<<q.dequeue()<<endl;
    }
    cout<<"size after dequeue: "<<q.size()<<endl;
    q.enqueue(50);
    q.enqueue(60);
    cout<<q.dequeue()<<endl;
    cout<<q.dequeue()<<endl;
    return 0;
}
