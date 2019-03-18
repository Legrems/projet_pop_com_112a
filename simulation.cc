#include "simulation.h"

#define ERROR_MODE_KEYWORD "Error"

using namespace std;

bool Simulation::load_from_file(char * filepath){
    string line;
    ifstream file(filepath); 
    if (!file.fail()) {
        // l’appel de getline filtre aussi les séparateurs
        while (getline(file >> ws,line)) {
			// ligne de commentaire à ignorer, on passe à la suivante
			if (line[0] == '#') {
                continue; 
            }
            Simulation::decodage_ligne(line);
        }
        // cout << "fin de la lecture" << endl;
	} else {
        error(LECTURE_OUVERTURE);
    }
    return true;
}

void Simulation::error(Error code){
	switch (code) {
	case LECTURE_ARG:
        cout << " nom de fichier manquant\n"; 
        break;
	case LECTURE_OUVERTURE:
        cout << " ouverture impossible\n";
        break;
	case LECTURE_FIN:
        cout << " format non respecté \n";
        break;
	case LECTURE_ETAT:
        cout << " etat inexistant\n";
        break;
    case MODE_ARG:
        cout << " mode manquant\n";
        break;
    case MODE_NONE:
        cout << " mode manquant\n";
        break;
    case ERROR_NONE:
        cout << " not in error mode\n";
        break;
	default:
        cout << " erreur inconnue\n";
	}
    exit(1);
}

void Simulation::decodage_ligne(string line)
{
	istringstream data(line);
  
	// états de l'automate de lecture					 
	enum Etat_lecture {NBCELL,      NBPLAYER,
                       PLAYERS,     NBOBSTACLE,
                       OBSTACLES,   NBBALL,
                       BALLS,       FIN};
  
	static int etat(NBCELL); // état initial
	static int i(0), total(0);
    int x(0), y(0), count(0), touch(0);
    double angle(0);

	switch(etat) 
	{
	case NBCELL: 
		if (!(data >> total)) {
            Simulation::error(UNKNOWN_ERROR); 
        } else {
            i = 0;
        }
		if (total == 0) {
            // 0 NBCELL
            Simulation::error(UNKNOWN_ERROR);
        } else {
            etat = NBPLAYER;
        }
        Simulation::nb_cell = total;
		// cout << "NBCELL: " << total << endl; 
	    break;

	case NBPLAYER: 
		if (!(data >> total)) {
            Simulation::error(UNKNOWN_ERROR);
        } else {
            i = 0;
        }
		if (total == 0) {
            // 0 Joueurs
            Simulation::error(UNKNOWN_ERROR);
        } else {
            etat = PLAYERS;
        }
		// cout << "NBPLAYER " << total << endl;
	    break;

	case PLAYERS:{
		if (!(data >> x >> y >> count >> touch)) {
            Simulation::error(UNKNOWN_ERROR); 
        } else {
            ++i;
        }
		if (i == total) {
            etat = NBOBSTACLE;
        }
        Point c(x, y);
        Player new_player(c, count, touch);
        Simulation::Players.push_back(new_player);
		// cout << "Position of players " << x << " " << y
            //  << " " << count << " " << touch << endl; 
	    break;
    }
	case NBOBSTACLE: 
		if (!(data >> total)) {
            Simulation::error(UNKNOWN_ERROR);
        } else {
            i = 0;
        }
		
		if (total == 0) {
            Simulation::error(UNKNOWN_ERROR);
        } else {
            etat = OBSTACLES;
        }
		// cout << "NBOBSTACLE " << total << endl;
	    break;

	case OBSTACLES:{
		if (!(data >> x >> y)) {
            Simulation::error(UNKNOWN_ERROR); 
        } else {
            ++i;
        }
		
		if (i == total) {
            etat = NBBALL;
        }
        Obstacle new_obstacle(x, y);
        Simulation::Obstacles.push_back(new_obstacle);
		// cout << "OBSTACLES: " << x << " " << y << endl; 
	    break;
    }
	case NBBALL: 
		if (!(data >> total)){
            Simulation::error(UNKNOWN_ERROR);
        } else {
            i = 0;
        }

		if (total == 0) {
            Simulation::error(UNKNOWN_ERROR);
        } else {
            etat = BALLS;
        }
		// cout << "NBBALL " << total << endl; 
	    break;
    
    case BALLS:{
		if (!(data >> x >> y >> angle)){
            Simulation::error(UNKNOWN_ERROR);
        } else {
            ++i;
        }

		if (i == total) {
            etat = FIN;
        }
        Point c(x, y);
        Ball new_ball(c, angle);
        Simulation::Balls.push_back(new_ball);
		// cout << "BALLS " << x << " " << y << " " << angle << endl;
	    break;
    }
	case FIN:
        Simulation::error(UNKNOWN_ERROR) ; 
		break;

	default:
        Simulation::error(UNKNOWN_ERROR);
	}	
}

