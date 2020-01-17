#include "isingWindow.h"
#include <cmath>
#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

void IsingWindow::from_file() throw(Glib::Exception){
  builder = Gtk::Builder::create();
  builder->add_from_file("Ising.glade");
  Gtk::DrawingArea *area;
  builder->get_widget("isingArea",area);
  model =
    std::make_unique<IsingModel>(
                                 new IsingModel(area,
                                                rectangular_grid(100,100,10,2),
                                                1,1,1
                                                )
                                 );
  builder->get_widget("magnetismArea", area);
  magnetismTicker = std::make_unique<Ticker>(new Ticker(area));
  builder->get_widget("varianceArea",area);
  varianceTicker = std::make_unique<Ticker>(new Ticker(area));
  builder->get_widget("window", this->window);
  timout = Glib::signal_timeout().connect(sigc::mem_fun(*this,&IsingWindow::step), 16);
}

Gtk::Window& IsingWindow::getWindow(){
  return *window;
}

bool IsingWindow::step() {
  //time keeping logic
  static std::vector<double> samples(128);
  static auto prev_time = std::chrono::system_clock::now();
  static auto curr_time = std::chrono::system_clock::now();
  static bool first = true;
  static double timer  = 0;
  const int INTERVAL = 1;
  double dt = 0;
  if (first){
    first = false;
  }else{
    curr_time = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(curr_time - prev_time).count();
    samples.push_back(dt);
    timer += dt;
    //print estimates of the mean and standard deviations of the samples
    if(timer >= (double)INTERVAL){
      timer = 0;
      double mean=0,variance =0;
      for(double x: samples){
        mean+= x;
      }
      mean /= samples.size();
      // n-1 estimator is the unbiased variance estimator
      for(double x: samples){
        variance += pow(mean - x,2);
      }
      variance/= samples.size()-1;
      std::cout << "for the last " << INTERVAL << " second(s)..." << std::endl;
      std::cout << "mean time: " << mean << std::endl;
      std::cout << "standard deviation: " << sqrt(variance) << std::endl;
      samples.clear();
    }
    prev_time = curr_time;
  }
  //TODO: Update logic

  static double step_timer = 0;
  step_timer+=dt;
  if(step_timer> step_frequency){
    step_timer-= step_frequency;
    model->step();
    model->invalidate_rect();
    magnetismTicker->invalidate_rect();
    varianceTicker->invalidate_rect();
  }
  return true;
}
