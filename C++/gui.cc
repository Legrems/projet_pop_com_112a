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

    //cout << Players << endl;
    
    //Point c(200, 200);
    
    //Ball b(c, 0.0, 6);
    
    //Point c1(300, 300);
    //Point c2(300, 200);
    //Point c3(300, 100);
    //Point c4(300, 0);
    
    //Player p1(c1, 1, 4, 6);
    //Player p2(c2, 2, 12, 6);
    //Player p3(c3, 3, 20, 6);
    //Player p4(c4, 4, 17, 6);

    
    //Obstacle o(2, 3, 6);
    
    //draw_ball(cr, b);
    //draw_player(cr, p1);
    //draw_player(cr, p2);
    //draw_player(cr, p3);
    //draw_player(cr, p4);
    //draw_obstacle(cr, o);
    
    //ajouter un cadre noir la fin (à faire ce weekend)
}

void MyArea::draw_ball(const RefPtr<Context>& cr, Ball b){

    Point c = b.c_dessin();
    double x = c.x();
    double y = c.y();
    double cell = SIDE/b.nbCells();
    cr->save();
    cr->arc(x, y, COEF_RAYON_BALLE * cell, 0, 2 * M_PI);
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->fill_preserve();
    cr->stroke();
}

void MyArea::draw_player(const RefPtr<Context>& cr, Player p){
    
    
    double cell = SIDE / p.nbCells();
    double fr_count = p.count() / MAX_COUNT;
    Point c = p.c_dessin();
    double x = c.x();
    double y = c.y();
    
    //Attention, changer les couleurs
    double red[5]{0, 0.8, 0.8, 0.4, 0.0};
    double green[5]{0, 0.0, 0.4, 0.4, 0.8};
    double blue[5]{0, 0.0, 0.0, 0.0, 0.0};
    
    double a_0 = 3 * M_PI / 2; //ajouter commentaire "qu'est-ce que c'est"
    double a_1 = a_0 + fr_count * M_PI * 2;
    
    cr->save();
    cr->arc(x, y, COEF_RAYON_JOUEUR * cell, a_0, a_1);
    cr->line_to(x, y);
    cr->close_path();
    cr->set_source_rgb(0.0, 0.0, 0.8);
    cr->fill_preserve();
    cr->stroke();
    cr->save();
    
    a_0 = a_1;
    a_1 = 7 * M_PI / 2;
    cr->arc(x, y, COEF_RAYON_JOUEUR*cell, a_0, a_1);
    cr->line_to(x, y);
    cr->close_path();
    cr->set_source_rgb(red[p.nbT()], green[p.nbT()], blue[p.nbT()]);
    cr->fill_preserve();
    cr->stroke();
    
    cr->save();
    
    //Attention, coef rayon = magic number (à modifier)
    cr->arc(x, y, 0.6 * COEF_RAYON_JOUEUR * cell, 0, 2 * M_PI); 
    cr->fill_preserve();
    cr->stroke();
}

void MyArea::draw_obstacle(const RefPtr<Context>& cr, Obstacle o){
    
    double cell = SIDE/o.nbCells();
    Point c1 = o.coin_sup();
    Point c2(c1.x(), c1.y() + cell);
    Point c3(c1.x() + cell, c1.y() + cell);
    Point c4(c1.x() + cell, c1.y());

    cr->save();
    cr->move_to(c1.x(), c1.y());
    cr->line_to(c2.x(), c2.y());
    cr->line_to(c3.x(), c3.y());
    cr->line_to(c4.x(), c4.y());
    cr->close_path();
    cr->set_source_rgb(0.8, 0.0, 0.8);
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
