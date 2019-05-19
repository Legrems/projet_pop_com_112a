#include "simulation.h"

// Get the index for the floyd matrice
#define idx(a, b, c, d, n) ( (((a * n + b) * n + c) * n + d) )

using namespace std;


Simulation::Simulation()
    : gamesover_(false), blocked_(false), ready_to_run_(false)
    {

    }

Simulation::~Simulation(){
    delete[] Floyd_Mat;
}

void Simulation::init_Floyd_Mat(){
    // delete[] Floyd_Mat;
    Floyd_Mat = new double[nb_cell * nb_cell * nb_cell * nb_cell];
}


bool Simulation::floyd(){
    const int n = nb_cell;
    const double infinity = n * n;

    for (int i1 = 0; i1 < n; ++i1){
        for (int j1 = 0; j1 < n; ++j1){
            // cell (i1, j1)
            for (int i2 = 0; i2 < n; ++i2){
                for (int j2 = 0; j2 < n; ++j2){
                    // On itere sur chaque cells
                    // On met inf si y'a un obstacle
                    if (has_obstacles_in(i2, j2)) {
                        Floyd_Mat[idx(i1, j1, i2, j2, n)] = infinity;
                    }
                    // On met 0 sur la case elle meme
                    else if (i1 == i2 && j1 == j2){
                        Floyd_Mat[idx(i1, j1, i2, j2, n)] = 0;
                    }
                    // On met 1 sur les cells directement adjacente
                    else if (((i1 == i2) && fabs(j1 - j2) <= 1)
                             or ((j1 == j2) && (fabs(i1 - i2) <= 1))){
                        Floyd_Mat[idx(i1, j1, i2, j2, n)] = 1;
                    }
                    // On traite les cells en diag.
                    else if (fabs(i1 - i2) == 1 && fabs(j1 - j2) == 1){
                        int di = i1 - i2;
                        int dj = j1 - j2;
                        int nb_voisin_obst = 0;
                        nb_voisin_obst += has_obstacles_in(i2 + di, j2);
                        nb_voisin_obst += has_obstacles_in(i2, j2 + dj);

                        switch(nb_voisin_obst){
                            case 0:
                                Floyd_Mat[idx(i1, j1, i2, j2, n)] = 1.41421;
                                break;
                            case 1:
                                Floyd_Mat[idx(i1, j1, i2, j2, n)] = 2;
                                break;
                            default:
                                Floyd_Mat[idx(i1, j1, i2, j2, n)] = infinity;
                        }
                    }
                    // On met "infinity" sur le reste
                    else {
                        Floyd_Mat[idx(i1, j1, i2, j2, n)] = infinity;
                    }
                }
            }
        }
    }
    // -- calcul phase
    for (int k1 = 0; k1 < n; ++k1){
        for (int k2 = 0; k2 < n; ++k2){
            // cell (k1, k2)
            for (int i1 = 0; i1 < n; ++i1){
                for (int i2 = 0; i2 < n; ++i2){
                    // cell(i1, i2)
                    for (int j1 = 0; j1 < n; ++j1){
                        for (int j2 = 0; j2 < n; ++j2){
                            double m = fmin(Floyd_Mat[idx(i1, i2, j1, j2, n)],
                                          Floyd_Mat[idx(i1, i2, k1, k2, n)] +
                                          Floyd_Mat[idx(k1, k2, j1, j2, n)]); 
                            Floyd_Mat[idx(i1, i2, j1, j2, n)] = m;
                        }
                    }
                }
            }
        }
    }
    // cout << "calculated" << endl;
   
    return true;
}

void Simulation::show_floyd_matrice_for(int k, int v){
    for (int i = 0; i < nb_cell; ++i){
        for (int j = 0; j < nb_cell; ++j){
            cout << Floyd_Mat[idx(k, v, i, j, nb_cell)] << "\t";
        }
        cout << endl;
    }
}

// Check if simulation has obstacles in pos (k, v)
bool Simulation::has_obstacles_in(int k, int v){
    for (uint i = 0; i < Obstacles.size(); ++i) {
        if (v == Obstacles[i].ligne() && k == Obstacles[i].colonne()){
            return true;
        }
    }
    return false;
}

