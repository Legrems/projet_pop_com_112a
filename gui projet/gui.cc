#include <iostream>
#include "gui.h"
#include <cairomm/context.h>

using namespace std;


bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	cr->set_line_width(1.0);
	
	Point c(200,200);
	
	Ball b(c,0.0,6);
	
	Point c1(300,300);
	Point c2(300,200);
	Point c3(300,0);
	Point c4(300,-200);
	
	Player p1(c1,1,4,6);
	Player p2(c2,2,12,6);
	Player p3(c3,3,20,6);
	Player p4(c4,4,17,6);

	
	Obstacle o(2,3,6);
	
	draw_ball(cr,b);
	draw_player(cr,p1);
	draw_player(cr,p2);
	draw_player(cr,p3);
	draw_player(cr,p4);
	draw_obstacle(cr,o);
	
	//ajouter un cadre noir la fin (à faire ce weekend)
}

void MyArea::draw_ball(const Cairo::RefPtr<Cairo::Context>& cr,Ball b){

	Point c = b.c_dessin();
	double x = c.x();
	double y = c.y();
	double cell = SIDE/b.nbCells();
	cr->save();
	cr->arc(x,y,COEF_RAYON_BALLE*cell,0,2*M_PI);
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->fill_preserve();
	cr->stroke();
}
void MyArea::draw_player(const Cairo::RefPtr<Cairo::Context>& cr,Player p){
	
	
	double cell = SIDE/p.nbCells();
	double fr_count = p.count()/MAX_COUNT;
	Point c = p.c_dessin();
	double x = c.x();
	double y = c.y();
	
	//Attention, changer les couleurs
	double red[5]{0,0.8,0.8,0.4,0.0};
	double green[5]{0,0.0,0.4,0.4,0.8};
	double blue[5]{0,0.0,0.0,0.0,0.0};
	
	double a_0 = 3*M_PI/2; //ajouter commentaire "qu'est-ce que c'est"
	double a_1 = a_0+fr_count*M_PI*2;
	
	cr->save();
	cr->arc(x,y,COEF_RAYON_JOUEUR*cell,a_0,a_1);
	cr->line_to(x,y);
	cr->close_path();
	cr->set_source_rgb(0.0, 0.0, 0.8);
	cr->fill_preserve();
	cr->stroke();
	cr->save();
	
	a_0 = a_1;
	a_1 = 7*M_PI/2;
	cr->arc(x,y,COEF_RAYON_JOUEUR*cell,a_0,a_1);
	cr->line_to(x,y);
	cr->close_path();
	cr->set_source_rgb(red[p.nbT()],green[p.nbT()],blue[p.nbT()]);
	cr->fill_preserve();
	cr->stroke();
	
	cr->save();
	
	//Attention, coef rayon = magic number (à modifier)
	cr->arc(x,y,0.6*COEF_RAYON_JOUEUR*cell,0,2*M_PI); 
	cr->fill_preserve();
	cr->stroke();
}

void MyArea::draw_obstacle(const Cairo::RefPtr<Cairo::Context>& cr,
                           Obstacle o){
	
	double cell = SIDE/o.nbCells();
	Point c1 = o.coin_sup();
	Point c2(c1.x(),c1.y()+cell);
	Point c3(c1.x()+cell,c1.y()+cell);
	Point c4(c1.x()+cell,c1.y());
	
	cr->save();
	cr->move_to(c1.x(),c1.y());
	cr->line_to(c2.x(),c2.y());
	cr->line_to(c3.x(),c3.y());
	cr->line_to(c4.x(),c4.y());
	cr->close_path();
	cr->set_source_rgb(0.8,0.0,0.8);
	cr->fill_preserve();
	cr->stroke();
}
	

//--------------------------------------

MyEvent::MyEvent() :
//Attention, marge = magic number
  m_Box(Gtk::ORIENTATION_VERTICAL,10),
  m_Box_Top(Gtk::ORIENTATION_HORIZONTAL, 10),
  
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
  
  
  m_Area.set_size_request(SIDE,SIDE);
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

void MyEvent::on_button_clicked_Exit()
{
  cout << "Exit"<<endl;
  exit(0);
}
void MyEvent::on_button_clicked_Open()
{
  cout << "Open"<<endl;
}
void MyEvent::on_button_clicked_Save()
{
  cout << "Save"<<endl;
}
void MyEvent::on_button_clicked_Start()
{
  cout << "Start"<<endl;
}
void MyEvent::on_button_clicked_Step()
{
  cout << "Step"<<endl;
  }
