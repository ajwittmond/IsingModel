#include "ticker.h"


bool Ticker::draw(const Cairo::RefPtr<Cairo::Context> &cr){
  double max_time = 0;
  double max_value = 0;
  for(Sample s : samples){
    max_time = std::max(max_time, s.time);
    max_value = std::max(max_value, s.value);
  }


  //draw y-axis
  //draw x-axis
  //draw curve
  return false;
}
