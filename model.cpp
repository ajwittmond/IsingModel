#include "model.h"
#include <cstdlib>




double sigmoid(double x){
  return 1/(1 + exp(x));
}

void IsingModel::step(){
  std::vector<Node> nodes = graph.nodes;
  std::random_shuffle(nodes.begin(), nodes.end()); // reduces bias visible in animation
  for(Node& node : nodes){
    double beta = 1/(*t);
    double local_field = *h;
    for(int i: graph.edges[node.get_index()]){
      local_field += *j*graph.nodes[i].spin ;
    }
    double p = sigmoid(-2*beta*local_field);
    if ((!node.on_boundary) || boundary_type == VARIABLE){
      if (((double)rand() / (double)RAND_MAX) < p) {
        graph.nodes[node.get_index()].spin = 1;
      } else {
        graph.nodes[node.get_index()].spin = -1;
      }
    }
    if (graph.nodes[node.get_index()].spin == 1) {
      graph.nodes[node.get_index()].shape->set_fill_color(1, 1, 1, 1);
    } else {
      graph.nodes[node.get_index()].shape->set_fill_color(0, 0, 0, 1);
    }
  }
}

void IsingModel::set_boundary(BoundaryType boundary){
  bool even = true;
  std::cout << boundary << std::endl;
  for(Node& node : graph.get_boundary()){
    even = !even;
    switch(boundary){
    case POSITIVE:
      node.spin = 1;
      break;
    case NEGATIVE:
      node.spin = -1;
      break;
    case PERIODIC:
      node.spin = even ? 1 : -1 ;
      break;
    }
  }
  boundary_type = boundary;

}

BoundaryIterator& BoundaryIterator::operator++() {
    if (first == -1)
      find_first();

    if(start){
      start = false;
    }
    Node& node = graph.nodes[curr];
    for(int i = 0; i< graph.edges[curr].size();i++){
      int adjacent = graph.edges[curr][i];
      if(adjacent != prev && graph.nodes[adjacent].on_boundary){
        prev = curr;
        curr = adjacent;
        break;
      }
    }

    return *this;
}

Boundary Graph::get_boundary(){
  return Boundary(*this);
}

Graph rectangular_grid(int w, int h, double size, double gap) {
  Graph out;
  out.nodes = std::vector<Node>();
  out.edges = std::vector<std::vector<int>>(w*h);
  for(int i = 0; i<w*h ; i++)
    out.edges.push_back(std::vector<int>(3));
  for(int x = 0 ; x< w; x++){
    for(int y = 0; y<h; y++){
      Node n(std::make_shared<Square>(x * (size + gap) + size / 2,
                                     y * (size + gap) + size / 2,
                                     size,
                                     size),
             x * w + y);
      n.on_boundary = x==0 || y==0 || x==w-1 || y==h-1 ;
      out.add_node(n);
      if (x != 0) 
        out.add_twosided_edge(x * w + y,(x-1) * w + y);
      if(y != 0)
        out.add_twosided_edge(x * w + y,x*w + (y-1));
    }
  }
  return out;
}


