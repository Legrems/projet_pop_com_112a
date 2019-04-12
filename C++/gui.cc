#include <iostream>
#include "gui.h"
#include <cairomm/context.h>

using namespace std;
using namespace Gtk;
using namespace Cairo;


bool MyArea::on_draw(const RefPtr<Context>& cr)
{
    cr->set_line_width(1.0);

    vector<Player> Players = simulation.get_players_to_draw();
    vector<Ball> Balls = simulation.get_balls_to_draw();
    vector<Obstacle> Obstacles = simulation.get_obstacles_to_draw();

    for (uint i = 0; i < Players.size(); ++i) {
        draw_player(cr, Players[i]);
    }

    for (uint i = 0; i < Balls.size(); ++i) {
        draw_ball(cr, Balls[i]);
    }

    for (uint i = 0; i < Obstacles.size(); ++i) {
        draw_obstacle(cr, Obstacles[i]);
    }

    simulation.print_players();
    simulation.print_balls();
    simulation.print_obstacles();

   
}

void MyArea::draw(const Cairo::RefPtr<Cairo::Context>& cr,Rond r){

	Point c = r.centre();
	double x = c.x(),y = c.y();
	double blue_r(0.0),blue_g(0.0),blue_b(0.8);
	
	Couleur co = r.couleur();
	double red = co.red(), green = co.green(), blue = co.blue();
	
	double fraction = r.fraction();
	double a_0 = 3*M_PI/2, a_1;
	
	cr->save();
	cr->arc(x,y,r.rayon(),0,2*M_PI);
	cr->set_source_rgb(red, green, blue);
	cr->fill_preserve();
	cr->stroke();
	
	if(fraction != 0)
	{
		a_1 = a_0 + 2*fraction*M_PI;
		cr->save();
		cr->arc(x,y,r.rayon(),a_0,a_1);
		cr->set_source_rgb(blue_r,blue_g,blue_b);
		cr->fill_preserve();
		cr->stroke();
	}
	cr->save();
	cr->arc(x,y,r.rayon()*COEF_RAYON_INT,0,2*M_PI);
	cr->set_source_rgb(red, green, blue);
	cr->fill_preserve();
	cr->stroke();
}

void MyArea::draw(const Cairo::RefPtr<Cairo::Context>& cr,Rectangle r){

	Point c = r.c1();
	double x = c.x(),y = c.y();
	
	double largeur = r.largeur(), hauteur = r.hauteur();
	
	Couleur co = r.couleur();
	double red = co.red(), green = co.green(), blue = co.blue();
	
	
	cr->save();
	cr->rectangle(x,y,largeur,hauteur);
	cr->set_source_rgb(red, green, blue);
	cr->fill_preserve();
	cr->stroke();
}

    

//--------------------------------------

MyEvent::MyEvent() :
//Attention, marge = magic number
    m_Box(ORIENTATION_VERTICAL, 10),
    m_Box_Top(ORIENTATION_HORIZONTAL, 10),

    m_Label_Top("No game to run"),
    m_Button_Exit("Exit"),
    m_Button_Open("Open"),
    m_Button_Save("Save"),
    m_Button_Start("Start"),
    m_Button_Step("Step")
{
  
    set_title("Dodgeball");
    set_border_width(0);


    add(m_Box);

    m_Box.pack_start(m_Box_Top);

    m_Box_Top.pack_start(m_Button_Exit);
    m_Box_Top.pack_start(m_Button_Open);
    m_Box_Top.pack_start(m_Button_Save);
    m_Box_Top.pack_start(m_Button_Start);
    m_Box_Top.pack_start(m_Button_Step);
    m_Box_Top.pack_start(m_Label_Top);


    m_Area.set_size_request(SIDE, SIDE);
    m_Box.pack_start(m_Area);
  
  
    show_all_children();


    m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Exit) );
    m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Open) );
    m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Save) );
    m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Start) );
    m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Step) );
}

MyEvent::~MyEvent()
{
}

void MyEvent::load_from_file(char * filename){
    Simulation simu;
    simu.load_from_file(filename);
}

void MyEvent::on_button_clicked_Exit(){
  cout << "Exit" << endl;
  exit(0);
}

void MyEvent::on_button_clicked_Open(){   
    FileChooserDialog dialog("Please choose a file to open",
                                  FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", RESPONSE_CANCEL);
    dialog.add_button("_Open", RESPONSE_OK);

    int result = dialog.run();

    switch(result){
        case(RESPONSE_OK):{
            cout << "Open clicked." << endl;
            //Notice that this is a std::string, not a Glib::ustring.
            string filename = dialog.get_filename();
            cout << "File selected: " << filename << endl;
            m_Area.simulation.load_from_file((char *)(filename.c_str()));
            if (m_Area.simulation.check_errors(true) == false) {
                show_all_children();
            } else {
                m_Area.simulation.destroy_all_members();
            }
            break;
        }
        case(RESPONSE_CANCEL):{
            cout << "Cancel clicked." << endl;
            break;
        }
        default:{
            cout << "Unexpected button clicked." << endl;
            break;
        }
    }
}

void MyEvent::on_button_clicked_Save(){
    FileChooserDialog dialog("Please choose a file to save",
                                  FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", RESPONSE_CANCEL);
    dialog.add_button("_Save", RESPONSE_OK);

    int result = dialog.run();

    switch(result){
        case(RESPONSE_OK):{
            cout << "Save clicked." << endl;
            //Notice that this is a std::string, not a Glib::ustring.
            string filename = dialog.get_filename();
            cout << "File selected: " << filename << endl;
            break;
        }
        case(RESPONSE_CANCEL):{
            cout << "Cancel clicked." << endl;
            break;
        }
        default:{
            cout << "Unexpected button clicked." << endl;
            break;
        }
    }
}

void MyEvent::on_button_clicked_Start(){
  cout << "Start" << endl;
}

void MyEvent::on_button_clicked_Step(){
  cout << "Step" << endl;
}
