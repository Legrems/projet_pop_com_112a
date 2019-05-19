#include <iostream>
#include "gui.h"
#include <cairomm/context.h>

#define LABEL_NO_GAME_TO_RUN "No game to run"
#define LABEL_GAME_READY_TO_RUN "Game ready to run"
#define LABEL_GAME_S_OVER "Game's over !"
#define LABEL_CANNOT_COMPLETE_THE_GAME "Cannot complete the game !"

using namespace std;
using namespace Gtk;

void MyArea::refresh(){
    auto win = get_window();
    if (win){
        Gdk::Rectangle r(0, 0,
                get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_line_width(1.0);

    vector<Rectangle> all_rectangle = simulation.get_rectangle_to_draw();
    vector<Rond> all_rond = simulation.get_rond_to_draw();

    for (uint i = 0; i < all_rectangle.size(); ++i){
        draw(cr, all_rectangle[i]);
    }

    for (uint i = 0; i < all_rond.size(); ++i){
        draw(cr, all_rond[i]);
    }
    
    return true;
}


void MyArea::draw(const Cairo::RefPtr<Cairo::Context>& cr, Rond r){

    Point c = r.centre();
    double x = c.x() + DIM_MAX, y = c.y() + DIM_MAX;
    double blue_r(0.0), blue_g(0.0), blue_b(0.8);
    
    Couleur co = r.couleur();
    double red = co.red(), green = co.green(), blue = co.blue();
    
    double fraction = r.fraction();
    double a_0 = 3 * M_PI / 2, a_1;
    
    cr->save();
    cr->arc(x, y, r.rayon(), 0, 2 * M_PI);
    cr->set_source_rgb(red, green, blue);
    cr->fill_preserve();
    cr->stroke();
    
    if (fraction != 0) {
        a_1 = a_0 + 2 * fraction * M_PI;
        cr->save();
        cr->arc(x, y, r.rayon(), a_0, a_1);
        cr->line_to(x,y);
        cr->set_source_rgb(blue_r, blue_g, blue_b);
        cr->fill_preserve();
        cr->stroke();
    }
    cr->save();
    cr->arc(x, y, r.rayon() * COEF_RAYON_INT, 0, 2 * M_PI);
    cr->set_source_rgb(red, green, blue);
    cr->fill_preserve();
    cr->stroke();
}

void MyArea::draw(const Cairo::RefPtr<Cairo::Context>& cr, Rectangle r){

    Point c = r.c1();
    double x = c.x(), y = c.y();
    
    double largeur = r.largeur(), hauteur = r.hauteur();
    
    Couleur co = r.couleur();
    double red = co.red(), green = co.green(), blue = co.blue();
    
    
    cr->save();
    cr->rectangle(x, y, largeur, hauteur);
    cr->set_source_rgb(red, green, blue);
    cr->fill_preserve();
    cr->stroke();
}

    

//--------------------------------------

MyEvent::MyEvent() :

	timeout_value(DELTA_T*1000), 
	disconnect(false),
	
	
	
//Attention, marge = magic number
    m_Box(ORIENTATION_VERTICAL, 10),
    m_Box_Top(ORIENTATION_HORIZONTAL, 10),

    m_Label_Top(LABEL_NO_GAME_TO_RUN),
    m_Button_Exit("Exit"),
    m_Button_Open("Open"),
    m_Button_Save("Save"),
    m_Button_Start_Stop("Start"),
    m_Button_Step("Step")
    
    
{
  
    set_title("Dodgeball");
    set_border_width(0);


    add(m_Box);

    m_Box.pack_start(m_Box_Top);

    m_Box_Top.pack_start(m_Button_Exit);
    m_Box_Top.pack_start(m_Button_Open);
    m_Box_Top.pack_start(m_Button_Save);
    m_Box_Top.pack_start(m_Button_Start_Stop);
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
    m_Button_Start_Stop.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Start_Stop) );
    m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Step) );
}

