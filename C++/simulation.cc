#include "simulation.h"

using namespace std;

// load simulation state from a file
bool Simulation::load_from_file(char * filepath) {
    string line;
    ifstream file(filepath); 
    if (!file.fail()) {
        while (getline(file >> ws,line)) {
			// comment line, ignore it
			if (line[0] == '#') {
                continue; 
            }
            decodage_ligne(line);
        }
	} else {
        error(READ_OPEN);
        return false;
    }
    return true;
}

void Simulation::error(Error code) {
	switch (code) {
	case FILENAME_NONE:
        cout << " filename is none\n"; 
        break;
	case READ_OPEN:
        cout << " failed to open file\n";
        break;
	case UNKNOWN_FORMAT:
        cout << " unknown format\n";
        break;
	case LECTURE_ETAT:
        cout << " etat inexistant\n";
        break;
    case MODE_NONE:
        cout << " mode manquant\n";
        break;
    case ERROR_NONE:
        cout << " not in error mode\n";
        break;
    case NBCELL_0:
        cout << " NBCELL is define as 0\n";
        break;
    case NBBALLS_0:
        cout << " NBBALLS is define as 0\n";
        break;
    case NBPLAYERS_0:
        cout << " NBPLAYERS is define as 0\n";
        break;
    case NBOBSTACLE_0:
        cout << " NBOBSTACLE is define as 0\n";
        break;
	default:
        cout << " erreur inconnue\n";
	}
}

void Simulation::decodage_ligne(string line)
{
	istringstream data(line);
	// states of the automate				 
	enum Etat_lecture {NBCELL,      NBPLAYER,
                       PLAYERS,     NBOBSTACLE,
                       OBSTACLES,   NBBALL,
                       BALLS,       FIN};
  
	static int etat(NBCELL); // initial state
	static int i(0), total(0);
    double x(0), y(0), nbt(0), count(0);
    double angle(0);

	switch(etat) 
	{
	case NBCELL: 
		if (!(data >> total)) error(UNKNOWN_FORMAT); 
        else i = 0;
		if (total == 0) error(NBCELL_0);
        else etat = NBPLAYER;
        nb_cell = total; 
	    break;

	case NBPLAYER: 
		if (!(data >> total)) error(UNKNOWN_FORMAT);
        else i = 0;
		if (total == 0) error(NBPLAYERS_0);
        else etat = PLAYERS;
	    break;

	case PLAYERS:{
		if (!(data >> x >> y >> nbt >> count)) error(UNKNOWN_FORMAT); 
        else ++i;
		if (i == total) etat = NBOBSTACLE;
        // Coordonnées en cellule (inversion d'axe Y !)
        double new_x = (x + DIM_MAX) / SIDE * nb_cell;
        double new_y = (DIM_MAX - y) / SIDE * nb_cell;
        Point c(new_x, new_y);
        Player new_player(c, nbt, count, nb_cell);
        Players.push_back(new_player);
	    break;
    }
	case NBOBSTACLE: 
		if (!(data >> total)) error(UNKNOWN_FORMAT);
        else i = 0;
		if (total == 0) etat = NBBALL;
        else etat = OBSTACLES;
	    break;

	case OBSTACLES:{
		if (!(data >> x >> y)) error(UNKNOWN_FORMAT); 
        else ++i;
		if (i == total) etat = NBBALL;
        Obstacle new_obstacle(x, y, nb_cell);
        Obstacles.push_back(new_obstacle);
	    break;
    }
	case NBBALL: 
		if (!(data >> total)) error(UNKNOWN_FORMAT);
        else i = 0;
		if (total == 0) etat = FIN;
        else etat = BALLS;
	    break;
    
    case BALLS:{
		if (!(data >> x >> y >> angle)) error(UNKNOWN_FORMAT);
        else ++i;
		if (i == total)  etat = FIN;
        // Coordonnées en cellule (inversion d'axe Y !)
        double new_x = (x + DIM_MAX) / SIDE * nb_cell;
        double new_y = (DIM_MAX - y) / SIDE * nb_cell;
        Point c(new_x, new_y);
        Ball new_ball(c, angle, nb_cell);
        Balls.push_back(new_ball);
	    break;
    }
	case FIN: break;
	default: error(UNKNOWN_ERROR);
	}	
}

// Just to make sure all is readed correclty
void Simulation::print_players() {
    cout << "List of all players\n";
    for (uint i = 0; i < Players.size(); ++i) {
        cout << "Players[" << i << "], x: "
             << (Players[i].centre().x())
             << ", y: "
             << (Players[i].centre().x()) << endl;
    }
    cout << "List of all old_players\n";
    for (uint i = 0; i < old_Players.size(); ++i) {
        cout << "old_Players[" << i << "], x: "
             << (old_Players[i].centre().x())
             << ", y: "
             << (old_Players[i].centre().x()) << endl;
    }
}

