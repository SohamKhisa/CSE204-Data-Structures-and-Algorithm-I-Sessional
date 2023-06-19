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
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
	int *col, *parent, *dist; //adjacency matrix to store the graph
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
	matrix = 0 ;
	directed = dir ;
	col = 0;
	dist = 0;
	parent = 0;//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges--;
    matrix[u][v] = 0;
    if(!directed)   matrix[v][u] = 0;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)  return  false;
    if(!directed) {
        int isthere1, isthere2;
        isthere1 = matrix[u][v];
        isthere2 = matrix[v][u];
        if(isthere1 == 0 && isthere2 == 0)   return false;
        else    return true;
    }
    else {
        int isthere;
        isthere = matrix[u][v];
        if(isthere == 0)   return false;
        else    return true;
    }
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u, bool out = true)
{
    if(u<0 || u >= nVertices)   return NULL_VALUE;
    int deg = 0;
    if(!directed) {
        for(int i = 0; i < nVertices; i++) {
            if(matrix[u][i] == 1)   deg++;
        }
        return deg;
    }
    else{
        if(out) {
            for(int i = 0; i < nVertices; i++) {
                if(matrix[u][i] == 1)   deg++;
            }
            return deg;
        }
        else {
            for(int i = 0; i < nVertices; i++) {
                if(matrix[i][u] != 0)
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
    for(int i = 0; i<nVertices; i++) {
        if(matrix[u][i] == 1)   printf("%d ", i);
    }
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

    for(int i=0; i<nVertices; i++){
        if(matrix[u][i] == 1 && matrix[v][i] == 1) {
            return true;
        }
    }
    return false;
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
        int v, i = 0;
        for(i = 0; i < nVertices; i++) {
            v=matrix[vertx][i];
            if(v==1) {
                if(col[i] == WHITE) {
                    col[i] = GREY;
                    dist[i] = dist[vertx] + 1;
                    parent[i] = vertx;
                    q.enqueue(i);
                }
            }
        }
        col[vertx] = BLACK;
    }
    //write this function
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
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(matrix) {
        for(int i = 0; i < nVertices; i++) {
        delete[] matrix[i];
        }
        delete[] matrix;
    }
    matrix = 0;
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
        printf("1. Add edge.\n2. Is edge.\n3. Get degree.\n");
        printf("4. Print adjacent vertices.\n5. Print Graph.\n");
        printf("6. Has common adjacent\n7. Get distance.\n");
        printf("8. Exit\n");

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
    }

}
