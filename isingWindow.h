#include <gtkmm.h>
#include <sigc++/sigc++.h>
#include "model.h"
#include "ticker.h"

//This is the top level class for the view
class IsingWindow : public sigc::trackable{
 public:
  IsingWindow() = default;
  virtual ~IsingWindow() = default;

  void from_file() throw(Glib::Exception);

  Gtk::Window& getWindow();

 protected:
  std::unique_ptr<IsingModel> model;
  std::unique_ptr<Ticker> magnetismTicker;
  std::unique_ptr<Ticker> varianceTicker;
  Gtk::Window* window;
  sigc::connection timout;
  double step_frequency = 1/10;

  bool step();

private:
  Glib::RefPtr<Gtk::Builder> builder;


};
