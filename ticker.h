#include <drawable.h>
#include <vector>

struct Sample{
  double time;
  double value;
};

class Ticker : public Drawable{
private:
  std::vector<Sample> samples;
public:
  Ticker(double initial);

  void tick(double time, double value) {
    samples.push_back((Sample){time,value});
  }
};
