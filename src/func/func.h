#include <vector>
#include <string>
#include <limits>

// Configuration namespace
namespace Config {
    extern const int MIN_NODES;
    extern const int MAX_NODES;
    extern const double MAX_DISTANCE;
    extern const double EPSILON;
}

using namespace std;

// Logger class declaration
class Logger {
public:
    static void logError(const string& message);
    static void logInfo(const string& message);
    static void logWarning(const string& message);
};

// Point class declaration
class Point {
public:
    double x, y;

    Point(double xCoord = 0.0, double yCoord = 0.0);
    double distanceTo(const Point& other) const;
    string toString() const;
};

// Edge class declaration
class Edge {
public:
    int sourceNode;
    int destinationNode;
    int weight;

    Edge(int source, int destination, int edgeWeight);
    bool operator<(const Edge& other) const;
};

// DisjointSet class declaration
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    explicit DisjointSet(int size);
    int find(int x);
    void unite(int x, int y);
};

// NetworkOptimizer class declaration
class NetworkOptimizer {
private:
    int numNodes;
    vector<vector<int>> distances;
    vector<vector<int>> capacities;
    vector<Point> centers;

    vector<vector<int>> readMatrix(const string& matrixName);
    bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent);

public:
    NetworkOptimizer(int N, const vector<vector<int>>& dis, const vector<vector<int>>& cap, const vector<Point>& cent);
    void readCenters();
    vector<Edge> calculateOptimalCabling();
    vector<int> calculateDeliveryRoute();
    int calculateMaxFlow();
    Point findNearestCenter(const Point& location);
};

/// @brief Computes the factorial of a given number.
/// @param number The number for which the factorial is to be computed.
/// @return The factorial of the given number.
unsigned int factorial(unsigned int number);