void Simulation::print_players(){
    cout << "List of all players\n";
    for(uint i = 0; i < Simulation::Players.size(); ++i){
        cout << "Players[" << i << "], x: "
             << (Simulation::Players[i].centre().x())
             << ", y: "
             << (Simulation::Players[i].centre().x()) << endl;
    }
}

void Simulation::print_balls(){
    cout << "List of all balls\n";
    for(uint i = 0; i < Simulation::Balls.size(); ++i){
        cout << "Balls[" << i << "], x: "
             << (Simulation::Balls[i].centre().x())
             << ", y: "
             << (Simulation::Balls[i].centre().x()) << endl;
    }
}

void Simulation::print_obstacles(){
    cout << "List of all obstacles\n";
    for(uint i = 0; i < Simulation::Obstacles.size(); ++i){
        cout << "Obstacles[" << i << "], line: "
             << (Simulation::Obstacles[i].ligne())
             << ", row: "
             << (Simulation::Obstacles[i].colonne()) << endl;
    }
}

void Simulation::check_errors(){
    for(uint i = 0; i < Simulation::Players.size(); ++i){
        for(uint j = 0; j < Simulation::Players.size(); ++j){
            if (1) {
                // cout << PLAYER_COLLISION(Simulation::Players[i],
                //                          Simulation::Players[j]) << endl;
                cout << PLAYER_COLLISION(i, j) << endl;
            }
        }
        for(uint j = 0; j < Simulation::Balls.size(); ++j){
            if (1) {
                // cout << PLAYER_BALL_COLLISION(Simulation::Players[i],
                //                               Simulation::Balls[j]) << endl;
                cout << PLAYER_BALL_COLLISION(i, j) << endl;
            }
        }
        for(uint j = 0; j < Simulation::Obstacles.size(); ++j){
            if (1) {
                // cout << COLL_OBST_PLAYER(Simulation::Players[i],
                //                          Simulation::Obstacles[j]) << endl;
                cout << COLL_OBST_PLAYER(i, j) << endl;
            }
        }
    }
    
    for(uint i = 0; i < Simulation::Balls.size(); ++i){
        for(uint j = 0; j < Simulation::Balls.size(); ++j){
            if (1) {
                // cout << BALL_COLLISION(Simulation::Balls[i],
                //                        Simulation::Balls[j]) << endl;
                cout << BALL_COLLISION(i, j) << endl;
            }
        }
        for(uint j = 0; j < Simulation::Obstacles.size(); ++j){
            if (1) {
                // cout << COLL_BALL_OBSTACLE(Simulation::Balls[i]) << endl;
                cout << COLL_BALL_OBSTACLE(i) << endl;
            }
        }
    }

    for(uint i = 0; i < Simulation::Obstacles.size(); ++i){
        for(uint j = 0; j < Simulation::Obstacles.size(); ++j){
            if (1==1) {
                // cout << MULTI_OBSTACLE(Simulation::Obstacles[i],
                //                        Simulation::Obstacles[j]) << endl;
                cout << MULTI_OBSTACLE(i, j) << endl;
            }
        }
    }
}