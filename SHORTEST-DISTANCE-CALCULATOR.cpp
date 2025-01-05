#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

const int INF = INT_MAX;
const int MAX_NODES = 8;
const double SPEED = 10.0;

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int dest, int n) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {

        int minDist = INF, u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path exists from " << char(src + 'A') << " to " << char(dest + 'A') << ".\n";
        return;
    }

    cout << "Shortest distance from " << char(src + 'A') << " to " << char(dest + 'A') << ": " << dist[dest] << "\n";

    double distanceInKm = dist[dest] / 10.0; // Convert to km (1 = 100m, 10 = 1km)
    double timeInHours = distanceInKm / SPEED;
    double timeInMinutes = timeInHours * 60;

    cout << "Time to cover the distance at " << SPEED << " km/h: " << timeInMinutes << " minutes\n";

    cout << "Path: ";
    int current = dest;
    int path[MAX_NODES], pathIndex = 0;
    while (current != -1) {
        path[pathIndex++] = current;
        current = parent[current];
    }
    for (int i = pathIndex - 1; i >= 0; i--) {
        cout << char(path[i] + 'A');
        if (i != 0) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    int n = 8;
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 4, 2, 0, 0, 0, 0, 0},
        {4, 0, 0, 5, 0, 0, 0, 0},
        {2, 0, 0, 8, 7, 0, 0, 0},
        {0, 5, 8, 0, 2, 6, 0, 0},
        {0, 0, 5, 2, 0, 3, 4, 0},
        {0, 0, 0, 6, 3, 0, 1, 0},
        {0, 0, 0, 0, 4, 1, 0, 7},
        {0, 0, 0, 0, 0, 0, 7, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 0) {
                graph[j][i] = graph[i][j];
            }
        }
    }

    char srcChar, destChar;
    cout << "Enter SHOOLINI BLOCK source node (A-H): ";
    cin >> srcChar;
    cout << "Enter SHOOLINI BLOCK destination node (A-H): ";
    cin >> destChar;

    int src = srcChar - 'A';
    int dest = destChar - 'A';

    auto start = high_resolution_clock::now();
    dijkstra(graph, src, dest, n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " ms\n";

    return 0;
}
