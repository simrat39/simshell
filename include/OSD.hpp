#include <gtkmm/label.h>
#include <gtkmm/revealer.h>
#include "gtkmm/progressbar.h"
#include "gtkmm/window.h"
#include "sigc++/connection.h"

class OSD: public Gtk::Window {
public:
  OSD();
  ~OSD() override;

  Gtk::Revealer* revealer;
  Gtk::ProgressBar* progress;

  sigc::connection timeout;
private:
};
