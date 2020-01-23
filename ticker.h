#pragma once

#include <drawable.h>
#include <vector>

struct Sample{
  double time;
  double value;
};

class Ticker : public Drawable , public AreaController{
private:
  std::vector<Sample> samples;
  
public:
  double ymax;
  double ymin;
  double xrange = 5;
  Ticker(Gtk::DrawingArea *area, double ymax, double ymin, double xrange) :
    AreaController(area),ymax{ymax}, ymin{ymin}, xrange{xrange} {
    this->connect(*area);
  }

  virtual bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override; 

  void tick(double time, double value) {
    samples.push_back((Sample){time,value});
    invalidate_rect();
  }
};
