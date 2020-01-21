#include "isingWindow.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

Glib::ustring f(const double d) { return Glib::ustring(std::to_string(d)); }
double t(Glib::ustring str){return atof(str.c_str());}

sigc::slot<double,Glib::ustring> to = sigc::ptr_fun(t);
sigc::slot<Glib::ustring,const double> from = sigc::ptr_fun(f);


void setBoundary(Glib::PropertyProxy<int> row, std::shared_ptr<IsingModel> model){
  model->set_boundary(static_cast<BoundaryType>((int)row));
}

std::shared_ptr<Binding<double>> fromEntry(double start,Gtk::Entry * entry){
  return to_from_binding<double,Glib::ustring>(start,
                                        entry->property_buffer().get_value()->property_text(),
                                        to,
                                        from );
}

void reset(std::shared_ptr<IsingModel> model){
  for(Node &node: model->graph.nodes){
    node.spin = 1;
  }
}

void changeGrid(std::shared_ptr<IsingModel> model,
                Glib::PropertyProxy<double> w,
                Glib::PropertyProxy<double> h){
  model->graph = rectangular_grid(floor(w.get_value()),
                                  floor(h.get_value()),
                                  10,
                                  2);
}

void IsingWindow::from_file() throw() {
  builder = Gtk::Builder::create();
  builder->add_from_file("Ising.glade");
  Gtk::DrawingArea *area;
  Gtk::Entry *hEntry;
  Gtk::Entry *jEntry;
  Gtk::Entry *tEntry;
  Gtk::Entry *fpsEntry;
  builder->get_widget("isingArea",area);
  builder->get_widget("hEntry",hEntry);
  builder->get_widget("jEntry", jEntry);
  builder->get_widget("tEntry", tEntry);
  builder->get_widget("fpsEntry", fpsEntry);
  const int START_WIDTH=40, START_HEIGHT=40;
  model =
      std::make_shared<IsingModel>(area, rectangular_grid(START_WIDTH, START_HEIGHT, 10, 2),
                                   fromEntry(1, hEntry),
                                   fromEntry(1, jEntry),
                                   fromEntry(1, tEntry)
                                   );
  builder->get_widget("magnetismArea", area);
  magnetismTicker = std::make_shared<Ticker>(area);
  builder->get_widget("varianceArea",area);
  varianceTicker = std::make_shared<Ticker>(area);
  builder->get_widget("window", this->window);
  window->set_events(Gdk::ALL_EVENTS_MASK);
  timout =
      Glib::signal_timeout().connect(sigc::mem_fun(*this, &IsingWindow::step),
                                     16);
  this->step_frequency = fromEntry(10,fpsEntry);
  Gtk::SpinButton * width;
  Gtk::SpinButton * height;
  builder->get_widget("width", width);
  builder->get_widget("height", height);
  width->get_adjustment()->set_upper(100000);
  height->get_adjustment()->set_upper(100000);
  width->set_value(START_WIDTH);
  height->set_value(START_HEIGHT);
  auto changGridF = sigc::bind(&changeGrid,
                               model,
                               width->property_value(),
                               height->property_value());
  width->signal_changed().connect(changGridF);
  height->signal_changed().connect(changGridF);
  builder->get_widget("playButton", running);
  Gtk::ComboBoxText* boundary;
  builder->get_widget("boundaryBox", boundary);
  boundary->property_active().signal_changed().connect(sigc::bind(&setBoundary,
                                                                  boundary->property_active(),
                                                                  model));
  Gtk::Button * button;
  builder->get_widget("resetButton",button);
  button->signal_clicked().connect(sigc::bind(&reset,model));
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

  //time keeping and reporting
  if (first){
    first = false;
  }else{
    curr_time = std::chrono::system_clock::now();
    dt = std::chrono::duration<double>(curr_time - prev_time).count();
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

  if(running->get_active()){
    //update logic
    static double step_timer = 0;
    step_timer+=dt;

    if (step_timer > 1.0 / *step_frequency) {
      step_timer -= 1.0 / *step_frequency;
      model->step();
      model->invalidate_rect();
      magnetismTicker->invalidate_rect();
      varianceTicker->invalidate_rect();
    }
  }
  return true;
}
