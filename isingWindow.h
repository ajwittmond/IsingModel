#pragma once

#include <gtkmm.h>
#include <sigc++/sigc++.h>
#include "model.h"
#include "ticker.h"
#include "binding.h"



//This is the top level class for the view
class IsingWindow : public sigc::trackable{
 public:
  IsingWindow() = default;
  virtual ~IsingWindow() = default;

  void from_file() throw();

  Gtk::Window& getWindow();

 protected:
  std::shared_ptr<IsingModel> model;
  std::shared_ptr<Ticker> magnetismTicker;
  std::shared_ptr<Ticker> varianceTicker;
  Gtk::Window* window;
  sigc::connection timout;
  std::shared_ptr<Binding<double>> step_frequency;

  bool step();

private:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::ToggleButton *running;

};
