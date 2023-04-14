#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_VERTICES = 100;
int grafo[MAX_VERTICES][MAX_VERTICES];
int num_vertices;

// Función para calcular el grado de un vértice en una matriz de adyacencia
int grado_vertice(int vertice, int grafo[][MAX_VERTICES]) {
    int grado = 0;
    for (int i = 0; i < num_vertices; i++) {
        if (grafo[vertice][i] == 1) {
            grado++;
        }
    }
    return grado;
}

// Función para determinar el tipo de grafo en base a su matriz de adyacencia
string tipo_grafo(int grafo[][MAX_VERTICES]) {
    bool dirigido = false;
    bool no_dirigido = false;
    bool multi = false;

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (grafo[i][j] != grafo[j][i]) {
                dirigido = true;
                no_dirigido = true;
            } else if (grafo[i][j] > 1) {
                multi = true;
            }
        }
    }

    if (dirigido && no_dirigido) {
        return "Grafo mixto";
    } else if (dirigido) {
        return "Grafo dirigido";
    } else if (no_dirigido && multi) {
        return "Multi-grafo no dirigido";
    } else if (no_dirigido) {
        return "Grafo simple no dirigido";
    } else {
        return "Grafo no dirigido";
    }
}

int main() {
    // Leer la lista de aristas desde el archivo aristas.txt
    vector<pair<int, int>> aristas;
    ifstream archivo_aristas("aristas.txt");
    int a, b;
    while (archivo_aristas >> a >> b) {
        aristas.push_back(make_pair(a, b));
    }
    archivo_aristas.close();

    // Encontrar el número de vértices
    num_vertices = 0;
    for (auto arista : aristas) {
        num_vertices = max(num_vertices, max(arista.first, arista.second));
    }
    num_vertices++;

    // Crear la matriz de adyacencia
    for (auto arista : aristas) {
        grafo[arista.first][arista.second] = 1;
        grafo[arista.second][arista.first] = 1;
    }

    // Calcular el grado de cada vértice y mostrar los resultados
    for (int i = 0; i < num_vertices; i++) {
        cout << "El grado del vértice " << i << " es " << grado_vertice(i, grafo) << endl;
    }

    // Determinar el tipo de grafo
    cout << "El grafo es de tipo " << tipo_grafo(grafo) << endl;

    return 0;
}
