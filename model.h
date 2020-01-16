#include <vector>
#include "drawable.h"


struct Node{

  bool spin;
};


struct Graph{
  std::vector<Node> nodes;
  std::vector<std::vector<int>> edges;
};


class IsingModel{
 public:
  Graph graph;
  double h;
  double j;
  double t;
  IsingModel(Graph graph,double h,double j,double t);
  void step();
};

