#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include "tools.h"
#include "simulation.h"


class MyArea : public Gtk::DrawingArea
{
public:
  
  Simulation simulation;

  void draw(const Cairo::RefPtr<Cairo::Context>& cr,Rond r);
  void draw(const Cairo::RefPtr<Cairo::Context>& cr,Rectangle r);
  void refresh();


protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};


class MyEvent : public Gtk::Window
{
public:
    MyEvent();
    virtual ~MyEvent();
    bool load_from_file(char * filename);

protected:

	//début test timer  
        
	// This is the standard prototype of the Timer callback function
	bool on_timeout(); 
		

	// This constant is initialized in the constructor's member initializer:
	const int timeout_value;
	
	// to store a timer disconnect request
	bool disconnect;
        
        
//fin test timer

    void on_button_clicked_Exit();
    void on_button_clicked_Open();
    void on_button_clicked_Save();
    void on_button_clicked_Start_Stop();
    void on_button_clicked_Step();
    
    

    MyArea              m_Area;
    Gtk::Box            m_Box;
    Gtk::Box            m_Box_Top;
    Gtk::Label          m_Label_Top;
    Gtk::Button         m_Button_Exit;
    Gtk::Button         m_Button_Open;
    Gtk::Button         m_Button_Save;
    Gtk::Button         m_Button_Start_Stop;
    Gtk::Button         m_Button_Step;
    
    
  
private:
    void draw();
};

#endif
