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
    int index = node.get_index();
    Node& orig = graph.nodes[index];
    for(int i: graph.edges[index]){
      local_field += *j*graph.nodes[i].spin ;
    }
    double p = sigmoid(-2*beta*local_field);
    if ((!node.on_boundary) || boundary_type == VARIABLE){
      if (((double)rand() / (double)RAND_MAX) < p) {
        graph.nodes[index].spin = 1;
      } else {
        graph.nodes[index].spin = -1;
      }
    }
    if (graph.nodes[node.get_index()].spin == 1) {
      orig.shape->set_fill_color(1, 1, 1, 1);
    } else {
      orig.shape->set_fill_color(0, 0, 0, 1);
    }
  }
  if (left_pressed || right_pressed)
    set_point();
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

double IsingModel::get_scale(){
  double height = 0;
  for(Node& node: graph.nodes){
    height = std::max(height,node.shape->bottom());
  }
  return (double)area->get_allocation().get_height()/height;
}

bool IsingModel::draw(const Cairo::RefPtr<Cairo::Context> &cr){
  double scale = get_scale();
  cr->scale(scale,scale);
  return graph.draw(cr);
}

void IsingModel::set_mouse(double x, double y){
  double scale = get_scale();
  const Gtk::Allocation alloc = area->get_allocation();
  mx = (x-alloc.get_x())/scale;
  my = (y-alloc.get_y())/scale;
}

void IsingModel::process_state(guint state){
  left_pressed = ( state & Gdk::BUTTON1_MASK ) != 0;
  right_pressed = ( state & Gdk::BUTTON3_MASK ) != 0;
}

bool IsingModel::on_button(GdkEventButton *evt){
  set_mouse(evt->x,evt->y);
  //process_state(evt->state);
  if (left_pressed || right_pressed) {
    set_point();
  }
  return false;
}

bool IsingModel::on_motion(GdkEventMotion * evt){
  set_mouse(evt->x, evt->y);
  process_state(evt->state);
  if (left_pressed || right_pressed) {
    set_point();
  }
  return false;
}

void IsingModel::set_point(){
  bool changed = false;
  for(Node& node : graph.nodes){
    if(node.shape->point_inside(mx, my) && !(node.on_boundary && boundary_type!=VARIABLE)){
      if (left_pressed) {
        node.spin = 1;
        node.shape->set_fill_color(1, 1, 1, 1);
      } else if (right_pressed) {
        node.spin = -1;
        node.shape->set_fill_color(0, 0, 0, 1);
      }
      changed = true;
    }
  }
  if(changed)
    this->invalidate_rect();
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
             x * h + y);
      n.on_boundary = x==0 || y==0 || x==w-1 || y==h-1 ;
      out.add_node(n);
      if (x != 0)
        out.add_twosided_edge(x*h + y,(x-1)*h + y);
      if(y != 0)
        out.add_twosided_edge(x*h + y,x*h + (y-1));
    }
  }
  return out;
}

