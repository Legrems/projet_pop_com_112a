#include "simulation.h"
#include "gui.h"

#define ERROR_MODE_KEYWORD "Error"
#define STEP_MODE_KEYWORD "Step"


using namespace std;
using namespace Gtk;


int main(int argc, char * argv[]){

    if (argc == 1 or argc == 2){
    	auto app = Application::create();

    	MyEvent eventWindow;
    	
    	eventWindow.set_etat_jeu(0);
    	eventWindow.set_default_size(500, 200);
    	eventWindow.set_resizable(false);

    	if (argc == 2){
    		eventWindow.load_from_file(argv[1]);
    		if (eventWindow.check_errors(true)) 
				{return 0;}
			eventWindow.set_etat_jeu(1);
    	}
    	eventWindow.set_label_top(eventWindow.get_etat_jeu());

    	return app->run(eventWindow);
    }

    else if (argc == 3 and argv[1] == string(ERROR_MODE_KEYWORD)){
        Simulation simulation;

        if (simulation.load_from_file(argv[2])){
            simulation.check_errors(true);
        }
    }
    
    else if (argc == 4 and argv[1] == string(STEP_MODE_KEYWORD)){
		Simulation simulation;
		
		if(simulation.load_from_file(argv[2])){
			if (simulation.check_errors(true)) {return 0;}
			
			else{
				simulation.run();
				simulation.write_members_to_file(argv[3]);
			}
		}
	}			

	return 0;
}