// Just to make sure all is readed correclty
void Simulation::print_balls() {
    cout << "List of all balls\n";
    for (uint i = 0; i < Balls.size(); ++i) {
        cout << "Balls[" << i << "], x: "
             << (Balls[i].centre().x())
             << ", y: "
             << (Balls[i].centre().x()) << endl;
    }
    cout << "List of all old_balls\n";
    for (uint i = 0; i < old_Balls.size(); ++i) {
        cout << "old_Balls[" << i << "], x: "
             << (old_Balls[i].centre().x())
             << ", y: "
             << (old_Balls[i].centre().x()) << endl;
    }
}

// Just to make sure all is readed correclty
void Simulation::print_obstacles() {
    cout << "List of all obstacles\n";
    for (uint i = 0; i < Obstacles.size(); ++i) {
        cout << "Obstacles[" << i << "], line: "
             << (Obstacles[i].ligne())
             << ", row: "
             << (Obstacles[i].colonne()) << endl;
    }
    cout << "List of all old_obstacles\n";
    for (uint i = 0; i < old_Obstacles.size(); ++i) {
        cout << "old_Obstacles[" << i << "], line: "
             << (old_Obstacles[i].ligne())
             << ", row: "
             << (old_Obstacles[i].colonne()) << endl;
    }
}

