#include <iostream>
#include <vector>
#include <random>
#include <locale> // Для setlocale

using namespace std;

void dfs(const vector<vector<int>>& graph, int v, vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    cout << v << " ";
    for (int u = 0; u < graph.size(); ++u) {
        if (graph[v][u] == 1 && !visited[u]) {
            dfs(graph, u, visited, result);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int num_vertices;
    cout << "Введите количество вершин: ";
    cin >> num_vertices;

    if (num_vertices <= 0) {
        cerr << "Количество вершин должно быть больше 0." << endl;
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    vector<vector<int>> adjacency_matrix(num_vertices, vector<int>(num_vertices));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i; j < num_vertices; ++j) {
            if (i == j) {
                adjacency_matrix[i][j] = 0;
            }
            else {
                adjacency_matrix[i][j] = adjacency_matrix[j][i] = distrib(gen);
            }
        }
    }

    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            cout << adjacency_matrix[i][j] << "\t";
        }
        cout << endl;
    }

    int start_vertex;
    cout << "Введите начальную вершину для обхода (от 0 до " << num_vertices - 1 << "): ";
    cin >> start_vertex;

    if (start_vertex < 0 || start_vertex >= num_vertices) {
        cerr << "Некорректный номер начальной вершины." << endl;
        return 1;
    }

    cout << "Результат обхода в глубину: ";
    vector<bool> visited(num_vertices, false);
    vector<int> result;

    dfs(adjacency_matrix, start_vertex, visited, result);

    cout << endl;
    return 0;
}