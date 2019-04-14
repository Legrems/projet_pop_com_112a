#include "simulation.h"
#include "gui.h"

#define ERROR_MODE_KEYWORD "Error"

using namespace std;
using namespace Gtk;


int main(int argc, char * argv[]){

    if (argc == 1 or argc == 2){
    	auto app = Application::create();

    	MyEvent eventWindow;
    	eventWindow.set_default_size(500, 200);
    	eventWindow.set_resizable(false);

    	if (argc == 2){
    		eventWindow.load_from_file(argv[1]);
    	}

    	return app->run(eventWindow);
    }

    else if (argc == 3 and argv[1] == string(ERROR_MODE_KEYWORD)){
        Simulation simulation;

        if (simulation.load_from_file(argv[2])){
            simulation.check_errors(true);
        }
    }

	return 0;
}
