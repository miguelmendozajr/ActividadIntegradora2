#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Config Constants
namespace Config {
    const int MIN_NODES = 1;
    const int MAX_NODES = 1000;
    const double MAX_DISTANCE = 1000000.0;
    const double EPSILON = 1e-10;
}

// Point Structure
struct Point {
    int x, y;

    Point(int xCoord = 0.0, int yCoord = 0.0) {
        if (!isfinite(xCoord) || !isfinite(yCoord)) {
            throw invalid_argument("Coordenadas inválidas");
        }
        x = xCoord;
        y = yCoord;
    }

    double distanceTo(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    string toString() const {
        ostringstream oss;
        oss << fixed << setprecision(2) << "(" << x << ", " << y << ")";
        return oss.str();
    }
};

// Edge Structure
struct Edge {
    int sourceNode;
    int destinationNode;
    int weight;

    Edge(int source, int destination, int edgeWeight)
        : sourceNode(source), destinationNode(destination), weight(edgeWeight) {
        if (edgeWeight < 0) {
            throw invalid_argument("Peso de arista negativo");
        }
    }

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Functions for Kruskal's Algorithm
vector<int> initializeDisjointSet(int size);

int find(int x, vector<int>& parent);

void unite(int x, int y, vector<int>& parent, vector<int>& rank);

// BFS Function for Max Flow Calculation
bool bfs(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent);

// Function to read matrix from standard input
vector<vector<int>> readMatrix(int numNodes, const string& matrixName);

// Function to calculate the optimal cabling
vector<Edge> calculateOptimalCabling(int numNodes, const vector<vector<int>>& distances);

// Function to calculate delivery route
vector<int> calculateDeliveryRoute(int numNodes, const vector<vector<int>>& distances);

// Function to calculate max flow
int calculateMaxFlow(int numNodes, const vector<vector<int>>& capacities);

// Function to find the nearest center
Point findNearestCenter(const vector<Point>& centers, const Point& location);