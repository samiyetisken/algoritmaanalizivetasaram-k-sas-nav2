#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 5

// Minimum fonksiyonu
int min(int a, int b) {
    return a < b ? a : b;
}

// TSP için gerekli matris
int tspGraph[N][N] = {
    {0, 2, 9, INT_MAX, 1},
    {2, 0, 6, 4, INT_MAX},
    {9, 6, 0, 3, 8},
    {INT_MAX, 4, 3, 0, 5},
    {1, INT_MAX, 8, 5, 0}
};

// MST oluþturma fonksiyonu
void createMST(int graph[N][N], int parent[N]) {
    int key[N], mstSet[N];
    for (int i = 0; i < N; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < N-1; count++) {
        int u, minKey = INT_MAX;
        for (int v = 0; v < N; v++)
            if (!mstSet[v] && key[v] < minKey)
                minKey = key[v], u = v;
        mstSet[u] = 1;
        for (int v = 0; v < N; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

// Euler turu oluþturma fonksiyonu
void createEulerTour(int graph[N][N], int parent[N], int eulerTour[]) {
    int index = 0;
    for (int i = 0; i < N; i++)
        if (parent[i] != -1)
            eulerTour[index++] = parent[i], eulerTour[index++] = i;
}

// Minimum maliyetli tur bulma fonksiyonu
void tsp(int graph[N][N], int tour[]) {
    int parent[N], eulerTour[2*N];
    createMST(graph, parent);
    createEulerTour(graph, parent, eulerTour);
    int added[N] = {0}, index = 0;
    for (int i = 0; i < 2*N; i++)
        if (!added[eulerTour[i]])
            tour[index++] = eulerTour[i], added[eulerTour[i]] = 1;
    tour[index] = 0;
}

// Test fonksiyonu
void test() {
    int tour[N+1];
    tsp(tspGraph, tour);
    printf("Minimum maliyetli tur: ");
    for (int i = 0; i < N+1; i++)
        printf("%d ", tour[i]);
    printf("\n");
}

int main() {
    test();
    return 0;
}
