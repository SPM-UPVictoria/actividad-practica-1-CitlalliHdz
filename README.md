# Actividad Práctica 1: Estructura de Datos de Grafos.


Implementar en C++ un programa que mediante una **lista de aristas** (Edge List) genere la representación de uno o más grafos almacenados en dos archivos llamados: `vertices.txt` y `aristas.txt`, y que además calcule lo siguiente:

  * Determinar el tipo de grafo: grafo simple, multi-grafo, grafo dirigido, grafo no dirigido o grafo mixto.
  * Determinar el grado de cada vértice.
  * En el caso de grafos dirigidos y grafos mixtos determinar el grado de entrada y grado de salida de cada vértice.

Como salida se deberá generar un archivo CSV con la información de cada grafo.


## Ejemplo de los archivos de entrada

### vertices.txt

  > a,b,c,d,e
  > tokio, New York, Colima, Singapur, Argentina  
  > 7, 6, 8, 9, 10


### aristas.txt

  > {{a,b}, {b, a}, {c, d}, {a, e}, {e, c}}
  > {(Tokio, Argentina}, {New York, Colima}, (New York, Tokio)}
  > {(7, 8), (8, 7), (10, 9), (8, 10)}

 
