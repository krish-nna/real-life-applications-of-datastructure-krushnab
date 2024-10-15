#include <stdio.h>
#include <limits.h>

#define MAX 100

void addRoad(int graph[MAX][MAX], int u, int v, int weight);
void displayGraph(int graph[MAX][MAX], int vertices);
void dijkstra(int graph[MAX][MAX], int src, int vertices);

int main() {
    int graph[MAX][MAX];
    int vertices, edges, u, v, weight;

    printf("Enter the number of intersections (vertices): ");
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the number of roads (edges): ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter road (start intersection, end intersection, distance): ");
        scanf("%d %d %d", &u, &v, &weight);
        addRoad(graph, u, v, weight);
    }

    displayGraph(graph, vertices);

    int start;
    printf("Enter the starting intersection for Dijkstra's shortest path: ");
    scanf("%d", &start);

    dijkstra(graph, start, vertices);

    return 0;
}

void addRoad(int graph[MAX][MAX], int u, int v, int weight) {
    graph[u][v] = weight;
    graph[v][u] = weight;
}

void displayGraph(int graph[MAX][MAX], int vertices) {
    printf("\nRoad Network (Adjacency Matrix):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int minDistance(int dist[], int visited[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int graph[MAX][MAX], int src, int vertices) {
    int dist[MAX];
    int visited[MAX];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX, visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from intersection %d:\n", src);
    for (int i = 0; i < vertices; i++) {
        printf("To %d: %d\n", i, dist[i]);
    }
}
