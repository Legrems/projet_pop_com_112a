#include "simulation.h"

#define ERROR_MODE_KEYWORD "Error"

using namespace std;

int main(int argc, char * argv[]){

    Simulation simu;
    // Not enough arguments
    if (argc != 3) {
        simu.error(LECTURE_ARG);
    }

    // Not in error mode
    if (argv[1] == ERROR_MODE_KEYWORD) {
        simu.error(ERROR_NONE);  
    }

    simu.load_from_file(argv[2]);

    simu.check_errors();

    // simu.print_players();
    // simu.print_balls();
    // simu.print_obstacles();

    // In error mode, with exactly 3 arguments, its ok
    // So we read the file
    
    cout << FILE_READING_SUCCESS;

	return 0;
}