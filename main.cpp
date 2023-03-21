#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
};

struct Vertex {
    int id;
    int degree;
    int in_degree;
    int out_degree;
};

int main() {
    // Abrir archivo de entrada
    ifstream fin("aristas.txt");

    // Leer número de vértices y número de aristas
    int n, m;
    fin >> n >> m;

    // Leer lista de aristas
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        fin >> edges[i].u >> edges[i].v;
    }

    // Cerrar archivo de entrada
    fin.close();

    // Generar archivo de vértices
    ofstream vertices_out("vertices.txt");
    for (int i = 1; i <= n; i++) {
        vertices_out << i << endl;
    }
    vertices_out.close();

    // Generar archivo de aristas
    ofstream aristas_out("aristas.txt");
    for (int i = 0; i < m; i++) {
        aristas_out << edges[i].u << " " << edges[i].v << endl;
    }
    aristas_out.close();

    // Determinar el tipo de grafo
    bool is_directed = true;
    bool is_undirected = true;
    bool is_multigraph = false;
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 0; j < m; j++) {
            if (edges[j].u == i || edges[j].v == i) {
                count++;
            }
        }
        if (count > 1) {
            is_multigraph = true;
        }
        if (count == 0 || count > 1) {
            is_undirected = false;
        }
        if (count == 0) {
            is_directed = false;
        }
    }
    string type;
    if (is_directed && !is_undirected) {
        type = "dirigido";
    } else if (!is_directed && is_undirected) {
        type = "no dirigido";
    } else if (is_multigraph) {
        type = "multigrafo";
    } else {
        type = "mixto";
    }
    cout << "Tipo de grafo: " << type << endl;

    // Determinar el grado de cada vértice
    map<int, int> degree_map;
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 0; j < m; j++) {
            if (edges[j].u == i || edges[j].v == i) {
                count++;
            }
        }
        degree_map[i] = count;
    }
    cout << "Grado de cada vértice: " << endl;
    for (auto it = degree_map.begin(); it != degree_map.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    // Determinar el grado de entrada y salida de cada vértice
    map<int, Vertex> vertex_map;
    for (int i = 1; i <= n; i++) {
        vertex_map[i].id = i;
        vertex_map[i].degree = 0;
        vertex_map[i].in_degree = 0;
        vertex_map[i].out_degree = 0;
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        vertex_map[u].degree++;
        vertex_map[v].degree++;
        if (is_directed) {
            vertex_map[u].out_degree++;
            vertex_map[v].in_degree++;
        }
    }
    if (is_directed) {
        cout << "Grado de entrada y salida de cada vértice: " << endl;
        for (auto it = vertex_map.begin(); it != vertex_map.end(); it++) {
            cout << it->first << ": " << it->second.in_degree << " " << it->second.out_degree << endl;
        }
    }

    // Generar archivo CSV con la información del grafo
    ofstream csv_out("grafo.csv");
    csv_out << "Tipo,";
    if (is_directed) {
        csv_out << "Grado de entrada,Grado de salida,";
    } else {
        csv_out << "Grado,";
    }
    csv_out << "Id de vértice" << endl;
    for (int i = 1; i <= n; i++) {
        csv_out << type << ",";
        if (is_directed) {
            csv_out << vertex_map[i].in_degree << "," << vertex_map[i].out_degree << ",";
        } else {
            csv_out << vertex_map[i].degree << ",";
        }
        csv_out << vertex_map[i].id << endl;
    }
    csv_out.close();

    return 0;
}
