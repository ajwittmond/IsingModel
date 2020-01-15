#include <gtkmm.h>
#include "isingWindow.h"
#include <iostream>

int main(int argc,char **argv){
   auto app =
     Gtk::Application::create(argc, argv, "ising.model");

   IsingWindow ising;
   try {
     ising.from_file();
   } catch (Glib::Error e) {
     std::cerr << "failed to load glade file";
   }

   return app->run(ising.getWindow());
}
