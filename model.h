#pragma once

#include <vector>
#include "drawable.h"
#include <iostream>


class Node : public ChildDrawer{
private:
  int index;
public:
  
  int spin = 1;
  bool fixed = false;
  bool on_boundary=false;
  std::shared_ptr<Shape> shape;

  Node(std::shared_ptr<Shape> &&shape, int index)
    : index(index),shape(shape) {
    std::shared_ptr<Drawable> d = shape;
    addChild(shape);
  }

  int get_index(){
    return index;
  }

  ~Node() = default;
};


class Boundary;

class Graph : public Drawable{
public:
  Graph() = default;
  ~Graph() = default;

  std::vector<Node> nodes;
  std::vector<std::vector<int>> edges;

  bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override{
    for(Node & n: nodes){
      n.draw(cr);
    }
    return false;
  }

  Boundary get_boundary();

  Graph& add_twosided_edge(int a, int b){
    add_edge(a,b);
    add_edge(b,a);
  }

  Graph& add_edge(int a , int b){
    edges[a].push_back(b);
  }

  Graph& add_node(Node n){
    nodes.push_back(n);
  }

};

class BoundaryIterator : public std::iterator<std::forward_iterator_tag, Node>{
private:
  int curr = -1;
  int first = -1;
  int prev = -1;
  bool start = true;
  Graph& graph;
  void find_first(){
    for(first =0; first<graph.nodes.size(); first++)
      if(graph.nodes[first].on_boundary)
        break;
    curr=first;
    prev=first;
  }
public:
  BoundaryIterator(Graph &graph) : graph(graph) {}

  BoundaryIterator(const BoundaryIterator &iter) : curr(iter.curr), graph(iter.graph) {}

  BoundaryIterator &operator++();

  bool operator!=(const BoundaryIterator& it){
    return !start && curr==first;
  }

  Node& operator*(){
    if(first==-1)
      find_first();
    return graph.nodes[first];
  }

};

class Boundary{
private:
  Graph &graph;

public:
  Boundary(Graph &graph) : graph(graph) {}

  BoundaryIterator begin(){ return BoundaryIterator(graph); }

  BoundaryIterator end() { return BoundaryIterator(graph); }
};


class IsingModel : public Drawable, public AreaController{
 public:
  Graph graph;
  double h;
  double j;
  double t;


  IsingModel(Gtk::DrawingArea *area, Graph graph, double h, double j, double t)
    : graph(graph), h(h), j(j), t(t),  AreaController(area) {
    connect(*area);
  }

  void step();

  bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override{
    static int x = 0;
    return graph.draw(cr);
  }
};

//generates a rectangular grid of the the given width and height
Graph rectangular_grid(int w, int h, double size,double gap);
