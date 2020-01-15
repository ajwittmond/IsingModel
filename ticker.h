#include <sigc++/sigc++.h>


class Ticker : public sigc::trackable{
private:
  double previous;
public:
  Ticker(double initial);
};