// load simulation state from a file
bool Simulation::load_from_file(char * filepath) {
    string line;
    ifstream file(filepath); 
    int nb_ligne = 0;
    if (!file.fail()) {
        while (getline(file >> ws,line)) {
            // comment line, ignore it
            if (line[0] == '#') {
                continue; 
            }
            decodage_ligne(line, nb_ligne);
            nb_ligne++;
        }
    } else {
        error(READ_OPEN);
        return false;
    }
    init_Floyd_Mat();
    floyd();
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

void Simulation::decodage_ligne(string line, int nb_ligne)
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
    if (nb_ligne == 0){
        etat = NBCELL;
    }
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
        double new_x = (x + DIM_MAX) * nb_cell / SIDE;
        double new_y = (DIM_MAX - y) * nb_cell / SIDE;
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

// Run some check about the collision, && the range of the positions
bool Simulation::check_errors(bool start_game) {

    double marge = (COEF_MARGE_JEU);

    if (start_game) marge *= 2;

    if (check_ball_collision(marge)) return true;
    if (check_player_collision(marge)) return true;
    if (check_obstacle_collision(marge)) return true;

    if (detect_if_outside(Players)) return true;
    if (detect_if_outside(Balls)) return true;
    if (detect_if_outside(Obstacles)) return true;

    cout << FILE_READING_SUCCESS << endl;

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




bool Simulation::write_members_to_file(char * filepath){
    fstream file_out;

    file_out.open(filepath, fstream::out);

    if (file_out){
        file_out << "# NBCELL" << endl;
        file_out << nb_cell << endl;

        file_out << endl << "# Players" << endl;
        file_out << Players.size() << endl;

        for (uint i = 0; i < Players.size(); ++i) {
            file_out << setprecision(10) << Players[i].c_dessin().x()  <<  " "
                     << -Players[i].c_dessin().y() << " "
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
                     << -Balls[i].c_dessin().y() << " "
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
    nb_cell = 0;
    return true;
}

bool Simulation::destroy_old_members(){
    // Delete old members
    old_Players.clear();
    old_Balls.clear();
    old_Obstacles.clear();
    old_nb_cell = 0;
    return true;
}

bool Simulation::backup_members(){
    // Delete old members, && put the actual in the old ones
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

    old_nb_cell = nb_cell;

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

    nb_cell = old_nb_cell;

    return true;
}

void Simulation::move_players()
{
    for (uint i = 0; i < Players.size(); i++)
    {
        int target = Players[i].target(Players);
        move_player(i, target);
    }
}

void Simulation::move_player(int index, int target){
    Point vec = get_dir_vector(index, target);
    
    Players[index].move(vec);
}

// Return the cell index to the direction from starting to ending
Point Simulation::get_dir_vector(int index, int target){
    Point starting = Players[index].centre();
    Point ending = Players[target].centre();  

    if (ecart(starting, ending) <= 2 * COEF_RAYON_JOUEUR + COEF_MARGE_JEU){
        return Point(0, 0);
    }

    if (visible(Players[index], Players[target])) {
        double delta_x = Players[target].centre().x() - Players[index].centre().x();
        double delta_y = Players[target].centre().y() - Players[index].centre().y();

        double length = sqrt(delta_x * delta_x + delta_y * delta_y);

        double cell = SIDE / nb_cell;

        double move_x = delta_x * COEF_VITESSE_JOUEUR * cell * DELTA_T / length;
        double move_y = delta_y * COEF_VITESSE_JOUEUR * cell * DELTA_T / length;

        Point vector(move_x, - move_y);

        return vector;
    }

    int p1x = floor(starting.x());
    int p1y = floor(starting.y());
    int p2x = floor(ending.x());
    int p2y = floor(ending.y());

    double minimum = nb_cell * nb_cell;
    double move_x;
    double move_y;

    for(int i = 0; i < 3; ++i){
        if (p1x - 1 + i >= nb_cell) {continue;}
        if (p1x - 1 + i < 0) {continue;}
        for(int j = 0; j < 3; ++j){
            if (p1y - 1 + j >= nb_cell) {continue;}
            if (p1y - 1 + j < 0) {continue;}
            int id = idx(p2x, p2y, p1x - 1 + i, p1y - 1 + j, nb_cell);
            if (Floyd_Mat[id] < minimum){
                if (i != 1 && j != 1){
                    // Check si la somme des voisins vaut plus que nb_cell^2
                    // => on va pas tangent
                    float s = Floyd_Mat[idx(p2x, p2y, p1x - 1 + i, p1y - 1 + j, nb_cell)] +
                              Floyd_Mat[idx(p2x, p2y, p1x - 1 + i, p1y, nb_cell)] + 
                              Floyd_Mat[idx(p2x, p2y, p1x, p1y - 1 + j, nb_cell)];
                    if (s < nb_cell * nb_cell){
                        minimum = Floyd_Mat[id];
                        move_x = i - 1;
                        move_y = j - 1;
                    }
                } else {
                    minimum = Floyd_Mat[id];
                    move_x = i - 1;
                    move_y = j - 1;
                }
            }
        }
    }
    // minimum > nb_cell^2 => Pas de chemin
    if (minimum != nb_cell * nb_cell){

        double cell = SIDE / nb_cell;

        double length = sqrt((move_x * move_x) + (move_y * move_y));

        if (length == 0){
            length = 1;
        }

        double aim_x = p1x + move_x + 0.5; // 0.5 => centre d'une cell
        double aim_y = p1y + move_y + 0.5;

        aim_x = aim_x - starting.x();
        aim_y = aim_y - starting.y();

        length = sqrt(aim_x * aim_x + aim_y * aim_y);

        aim_x = aim_x * COEF_VITESSE_JOUEUR * cell * DELTA_T / length;
        aim_y = aim_y * COEF_VITESSE_JOUEUR * cell * DELTA_T / length;

        return Point(aim_x, - aim_y);
    } else {
        blocked_ = true;
        return Point(0, 0);
    }
}

void Simulation::shot_player()
{
    for (uint i(0); i < Players.size(); i++)
    {
        int target = Players[i].target(Players);
        
        if (Players[i].contact_shot(Players[target]))
        {
            if (Players[i].count() >= MAX_COUNT)
            {
                lose_life(Players[target],target);
                Players[i].count(0);
            }
        }
        else 
        {
            if (visible(Players[i],Players[target]))
            {
                if ( Players[i].count() >= MAX_COUNT)
                {
                    Players[i].shot(Players[target],Balls);
                    Players[i].count(0);
                }
            }
        }
        
        Players[i].add_count();
        if(Players[i].count() > MAX_COUNT)
        {
            Players[i].count(MAX_COUNT);
        }
    }
    
}
    
 
bool Simulation::visible(Player p1, Player p2)
{
    Point c1 ((p1.c_dessin().x()+DIM_MAX),(p1.c_dessin().y()+DIM_MAX));
    Point c2 ((p2.c_dessin().x()+DIM_MAX),(p2.c_dessin().y()+DIM_MAX));
    Rectangle rect(c1, c2, 2 * (COEF_RAYON_JOUEUR + COEF_MARGE_JEU) * SIDE / nb_cell);
    
    
    for (uint i(0); i < Obstacles.size(); i++)
    {
        if (rect.collide_with(Obstacles[i].rectangle_()))
        {
            return false;
        }
    }
    return true;
}


void Simulation::run(){

    if (!gamesover_){

        bool have_to_recalculate = false;
        
        ready_to_run_ = true;

        move_players();
        shot_player();
        move_ball();
        check_collide();
        have_to_recalculate = kill();
        
        if (Players.size() <= 1)
        {
            gamesover_ = true;
        }

        if (have_to_recalculate){
            floyd();
        }   
    }
}


void Simulation::check_collide(){
    
    
    
    for (uint i(0); i < Players.size(); i++)
    {
        if(Players[i].collide_with(Balls))
        {
            lose_life(Players[i],i);
        }
    }
    for (uint i(0); i < Balls.size(); i++)
    {
        
        if ((Balls[i].collide_with(Balls))||
            (Balls[i].collide_with(Players))||
            (Balls[i].collide_with(Obstacles))||
            (Balls[i].centre().x() < 0)||
            (Balls[i].centre().x() >= nb_cell)|| 
            (Balls[i].centre().y() < 0)|| 
            (Balls[i].centre().y() >= nb_cell)) 
        {
            ball_to_delete.push_back(i);
        }
    }
    for (uint i(0); i < Obstacles.size(); i++)
    {
        if (Obstacles[i].collide_with(Balls))
        {
            obstacle_to_delete.push_back(i);
        }
    }
    
}

// Return true if one obstacle (or more) is destroyed
bool Simulation::kill(){
    
    int PTD = player_to_delete.size();
    int BTD = ball_to_delete.size();
    int OTD = obstacle_to_delete.size();
    
    sort(player_to_delete.begin(),player_to_delete.begin() + PTD);
    sort(ball_to_delete.begin(),ball_to_delete.begin() + BTD);
    sort(obstacle_to_delete.begin(),obstacle_to_delete.begin() + OTD);
    
    if (player_to_delete.size()>0){
        for (int i(player_to_delete.size()-1);i >= 0; i--)
        {
            Players.erase(Players.begin()+player_to_delete[i]);
        }
    }
    if(ball_to_delete.size() > 0)
    {
        for (int i(ball_to_delete.size()-1);i >= 0; i--)
        {
            Balls.erase(Balls.begin()+ball_to_delete[i]);
        }
    }
    if(obstacle_to_delete.size() > 0)
    {
        for (int i(obstacle_to_delete.size()-1);i >= 0; i--)
        {
            Obstacles.erase(Obstacles.begin()+obstacle_to_delete[i]);
        }
    } 
    player_to_delete.clear();
    ball_to_delete.clear();
    obstacle_to_delete.clear();

    if (OTD > 0){
        return true;
    }
    return false;  
}

void Simulation::lose_life(Player &p, int i)
{
    int nbT =p.nbT();
    nbT--;
    p.nbT(nbT);
    if (p.nbT() < 1){
        player_to_delete.push_back(i);
    }
    return;
}

void Simulation::move_ball(){
    

    
    for (uint i(0); i < Balls.size(); i++)
    {
        double cell = SIDE / nb_cell;
        double angle = Balls[i].angle();
        
        
        double move_x, move_y;
        
        move_x = cos(angle) * COEF_VITESSE_BALLE * cell * DELTA_T;
        move_y = sin(angle) * COEF_VITESSE_BALLE * cell * DELTA_T;
        
        
        Balls[i].move(move_x,move_y);
    }
}
        
bool Simulation::gamesover(){ return gamesover_;}
bool Simulation::blocked(){ return blocked_;}
bool Simulation::ready_to_run(){return ready_to_run_;}      
        
        
void Simulation::reset()
{
	gamesover_ = false;
	blocked_ = false;
}
	
	
        
