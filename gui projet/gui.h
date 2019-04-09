#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include "ball.h"
#include "player.h"
#include "obstacle.h"



class MyArea : public Gtk::DrawingArea
{
public:
  
 
  void draw_ball(const Cairo::RefPtr<Cairo::Context>& cr,Ball b);
  void draw_player(const Cairo::RefPtr<Cairo::Context>& cr,Player p);
  void draw_obstacle(const Cairo::RefPtr<Cairo::Context>& cr,Obstacle o);


protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  

};


class MyEvent : public Gtk::Window
{
public:
  MyEvent();
  virtual ~MyEvent();

protected:
  void on_button_clicked_Exit();
  void on_button_clicked_Open();
  void on_button_clicked_Save();
  void on_button_clicked_Start();
  void on_button_clicked_Step();

  Gtk::Box m_Box, m_Box_Top;
  MyArea              m_Area;
  Gtk::Button 		  m_Button_Exit;
  Gtk::Button 		  m_Button_Open;
  Gtk::Button 		  m_Button_Save;
  Gtk::Button 		  m_Button_Start;
  Gtk::Button 		  m_Button_Step;
  
  Gtk::Label          m_Label_Top;
  
private:
	void draw();
};

#endif GUI_H