MyEvent::~MyEvent()
{
}

bool MyEvent::load_from_file(char * filename){
    return m_Area.simulation.load_from_file(filename);
}

void MyEvent::on_button_clicked_Exit(){
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
            //Notice that this is a std::string, not a Glib::ustring.
            string filename = dialog.get_filename();
 
            m_Area.simulation.backup_members();
            m_Area.simulation.destroy_current_members();
            if (m_Area.simulation.load_from_file((char *)(filename.c_str()))){

                bool is_error = m_Area.simulation.check_errors(true);
                // cout << is_error << endl;
                if (!is_error) {
					m_Area.simulation.reset();
                    // Pas d'erreur, good -> on affiche

                } else {
                    m_Area.simulation.restore_old_members();
                    // On restore les anciens membres
                }
                
                set_label_top(1);

                m_Area.refresh();

            }

            break;
        }
        case(RESPONSE_CANCEL):{
            break;
        }
        default:{
            cout << "Unexpected button clicked." << endl;
            break;
        }
    }
}

void MyEvent::on_button_clicked_Save(){
    FileChooserDialog dialog("Please choose a file to save", FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", RESPONSE_CANCEL);
    dialog.add_button("_Save", RESPONSE_OK);

    int result = dialog.run();

    switch(result){
        case(RESPONSE_OK):{
           
            string filename = dialog.get_filename();

            m_Area.simulation.write_members_to_file((char *)(filename.c_str()));
            break;
        }
        case(RESPONSE_CANCEL):{
            break;
        }
        default:{
            cout << "Unexpected button clicked." << endl;
            break;
        }
    }
}

void MyEvent::on_button_clicked_Start_Stop(){
    if (m_Button_Start_Stop.get_label() == "Start"){
        m_Button_Start_Stop.set_label("Stop");
        Glib::signal_timeout().connect( sigc::mem_fun(*this, 
									   &MyEvent::on_timeout),
									   timeout_value );
    } 

    else {
        m_Button_Start_Stop.set_label("Start");
        disconnect  = true;
    }
}

void MyEvent::on_button_clicked_Step(){
    m_Area.simulation.run();
    set_etat_jeu();
	set_label_top(etat_jeu);
    m_Area.refresh();
    
}

bool MyEvent::on_timeout()
{

	if(disconnect)
	{
		disconnect = false; // reset for next time a Timer is created
	  
		return false; // End of Timer 
	}
  
	m_Area.simulation.run();
	set_etat_jeu();
	set_label_top(etat_jeu);
	m_Area.refresh();
	

	return true; // keep the Timer working
}

void MyEvent::set_label_top(int etat)
{
	// cout << etat << endl;
	
	if(etat == 0)
	{ 
		m_Label_Top.set_label(LABEL_NO_GAME_TO_RUN);
	}
	if(etat == 1)
	{
		m_Label_Top.set_label(LABEL_GAME_READY_TO_RUN);
	}
	if(etat == 2)
	{
		m_Label_Top.set_label(LABEL_GAME_S_OVER);
	}
	if(etat == 3)
	{	
		m_Label_Top.set_label(LABEL_CANNOT_COMPLETE_THE_GAME);
	}	
	}


void MyEvent::set_etat_jeu()
{
	if(m_Area.simulation.gamesover())
	{
		etat_jeu = 2 ;
		return;
	}
	
	if(m_Area.simulation.blocked())
	{
		etat_jeu = 3;
		return;
	}
	
	if (m_Area.simulation.ready_to_run())
	{
		etat_jeu = 1;
		return;
	}
	
	else
	{
		etat_jeu = 0;
		return;
	}
}


bool MyEvent::check_errors(bool start_game)
{
	return m_Area.simulation.check_errors(start_game);
}
	
void MyEvent::set_etat_jeu(int i){etat_jeu = i;}
int MyEvent::get_etat_jeu(){return etat_jeu;}
