 #include<iostream>
#include<stdlib.h>
using namespace std;

// Structure for node in adjacency list
struct node {
    int vertex;
    node* next;
    node(int x, node* t) { vertex = x; next = t; }
};
typedef node* lnk;

// Function to create a new node
node* createNode(int vertex) {
    return new node(vertex, NULL);
}

// Function to add a new edge to the adjacency list
void addEdge(lnk adj[], int src, int dest) {
    node* newNode = createNode(dest);
    newNode->next = adj[src];
    adj[src] = newNode;
}

// Function to input graph as adjacency list
void inputGraph(lnk adj[], int n) {
    int tmp;
    cout << "Enter adjacency list for each vertex: \n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        do {
            cin >> tmp;
            if (tmp != 0) {
                addEdge(adj, i, tmp - 1);
            }
        } while (tmp != 0);
    }
}

// Depth first search traversal
void dfs(lnk adj[], int start, int visited[]) {
    if (visited[start]) return;
    visited[start] = 1;
    cout << start + 1 << ' ';

    node* temp = adj[start];
    while (temp != NULL) {
        int childVertex = temp->vertex;
        dfs(adj, childVertex, visited);
        temp = temp->next;
    }
}

int main() {
    int n, start;
    cout << "Enter number of vertices: ";
    cin >> n;

    lnk adj[n];
    int visited[n] = {0};

    // Initialize adjacency list
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
    }

    // Input graph as adjacency list
    inputGraph(adj, n);

    cout << "Enter starting vertex: ";
    cin >> start;

    // Perform DFS traversal
    cout << "DFS traversal: ";
    dfs(adj, start - 1, visited);
    cout << endl;

    return 0;
}
