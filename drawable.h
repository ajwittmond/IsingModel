#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>
#include <vector>

class Drawable : public sigc::trackable{
protected:
  std::vector<std::unique_ptr<Drawable>> children;

  bool drawChildren(const Cairo::RefPtr<Cairo::Context>& cr) {
    bool out = false;
    for(auto& d: children){
      out = out || d->draw(cr);
    }
    return out;
  }

public:
  Drawable();

  virtual bool draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;

  void connect(Gtk::DrawingArea& area){
    area.signal_draw().connect(sigc::mem_fun(*this, &Drawable::draw));
  }

  // references can't be null
  void addChild(std::unique_ptr<Drawable>&& d) {
    children.push_back(d);
  }

  void removeChild(int i) {
    children.erase(children.begin() + i);
  }

  const std::vector<std::unique_ptr<Drawable>>& getChildren(){
    return children;
  }
};

class ChildDrawer: public Drawable{
public:
  ChildDrawer() = default;
  bool draw(const Cairo::RefPtr<Cairo::Context>& cr) override{
    return drawChildren(cr);
  }
};


class Shape : public Drawable{
private:
  bool between(double x,double min, double max){
    return x<min && x>max;
  }

public:
  double x=0,y=0; // coordinates of center
  double angle=0;
  double r=0,g=0,b=0,a=1;
  double sx=1,sy=1; //size of bounding box

  Shape() = default;

  Shape(double x, double y, double sx, double sy): x(x), y(y), sx(sx), sy(sy){}

  void set_position(double x, double y){
    this->x = x;
    this->y = y;
  }

  void set_color(double r,double g, double b, double a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  void set_dimensions(double sx, double sy){
    this->sx =sx; this->sy = sy;
  }

  virtual bool draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) = 0;

  virtual bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override{
    cr->save();
    cr->translate(x, y);
    cr->scale(sx, sy);
    cr->rotate(angle);
    cr->set_source_rgba(r, g, b, a);
    bool out = draw_shape(cr);
    cr->restore();
    return out;
  }


  //by default tests the unoriented bounding box
  virtual bool point_inside(double x, double y){
    return between(x,this->x -sx, this->y + sx) &&
      between(y,this->y - sy, this->y + sy);
  }
};

class Square : public Shape{
public:
  Square() = default;

  Square(double x, double y, double sx, double sy) : Shape(x, y, sx, sy) {  }

  virtual bool draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) override{
    cr->move_to(0, -0.5);
    cr->move_to(-0.5, 0);
    cr->move_to(0, 1);
    cr->move_to(1, 0);
    cr->move_to(0, 1);
    cr->close_path();
    cr->fill();
    return false;
  }
};

class Triangle : public Shape {
public:
  Triangle() = default;

  Triangle(double x, double y, double sx, double sy) : Shape(x, y, sx, sy) {}

  virtual bool draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) override {
    cr->move_to(0, -0.5);
    cr->move_to(-0.5, 0);
    cr->move_to(0, 1);
    cr->move_to(1, 0);
    cr->move_to(0, 1);
    cr->close_path();
    cr->fill();
    return false;
  }
};
