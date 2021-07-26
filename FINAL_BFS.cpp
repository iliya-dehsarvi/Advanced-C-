#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define initial 1
#define waiting 2
#define visited 3
// Converted the program into an object oriented program and
// changed the create graph to be the the constructor of the class.
class GRAPH {
    int n;
    // Changed C++ 2D array to 2D std::vector
    std::vector<std::vector<int>> adj;
    // Changed C++ array to std::vector
    std::vector<int> state;
    // Changed queue array to std::queue
    std::queue<int> Queue;
public:
    // Used advanced C++ techniques to initialize the STL objects
    GRAPH(int _n) : adj(_n, std::vector<int>(_n)), state(_n) {
        int max_edge, origin, destin;
        n=_n;
        max_edge=n*(n-1);
        for (int count=1; count<=max_edge; count++) {
            std::cout << "Enter edge " << count << "( -1 -1 to quit ) : ";
            std::cin >> origin >> destin;
            if ((origin == -1) && (destin == -1)) { break; }
            if (origin>=n || destin>=n || origin<0 || destin<0) {
                std::cout << "Invalid edge!\n";
                count--;
            } else { adj[origin][destin] = 1; }
        }
    }
    void BF_Traversal() {
        int v;
        // Replaced for loop with for_each
        for_each(state.begin(), state.begin()+n, [](int &v) { v = initial; });
        std::cout << "Enter Start Vertex for BFS: \n";
        std::cin >> v;
        BFS(v);
    }
    void BFS(int v) {
        // removed the insert_queue() function and used std::queue.push() instead
        Queue.push(v);
        state[v] = waiting;
        while (!Queue.empty()) {
            // removed the delete_queue() function and used std::queue.pop() and std::queue.front() instead
            v = Queue.front();
            Queue.pop();
            std::cout << v << " ";
            state[v] = visited;
            int i=0;
            // Change for loop to for_each
            for_each(state.begin(), state.end()+n, [&](int &s) {
                if (adj[v][i] == 1 && s == initial) {
                    // Replaced the insert_queue() function with std::queue.push() instead
                    Queue.push(i);
                    s=waiting;
                } i++;
            });
        } std::cout << "\n";
    }
};
int main() {
    int n;
    std::cout << "Enter number of vertices : ";
    std::cin >> n;
    GRAPH GRAPH_OBJ(n);
    GRAPH_OBJ.BF_Traversal();
    return 0;
}

/*
 SAMPLE OUTPUT:
 
 Enter number of vertices : 9
 Enter edge 1( -1 -1 to quit ) : 0 1
 Enter edge 2( -1 -1 to quit ) : 0 3
 Enter edge 3( -1 -1 to quit ) : 0 4
 Enter edge 4( -1 -1 to quit ) : 1 2
 Enter edge 5( -1 -1 to quit ) : 3 6
 Enter edge 6( -1 -1 to quit ) : 4 7
 Enter edge 7( -1 -1 to quit ) : 6 4
 Enter edge 8( -1 -1 to quit ) : 6 7
 Enter edge 9( -1 -1 to quit ) : 2 5
 Enter edge 10( -1 -1 to quit ) : 4 5
 Enter edge 11( -1 -1 to quit ) : 7 5
 Enter edge 12( -1 -1 to quit ) : 7 8
 Enter edge 13( -1 -1 to quit ) : -1 -1
 Enter Start Vertex for BFS:
 0
 0 1 3 4 2 6 5 7 8
 */
