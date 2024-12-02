/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <limits>
#include <sstream>

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
    double x, y;

    Point(double xCoord = 0.0, double yCoord = 0.0) {
        if (!isfinite(xCoord) || !isfinite(yCoord)) {
            throw invalid_argument("Coordenadas inválidas");
        }
        x = xCoord;
        y = yCoord;
    }

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
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
vector<int> initializeDisjointSet(int size) {
    if (size < Config::MIN_NODES) {
        throw invalid_argument("Tamaño del conjunto inválido");
    }
    vector<int> parent(size);
    vector<int> rank(size, 0);
    for (int i = 0; i < size; i++) {
        parent[i] = i;
    }
    return parent;
}

int find(int x, vector<int>& parent) {
    if (x < 0 || x >= static_cast<int>(parent.size())) {
        throw out_of_range("Índice fuera de rango");
    }
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}

void unite(int x, int y, vector<int>& parent, vector<int>& rank) {
    int rootX = find(x, parent);
    int rootY = find(y, parent);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// BFS Function for Max Flow Calculation
bool bfs(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int numNodes = residualGraph.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int nextNode = 0; nextNode < numNodes; nextNode++) {
            if (!visited[nextNode] && residualGraph[currentNode][nextNode] > 0) {
                q.push(nextNode);
                parent[nextNode] = currentNode;
                visited[nextNode] = true;
            }
        }
    }

    return visited[sink];
}

// Function to read matrix from standard input
vector<vector<int>> readMatrix(int numNodes, const string& matrixName) {
    vector<vector<int>> matrix(numNodes, vector<int>(numNodes));
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (!(cin >> matrix[i][j])) {
                throw runtime_error("Error leyendo " + matrixName);
            }
            if (matrix[i][j] < 0) {
                throw invalid_argument(matrixName + " contiene valores negativos");
            }
        }
    }
    return matrix;
}

// Function to calculate the optimal cabling
vector<Edge> calculateOptimalCabling(int numNodes, const vector<vector<int>>& distances) {
    vector<Edge> edges;
    for (int i = 0; i < numNodes; i++) {
        for (int j = i + 1; j < numNodes; j++) {
            if (distances[i][j] > 0) {
                edges.emplace_back(i, j, distances[i][j]);
            }
        }
    }

    vector<Edge> minimumSpanningTree;
    vector<int> parent = initializeDisjointSet(numNodes);
    vector<int> rank(numNodes, 0);
    sort(edges.begin(), edges.end());

    for (const Edge& edge : edges) {
        if (find(edge.sourceNode, parent) != find(edge.destinationNode, parent)) {
            unite(edge.sourceNode, edge.destinationNode, parent, rank);
            minimumSpanningTree.push_back(edge);
        }
    }

    return minimumSpanningTree;
}

// Function to calculate delivery route
vector<int> calculateDeliveryRoute(int numNodes, const vector<vector<int>>& distances) {
    vector<bool> visited(numNodes, false);
    vector<int> route;
    
    int currentPos = 0;
    route.push_back(currentPos);
    visited[currentPos] = true;

    for (int i = 0; i < numNodes - 1; i++) {
        int nextPos = -1;
        int minDistance = numeric_limits<int>::max();

        for (int j = 0; j < numNodes; j++) {
            if (!visited[j] && distances[currentPos][j] < minDistance) {
                minDistance = distances[currentPos][j];
                nextPos = j;
            }
        }

        if (nextPos == -1) {
            throw runtime_error("No se encontró ruta válida");
        }

        route.push_back(nextPos);
        visited[nextPos] = true;
        currentPos = nextPos;
    }

    route.push_back(0);  // Regresar al inicio
    return route;
}

// Function to calculate max flow
int calculateMaxFlow(int numNodes, vector<vector<int>>& capacities) {
    vector<vector<int>> residualGraph = capacities;
    vector<int> parent(numNodes);
    int maxFlow = 0;
    int source = 0;
    int sink = numNodes - 1;

    while (bfs(residualGraph, source, sink, parent)) {
        int pathFlow = numeric_limits<int>::max();
        
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

// Function to find the nearest center
Point findNearestCenter(const vector<Point>& centers, const Point& location) {
    if (centers.empty()) {
        throw runtime_error("No hay centrales disponibles");
    }

    Point nearest = centers[0];
    double minDistance = location.distanceTo(centers[0]);

    for (size_t i = 1; i < centers.size(); i++) {
        double distance = location.distanceTo(centers[i]);
        if (distance < minDistance) {
            minDistance = distance;
            nearest = centers[i];
        }
    }

    return nearest;
}
