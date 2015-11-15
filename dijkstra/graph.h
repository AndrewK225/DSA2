#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

#include <string>
#include <list>
#include <fstream>

class graph {

 public:

  graph(int capacity=1000);

  /*
   Insert a vertex into the graph with string 'id'
   Returns true on success, false if the vertex exists already.
   */
  bool insert_vertex(std::string id);

  bool check_vertex(std::string id);

  /*
   * Insert an edge with given start and end string ids with cost dist
   */
  void insert_edge(std::string start, std::string end, int dist);

  /*
   * Dijkstra's algorithm.
   */
  void Dijkstra(std::string sourceVertex);

  void output(std::string filename);

 private:
  // Nested edge class
  class edge;

  // Nested vertex class
  class vertex {
  public:
    std::string name;
    bool isKnown;
    int dist;
    std::list<edge *> adj;
    vertex *prev;
  };

  class edge {
  public:
    int weight;
    vertex *destination;
  };

  std::list<vertex *> vertices;
  HashTable *vertex_map;
};

#endif
