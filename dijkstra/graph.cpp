/*
Andrew Koe
 
Implements the graph functions described in graph.h.  Provides functions to add edges and vertices, apply Dijkstra's algorithm, and check presence of a vertex
 */

#include "graph.h"
#include <iostream>
#include <cstdlib>

#define INFINITY 1000000000  //everything guaranteed under a billion

graph::graph(int capacity) { //constructor

  this->vertex_map = new HashTable(capacity);
}

bool graph::insert_vertex(std::string id) {
  if(this->check_vertex(id)) {
    return false;
  }

  vertex *v = new vertex();
  v->name = id;
  this->vertex_map->insert(id, v);
  this->vertices.push_back(v);
  return true;

}

bool graph::check_vertex(std::string id) {
  return this->vertex_map->contains(id);
}

void graph::insert_edge(std::string start, std::string end, int dist) {

  this->insert_vertex(start);
  this->insert_vertex(end);

  bool key_exists = false;
  vertex *dest = (vertex *)(this->vertex_map->getPointer(end, &key_exists));

  edge *e = new edge();
  e->weight = dist;  
  e->destination = dest;

  vertex *source = (vertex *)(this->vertex_map->getPointer(start, &key_exists));
  source->adj.push_back(e);

}


void graph::Dijkstra(std::string start_vertex) {
  // std::cout << "about to go into dijk"<<std::endl;
  heap graph(this->vertices.size()+1);

  std::list<vertex *>::iterator it;
  for (it=this->vertices.begin(); it!=this->vertices.end(); it++) {
    if ((*it)->name == start_vertex) {
      (*it)->dist = 0;
    }
    else {
      (*it)->dist = INFINITY;  //initally everything sans start is inf
    }

    (*it)->isKnown = false;  //everything sans start is "unknown"
    (*it)->prev = NULL;
    graph.insert((*it)->name, (*it)->dist, (*it));
  }

  vertex *v;
  while (graph.deleteMin(NULL,NULL,&v) != 1) {
    //std::cout<<"Changing to known"<<std::endl;
    v->isKnown = true; //add to set of known vertices
    std::list<edge *>::iterator it2;
    if (v->dist == INFINITY) {
      continue;
    }

    for (it2=v->adj.begin(); it2!=v->adj.end(); it2++) {
      int new_weight = v->dist + (*it2)->weight; //update weight at each it
      //std::cout<< "new weight is "<<new_weight << std::endl;
      if (new_weight < (*it2)->destination->dist) {
	(*it2)->destination->dist = new_weight;
	graph.setKey((*it2)->destination->name,new_weight);
	(*it2)->destination->prev = v;
      }
    }
  }

}


void graph::output(std::string filename) {

  std::ofstream out(filename.c_str());
  std::list<vertex *>::iterator it;
  std::string path;

  if(!out.is_open()) {
    std::cout << "could not open output file" << std::endl;   
    std::exit(1);
  }

  for (it=this->vertices.begin(); it!=this->vertices.end(); it++) {
    out << (*it)->name << ": ";
    vertex *v = (*it);

    if (v->dist == INFINITY) {
      out << "NO PATH" << std::endl;
    }
    else if (v->dist == 0) {
      out << v->dist << " [" << v->name << "]" << std::endl;
    }
    else {
      out << v->dist << " [";
      path = v->name;
      while (v->prev != NULL) {
	path = v->prev->name + ", " + path;
	v = v->prev;
      }
      out << path << "]" << std::endl;
    }
  }

}
