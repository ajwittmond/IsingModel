#include <gtkmm.h>
#include <sigc++/sigc++.h>

//This is the top level class for the view
class IsingWindow : public sigc::trackable{
 public:
  IsingWindow() = default;
  virtual ~IsingWindow() = default;

  void from_file() throw(Glib::Exception);

  Gtk::Window& getWindow();

 protected:
  Gtk::DrawingArea *isingArea;
  Gtk::DrawingArea* magnetismTicker;
  Gtk::DrawingArea* varianceTicker;
  Gtk::Window* window;
  sigc::connection timout;

  bool step();

private:
  Glib::RefPtr<Gtk::Builder> builder;


};
