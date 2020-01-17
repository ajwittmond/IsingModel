#include <drawable.h>
#include <vector>

struct Sample{
  double time;
  double value;
};

class Ticker : public Drawable {
private:
  Gtk::DrawingArea *area;
  std::vector<Sample> samples;

public:
  Ticker(Gtk::DrawingArea *area) : area{area} {
    this->connect(*area);
    auto win = area->get_window();
    win->invalidate_rect(area->get_allocation(), true );
  }

  void invalidate_rect() {
    auto win = area->get_window();
    win->invalidate_rect(area->get_allocation(), true);
  }

  virtual bool draw(const Cairo::RefPtr<Cairo::Context> &cr) override; 

  void tick(double time, double value) {
    samples.push_back((Sample){time,value});
  }
};
