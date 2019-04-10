#include "gui.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>


int main(int argc, char** argv)
{
	

   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   MyEvent eventWindow;
   eventWindow.set_default_size(500, 200);
   eventWindow.set_resizable(false);

   return app->run(eventWindow);
}
