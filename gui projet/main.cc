#include "gui.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int Ball::nbCells;
int::Obstacle::nbCells;
int::Player::nbCells;



int main(int argc, char** argv)
{
	Ball::nbCells = 10;
	Obstacle::nbCells =10;
	Player::nbCells = 10;

   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   MyEvent eventWindow;
   eventWindow.set_default_size(500, 200);
   eventWindow.set_resizable(false);

   return app->run(eventWindow);
}
