#include "simulation.h"

using namespace std;


int main(int argc, char * argv[]){

    Simulation simu;

    // Not enough arguments for now (rendu 1)
    if (argc != 3) {
        simu.error(FILENAME_NONE);
    }

    // Not in error mode
    if (argv[1] != string(simu.ERROR_MODE_KEYWORD)) {
        simu.error(ERROR_NONE);  
        return 1;
    }

    simu.load_from_file(argv[2]);

    if (simu.check_errors(true)) {
        return 1;
    }

    // simu.print_players();
    // simu.print_balls();
    // simu.print_obstacles();

    // In error mode, with exactly 3 arguments, its ok
    // So we read the file
    
    cout << FILE_READING_SUCCESS << endl;

	return 0;
}
