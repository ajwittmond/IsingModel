#include <isingWindow.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>

void IsingWindow::from_file() throw(Glib::Exception){
  builder = Gtk::Builder::create();
  builder->add_from_file("Ising.glade");
  builder->get_widget("isingArea",this->isingArea);
  builder->get_widget("magnetismArea", this->magnetismTicker);
  builder->get_widget("varianceArea",this->varianceTicker);
  builder->get_widget("window", this->window);
  timout = Glib::signal_timeout().connect(sigc::mem_fun(*this,&IsingWindow::step), 16);
}

Gtk::Window& IsingWindow::getWindow(){
  return *window;
}

bool IsingWindow::step() {
  //time keeping logic
  static std::vector<double> samples(128);
  static time_t prev_time = 0;
  static time_t curr_time = 0;
  static double timer  = 0;
  const int INTERVAL = 1;
  if (prev_time == 0){
    time(&prev_time);
  }else{
    time(&curr_time);
    double sample = difftime(curr_time, prev_time);
    samples.push_back(sample);
    timer += sample;
    //print estimates of the mean and standard deviations of the samples
    if(timer >= INTERVAL){
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
      std::cout << "standard deviation: " << variance << std::endl;
      samples.clear();
    }
    prev_time = curr_time;
  }

  //TODO: Update logic
  return true;
}