// Check the players with all object, stop within the first error, if so, return true
bool Simulation::check_player_collision(double marge) {
    for (uint i = 0; i < Players.size(); ++i) {
        for (uint j = 0; j < Players.size(); ++j) {
            if (Players[i].collide_with(Players[j], marge) && i != j) {
                // +1 to avoid beginning @ 0
                cout << PLAYER_COLLISION(i + 1, j + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Balls.size(); ++j) {
            if (Players[i].collide_with(Balls[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << PLAYER_BALL_COLLISION(i + 1, j + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Obstacles.size(); ++j) {
            if (Players[i].collide_with(Obstacles[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << COLL_OBST_PLAYER(j + 1, i + 1) << endl;
                return true;
            }
        }
    }
    return false;
}

// Check the balls with all object, stop within the first error, if so, return true
bool Simulation::check_ball_collision(double marge) {
    for (uint i = 0; i < Balls.size(); ++i) {
        for (uint j = 0; j < Players.size(); ++j) {
            if (Balls[i].collide_with(Players[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << PLAYER_BALL_COLLISION(j + 1, i + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Balls.size(); ++j) {
            if (Balls[i].collide_with(Balls[j], marge) && i != j) {
                // +1 to avoid beginning @ 0
                cout << BALL_COLLISION(i + 1, j + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Obstacles.size(); ++j) {
            if (Balls[i].collide_with(Obstacles[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << COLL_BALL_OBSTACLE(i + 1) << endl;
                return true;
            }
        }
    }
    return false;
}

// Check the obstacles with all object, stop within the first error, if so, return true
bool Simulation::check_obstacle_collision(double marge) {
    for (uint i = 0; i < Obstacles.size(); ++i) {
        for (uint j = 0; j < Players.size(); ++j) {
            if (Obstacles[i].collide_with(Players[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << COLL_OBST_PLAYER(i + 1, j + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Balls.size(); ++j) {
            if (Obstacles[i].collide_with(Balls[j], marge)) {
                // +1 to avoid beginning @ 0
                cout << COLL_BALL_OBSTACLE(j + 1) << endl;
                return true;
            }
        }
        for (uint j = 0; j < Obstacles.size(); ++j) {
            if (Obstacles[i].collide_with(Obstacles[j], marge) && i != j) {
                // Error with line / row of the obstacle
                cout << MULTI_OBSTACLE(Obstacles[i].ligne(),
                                       Obstacles[i].colonne()) << endl;
                return true;
            }
        }
    }
    return false;
}

// Check if ne object of the vector p is outside the field
bool Simulation::detect_if_outside(vector<Player> p) {
    for (uint i = 0; i < p.size(); ++i) {
        // Check the player p[i] if outside the field
        if (p[i].centre().x() < 0 || p[i].centre().x() >= nb_cell
                                  || p[i].centre().y() < 0
                                  || p[i].centre().y() >= nb_cell) {
            // +1 to avoid beginning @ 0
            cout << PLAYER_OUT(i + 1) << endl;
            return true;
        }
    }
    return false;
}

// Check if one object of the vector b is outside the field
bool Simulation::detect_if_outside(vector<Ball> b) {
    for (uint i = 0; i < b.size(); ++i) {
        // Check the ball b[i] if outside the field
        if (b[i].centre().x() < 0 || b[i].centre().x() >= nb_cell
                                  || b[i].centre().y() < 0
                                  || b[i].centre().y() >= nb_cell) {
            // +1 to avoid beginning @ 0
            cout << BALL_OUT(i + 1) << endl;
            return true;
        }
    }
    return false;
}

// Check if one object of the vector o is oustide the field
bool Simulation::detect_if_outside(vector<Obstacle> o) {
    for (uint i = 0; i < o.size(); ++i) {
        // Check if o is outside of the field
        // Returning the ligne or colonne, whoever is outside
        if (o[i].ligne() < 0 || o[i].ligne() >= nb_cell) {
            cout << OBSTACLE_VALUE_INCORRECT(o[i].ligne()) << endl;
            return true;
        }
        if (o[i].colonne() < 0 || o[i].colonne() >= nb_cell) {
            cout << OBSTACLE_VALUE_INCORRECT(o[i].colonne()) << endl;
            return true;
        }
    }
    return false;
}

// Run some check about the collision, and the range of the positions
bool Simulation::check_errors(bool start_game) {

    double marge = (COEF_MARGE_JEU) * (SIDE / nb_cell);

    if (start_game) marge /= 2;

    if (check_ball_collision(marge)) return true;
    if (check_player_collision(marge)) return true;
    if (check_obstacle_collision(marge)) return true;

    if (detect_if_outside(Players)) return true;
    if (detect_if_outside(Balls)) return true;
    if (detect_if_outside(Obstacles)) return true;

    cout << "No error" << endl;
    return false;
}

vector<Rectangle> Simulation::get_rectangle_to_draw(){
    vector<Rectangle> my_rectangles;  
    for (uint i = 0; i < Obstacles.size(); ++i) {
        my_rectangles.push_back(Obstacles[i].rectangle_());
    }

    return my_rectangles;
}

vector<Rond> Simulation::get_rond_to_draw(){
    vector<Rond> my_ronds;
    for (uint i = 0; i < Players.size(); ++i) {
        my_ronds.push_back(Players[i].rond());
    }
    for (uint i = 0; i < Balls.size(); ++i) {
        my_ronds.push_back(Balls[i].rond());
    }

    return my_ronds;
}

bool Simulation::start(){
    cout << "Start" << endl;
    return true;
}

bool Simulation::stop(){
    cout << "Stop" << endl;
    return true;
}

bool Simulation::step(int number_of_step){
    // Step of the simulation

    for (uint i = 0; i < number_of_step; ++i){
        cout << "Step " << i << endl;
    }

    return number_of_step;
}


bool Simulation::write_members_to_file(char * filepath){
    fstream file_out;

    file_out.open(filepath, fstream::out);

    if (file_out){
        file_out << "# NBCELL" << endl;
        file_out << nb_cell << endl;

        file_out << endl << "# Players" << endl;
        file_out << Players.size() << endl;

        for (uint i = 0; i < Players.size(); ++i) {
            file_out << Players[i].c_dessin().x() << " "
                     << Players[i].c_dessin().y() << " "
                     << Players[i].nbT() << " "
                     << Players[i].count() << endl;
        }


        file_out << endl << "# Obstacles" << endl;
        file_out << Obstacles.size() << endl;

        for (uint i = 0; i < Obstacles.size(); ++i) {
            file_out << Obstacles[i].ligne() << " " 
                     << Obstacles[i].colonne() << endl;
        }

        file_out << endl << "# Balls" << endl;
        file_out << Balls.size() << endl;

        for (uint i = 0; i < Balls.size(); ++i) {
            file_out << Balls[i].c_dessin().x() << " " 
                     << Balls[i].c_dessin().y() << " "
                     << Balls[i].angle() << endl;
        }

        file_out.close();
    }

    return true;
}


bool Simulation::destroy_current_members(){
    // Delete actual members

    Players.clear();
    Balls.clear();
    Obstacles.clear();
    return true;
}

bool Simulation::destroy_old_members(){
    // Delete old members
    old_Players.clear();
    old_Balls.clear();
    old_Obstacles.clear();
    return true;
}

bool Simulation::backup_members(){
    // Delete old members, and put the actual in the old ones
    destroy_old_members();

    for (uint i = 0; i < Players.size(); ++i) {
        old_Players.push_back(Players[i]);
    }
    for (uint i = 0; i < Balls.size(); ++i) {
        old_Balls.push_back(Balls[i]);
    }
    for (uint i = 0; i < Obstacles.size(); ++i) {
        old_Obstacles.push_back(Obstacles[i]);
    }

    return true;

}

bool Simulation::restore_old_members(){
    // Delete the actual members with the old one
    destroy_current_members();

    for (uint i = 0; i < old_Players.size(); ++i) {
        Players.push_back(old_Players[i]);
    }
    for (uint i = 0; i < old_Balls.size(); ++i) {
        Balls.push_back(old_Balls[i]);
    }
    for (uint i = 0; i < old_Obstacles.size(); ++i) {
        Obstacles.push_back(old_Obstacles[i]);
    }

    return true;
}