/* Andrew Koe
   Dijkstra

   Takes input file describing a graph and then applies Dijkstra's algorithm
   to find shortest path from start to dest.

   11/12/14
*/


#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream> //istringstream
#include <cstdlib> //for exit();

#include "graph.h"

using namespace std;

void load_graph(graph &graph, ifstream &in) {

  string line, start, end;
  int weight;

  while (getline(in,line)) {
    istringstream stream(line); //easier to parse
    stream >> start >> end >> weight;

    graph.insert_edge(start,end,weight);
  }
  return;

}

int main() {

  string infile, outfile,start;

  cout << "Enter name of graph file: ";
  cin >> infile;
  ifstream input(infile.c_str());
  if (!input.is_open()) {
    cout << "Invalid Filename: " << infile << endl;
    exit(1);
  }

  graph graph(1000); //allocate some space to start, can be resized if needed
  load_graph(graph, input);

 
  cout << "Enter a valid vertex id for the starting vertex: ";
  cin >> start;
  while(!graph.check_vertex(start)) {
    cout << "Enter a VALID vertex id for the starting vertex: ";
    cin >> start;
  }


  clock_t t1 = clock();
  graph.Dijkstra(start);
  clock_t t2 = clock();

  double time = ((double) (t2-t1)) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
  cout << time << endl;

  cout << "Enter name of output file: ";
  cin >> outfile;

  graph.output(outfile);

  return 0;
}
