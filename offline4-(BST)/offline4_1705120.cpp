#include<iostream>

using namespace std;

class BST;
class Node
{
    int key;
    Node *L;
    Node *R;
    friend class BST;
public:
    Node(int x) {
        key = x;
        L = NULL;
        R = NULL;
    }
};

class BST
{
    Node *np;
    void Insert(int num, Node *&nod);
    bool Search(int num, Node *nod);
    Node* Delete(int num, Node *&nod);
    void PreOrder(Node *nod);
    void InOrder(Node *nod);

public:
    BST() {
        np = NULL;
    }

    bool Search(int n) {
        if(Search(n, np) == true)   return true;
        else    return false;
    }

    void Insert(int num) {
        Insert(num, np);
    }

    void Delete(int num) {
        np = Delete(num, np);
    }

    void PreOrder() {
        PreOrder(np);
    }

    void InOrder() {
        InOrder(np);
    }

    Node* MinNode(Node *nod) {
        Node *n = nod;
        while(n && n->L != NULL)
            n = n->L;
        return n;
    }
};

void BST::Insert(int num, Node *&nod)
{
    if(nod == NULL){
        nod = new Node(num);
    }

    else if(num < nod->key) {
        if(nod->L == NULL)
            nod->L = new Node(num);
        else
            Insert(num, nod->L);
    }

    else if(num > nod->key) {
        if(nod->R == NULL)
            nod->R = new Node(num);
        else
            Insert(num, nod->R);
    }
}

bool BST::Search(int num, Node *nod)
{
    if(nod == NULL)    return false;
    else if(nod->key == num)   return true;
    else if(nod->key > num)    return Search(num, nod->L);
    else    return Search(num, nod->R);
}

Node* BST::Delete(int num, Node *&nod)
{
    if(nod == NULL) return nod;

    if(num < nod->key)
        nod->L = Delete(num, nod->L);
    else if(num > nod->key)
        nod->R = Delete(num, nod->R);
    else
    {
        if(nod->L == NULL) {
            Node *t = nod->R;
            free(nod);
            nod = NULL;
            return t;
        }
        else if(nod->R == NULL) {
            Node *t = nod->L;
            free(nod);
            nod = NULL;
            return t;
        }

        Node *tp = MinNode(nod->R);
        nod->key = tp->key;
        nod->R = Delete(tp->key, nod->R);
    }
    return nod;
}

void BST::InOrder(Node *nod)
{
    if(nod == NULL) return;
    InOrder(nod->L);
    cout<<nod->key<<endl;
    InOrder(nod->R);
}

void BST::PreOrder(Node *nod)
{
    if(nod == NULL) return;
    cout<<nod->key<<endl;
    PreOrder(nod->L);
    PreOrder(nod->R);
}

int main()
{
    int n , m;
    BST b;

    while(1)
    {
        cout<<"Enter 1 for searching a number"<<endl;
        cout<<"Enter 2 for inserting a number"<<endl;
        cout<<"Enter 3 for delete a number"<<endl;
        cout<<"Enter 4 for inorder traversal"<<endl;
        cout<<"Enter 5 for preorder traversal"<<endl;
        cout<<"Enter 6 for exit"<<endl;

        cin>>n;

        if(n==1) {
            cout<<"Enter a number to search"<<endl;
            cin>>m;
            bool verdict = b.Search(m);
            if(verdict==true)   cout<<"The integer is present in the BST\n"<<endl;
            else    cout<<"The integer is not present in the BST\n"<<endl;
        }

        else if(n==2) {
            cout<<"Enter a number to insert"<<endl;
            cin>>m;
            b.Insert(m);
            cout<<endl;
        }

        else if(n==3) {
            cout<<"Enter a number to delete"<<endl;
            cin>>m;
            b.Delete(m);
            cout<<endl;
        }

        else if(n==4) {
            cout<<"Inorder traversal:"<<endl;
            b.InOrder();
            cout<<endl;
        }

        else if(n==5) {
            cout<<"Preorder traversal:"<<endl;
            b.PreOrder();
            cout<<endl;
        }

        else if(n == 6)  break;
    }

    return 0;
}
