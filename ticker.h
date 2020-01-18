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
  Ticker(Gtk::DrawingArea *area) : AreaController(area) {
    this->connect(*area);
  }

  virtual bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override; 

  void tick(double time, double value) {
    samples.push_back((Sample){time,value});
  }
};
