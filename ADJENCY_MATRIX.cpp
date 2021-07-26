//Part1
class Graph {
    std::vector<std::vector<bool>> *_adjMatrix;
    int _numVertices;
public:
    // Initialize the matrix to zero
    Graph(int numVertices) {
        _numVertices = numVertices;
        _adjMatrix = new std::vector<std::vector<bool>>(_numVertices, std::vector<bool>(_numVertices, false));
    }
    // Add edges
    void addEdge(int i, int j) {
        (*_adjMatrix)[i][j] = true;
        (*_adjMatrix)[j][i] = true;
    }
    // Remove edges
    void removeEdge(int i, int j) {
        (*_adjMatrix)[i][j] = false;
        (*_adjMatrix)[j][i] = false;
    }
    // Print the martix
    void toString() {
        for (int i = 0; i < _numVertices; i++) {
            std::cout << i << " : ";
            for (int j = 0; j < _numVertices; j++) { std::cout << (*_adjMatrix)[i][j] << " "; }
            std::cout << "\n";
        }
    }
    ~Graph() {
        for (auto index: *_adjMatrix) { index.clear(); }
        delete _adjMatrix;
    }
};
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
//Part2
class Graph {
    std::vector<std::vector<bool>> _adjMatrix;
    int _numVertices;
public:
    // Initialize the matrix to zero
    Graph(int numVertices) {
        _numVertices = numVertices;
        std::vector<std::vector<bool>> adjMatrix(_numVertices, std::vector<bool>(_numVertices, false));
        _adjMatrix=adjMatrix;
    }
    // Add edges
    void addEdge(int i, int j) {
        _adjMatrix[i][j] = true;
        _adjMatrix[j][i] = true;
    }
    // Remove edges
    void removeEdge(int i, int j) {
        _adjMatrix[i][j] = false;
        _adjMatrix[j][i] = false;
    }
    // Print the martix
    void toString() {
        for (int i = 0; i < _numVertices; i++) {
            std::cout << i << " : ";
            for (int j = 0; j < _numVertices; j++) { std::cout << _adjMatrix[i][j] << " "; }
            std::cout << "\n";
        }
    }
    ~Graph() { _adjMatrix.clear(); }
};
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.toString();
}
