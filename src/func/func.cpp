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
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include "func.h"

using namespace std;

unsigned int factorial(unsigned int number) {
    unsigned int result = 1;
    for (unsigned int i = 2; i <= number; i++) {
        result *= i;
    }
    return result;
}

namespace Config {
    const int MIN_NODES = 1;
    const int MAX_NODES = 1000;
    const double MAX_DISTANCE = 1000000.0;
    const double EPSILON = 1e-10;
}

class Logger {
public:
    static void logError(const string& message) {
        cerr << "[ERROR] " << message << endl;
    }

    static void logInfo(const string& message) {
        cout << "[INFO] " << message << endl;
    }

    static void logWarning(const string& message) {
        cout << "[WARNING] " << message << endl;
    }
};

class Point {
public:
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

// Estructura para representar una arista en el grafo
class Edge {
public:
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

// Clase DisjointSet para el algoritmo de Kruskal
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    explicit DisjointSet(int size) {
        if (size < Config::MIN_NODES) {
            throw invalid_argument("Tamaño del conjunto inválido");
        }
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x < 0 || x >= static_cast<int>(parent.size())) {
            throw out_of_range("Índice fuera de rango");
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

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
};

class NetworkOptimizer {
private:
    int numNodes;
    vector<vector<int>> distances;
    vector<vector<int>> capacities;
    vector<Point> centers;

    vector<vector<int>> readMatrix(const string& matrixName) {
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

    bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
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

public:
    NetworkOptimizer(int N, vector<vector<int>> dis, vector<vector<int>> cap, vector<Point> cent){
    }

    void readCenters() {
        for (int i = 0; i < numNodes; i++) {
            double x, y;
            if (!(cin >> x >> y)) {
                throw runtime_error("Error leyendo coordenadas de central " + to_string(i + 1));
            }
            centers.emplace_back(x, y);
        }
    }

    vector<Edge> calculateOptimalCabling() {
        vector<Edge> edges;
        for (int i = 0; i < numNodes; i++) {
            for (int j = i + 1; j < numNodes; j++) {
                if (distances[i][j] > 0) {
                    edges.emplace_back(i, j, distances[i][j]);
                }
            }
        }

        vector<Edge> minimumSpanningTree;
        DisjointSet ds(numNodes);
        sort(edges.begin(), edges.end());

        for (const Edge& edge : edges) {
            if (ds.find(edge.sourceNode) != ds.find(edge.destinationNode)) {
                ds.unite(edge.sourceNode, edge.destinationNode);
                minimumSpanningTree.push_back(edge);
            }
        }

        return minimumSpanningTree;
    }

    vector<int> calculateDeliveryRoute() {
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

    int calculateMaxFlow() {
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

    Point findNearestCenter(const Point& location) {
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
};

NetworkOptimizer::NetworkOptimizer(int N, const vector<vector<int>>& dis, const vector<vector<int>> &cap, const vector<Point>& cent)
{
    numNodes = N;
    distances = dis;
    capacities = cap;
    centers = cent;
    if (N < Config::MIN_NODES || N > Config::MAX_NODES) {
        throw invalid_argument("Número de nodos fuera de rango válido");
    }

    try {
        Logger::logInfo("Inicializando matrices de red...");
        // Additional validation or processing can be added here
    } catch (const std::bad_alloc& e) {
        throw runtime_error("Error de memoria al inicializar: " + string(e.what()));
    } catch (const std::exception& e) {
        throw runtime_error("Error en inicialización: " + string(e.what()));
    }
}