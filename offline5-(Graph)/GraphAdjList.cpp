#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *col, *parent, *dist;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u, bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
	col = 0;
	parent = 0;
	dist = 0;//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges--;
    adjList[u].removeItem(v);
    if(!directed)   adjList[v].removeItem(u);
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)  return  false;
    if(!directed) {
        int isthere1, isthere2;
        isthere1 = adjList[u].searchItem(v);
        isthere2 = adjList[v].searchItem(u);
        if(isthere1 == NULL_VALUE && isthere2 == NULL_VALUE)   return false;
        else    return true;
    }
    else {
        int isthere;
        isthere = adjList[u].searchItem(v);
        if(isthere == NULL_VALUE)   return false;
        else    return true;
    }
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u, bool out=true)
{
    if(u<0 || u >= nVertices)   return NULL_VALUE;

    if(!directed)    return adjList[u].getLength();
    else{
        if(out)
            return adjList[u].getLength();
        else {
            int deg = 0;
            for(int i = 0; i < nVertices; i++) {
                if(adjList[i].searchItem(u) != NULL_VALUE)
                    deg++;
            }
            return deg;
        }
    }
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    if(u<0 || u >= nVertices)   return;
    adjList[u].printList();
    //directed and undirected will have their distinguished version
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

    int lenU = adjList[u].getLength();
    int lenV = adjList[v].getLength();

    for(int i=0; i<lenU; i++){
        for(int j=0; j<lenV; j++) {
            if(adjList[u].getItem(i) == adjList[v].getItem(j)) {
                return true;
            }
        }
    }
    return false;
    //directed and undirected don't matter
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    if(source<0 || source >= nVertices)
        return;
    Queue q;
    col = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    int vertx;
    for(int i=0; i<nVertices; i++) {
        if(i != source){
            col[i] = WHITE;
            parent[i] = NULL_VALUE;
            dist[i] = INFINITY;
        }
    }
    col[source] = GREY;
    parent[source] = NULL_VALUE;
    dist[source] = 0;

    if(!q.empty())  Queue q;
    q.enqueue(source);

    while(!q.empty()) {
        vertx = q.dequeue();
        int len = adjList[vertx].getLength();
        int v, i = 0;
        for(i = 0; i < len; i++) {
            v = adjList[vertx].getItem(i);
            if(col[v] == WHITE) {
                col[v] = GREY;
                dist[v] = dist[vertx] + 1;
                parent[v] = vertx;
                q.enqueue(v);
            }
        }
        col[vertx] = BLACK;
        printf("%d ", vertx);
    }
    printf("\n");
    //complete this function
    //initialize BFS variables for all n vertices first

}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)    return INFINITY ;
    this->bfs(u);
    int distance = dist[v] - dist[u];
    return distance;
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList) delete[] adjList;
    adjList = 0;
    if(col) delete[] col;
    col = 0;
    if(parent)  delete[] parent;
    parent = 0;
    if(dist)    delete[] dist;
    dist = 0;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);


    while(1)
    {
        printf("\n1. Add edge.\n2. Is edge.\n3. Get degree.\n");
        printf("4. Print adjacent vertices.\n5. Print Graph.\n");
        printf("6. Has common adjacent\n7. Get distance.\n");
        printf("8. Exit.\n9. BFS\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            printf("Enter the value of two vertices: ");
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            printf("Enter the value of two vertices: ");
            scanf("%d%d", &u, &v);
            bool res = g.isEdge(u, v);
            if(res == true) {
                printf("true\n");
            }
            else
                printf("false\n");
        }
        else if(ch==3)
        {
            int send, res, u;
            printf("Enter the value of the vertex: \n");
            scanf("%d", &u);
            printf("1. Outdegree.\n2. Indegree.\n");
            scanf("%d", &send);
            if(send == 1) {
                res = g.getDegree(u, true);
                printf("Outdegree: %d\n", res);
            }
            else {
                res = g.getDegree(u, false);
                printf("Indegree: %d\n", res);
            }
        }
        else if(ch==4)
        {
            int u;
            printf("Enter the value of the vertex: \n");
            scanf("%d", &u);
            g.printAdjVertices(u);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            printf("Enter the value of two vertices: \n");
            scanf("%d%d", &u, &v);
            bool res = g.hasCommonAdjacent(u, v);
            if(res) printf("true\n");
            else    printf("flase\n");
        }
        else if(ch==7)
        {
            int u, v;
            printf("Enter the value of two vertices: \n");
            scanf("%d%d", &u, &v);
            int dis = g.getDist(u, v);
            printf("distance: %d", dis);
        }
        else if(ch==8)
        {
            break;
        }
        else if(ch==9)
        {
            g.bfs(3);
        }
    }

}
