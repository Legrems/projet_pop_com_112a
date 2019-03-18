#include "tools.h"
#include "player.h"
#include "obstacle.h"
#include "ball.h"
#include "define.h"
#include "error.h"
#include "enum.h"
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

class Simulation {
    private:
        std::vector<Player> Players;
        std::vector<Ball> Balls;
        std::vector<Obstacle> Obstacles;
        int nb_cell;
    public:
        bool load_from_file(char * filepath);
        void check_errors();
        void error(Error code);
        void decodage_ligne(std::string line);
        void print_players();
        void print_balls();
        void print_obstacles();
};