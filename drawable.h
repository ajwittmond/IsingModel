#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>
#include <vector>

class Drawable : public sigc::trackable{
protected:
  std::vector<Drawable*> children;

  bool drawChildren(const Cairo::RefPtr<Cairo::Context>& cr) {
    bool out = false;
    for(Drawable* d: children){
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
  void addChild(Drawable &d) { children.push_back(&d); }

  void removeChild(Drawable &d) {
    children.erase(std::find(children.begin(), children.end(), &d));
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
public:
  double x=0,y=0; // coordinates of center
  double angle=0;
  double r=0,g=0,b=0,a=1;
  double sx=1,sy=1; //size of bounding box

  Shape() = default;

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
};

class Square : public Shape{
public:
  Square() = default;

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
