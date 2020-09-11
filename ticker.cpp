#include "ticker.h"
#include <iostream>


bool Ticker::draw(const Cairo::RefPtr<Cairo::Context> &cr){
  double max_time = 0;
  double max_value = 0;
  for(Sample s : samples){
    max_time = std::max(max_time, s.time);
    max_value = std::max(max_value, s.value);
  }

  double scale = area->get_allocation().get_height();
  double width = area->get_allocation().get_width()/scale;

  cr->scale(scale, scale);


  cr->set_line_width(1/scale);
  //draw y-axis
  cr->set_source_rgb(1,1,1);
  cr->rectangle(0, 0, width, 1);
  cr->fill();

  cr->set_source_rgb(0, 0, 0);
  cr->move_to(0.1, 0);
  cr->line_to(0.1, 1);
  cr->stroke();

  cr->move_to(0.05,0.1);
  cr->line_to(0.15,0.1);
  cr->stroke();

  cr->move_to(0.16,0.1);
  cr->scale(1/scale, 1/scale);
  cr->show_text(std::to_string(ymax));
  cr->scale( scale,  scale);
  cr->fill();

  cr->move_to(0.05, 0.9);
  cr->line_to(0.15, 0.9);
  cr->stroke();

  cr->move_to(0.16, 0.9);
  cr->scale(1/scale, 1/scale);
  cr->show_text(std::to_string(ymax));
  cr->scale( scale,  scale);
  cr->fill();

  //draw x-axis
  if (ymin < 0) {
    cr->move_to(0, -ymin/(ymax-ymin)*0.8+0.1);
    cr->line_to(width, -ymin / (ymax - ymin) * 0.8 + 0.1);
    cr->stroke();
  }

  //draw curve
  if(!samples.empty()){
    double max_time = samples[samples.size() - 1].time;
    double y_start = samples[samples.size()-1].value;
    cr->move_to(width, (ymax-y_start)/ (ymax-ymin) * 0.8 + 0.1);
    for(int i = samples.size()-2; i >= 0; i--){
      cr->line_to(width*(1-(max_time-samples[i].time)/xrange),
                  ( (ymax - samples[i].value)/ (ymax - ymin) ) * 0.8 + 0.1);
    }
    cr->stroke();
  }

  return false;
}
