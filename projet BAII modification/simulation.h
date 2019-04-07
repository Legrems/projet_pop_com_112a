#ifndef SIMULATION_H
#define SIMULATION_H

#include "tools.h"
#include "player.h"
#include "obstacle.h"
#include "ball.h"
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
        char * ERROR_MODE_KEYWORD = (char*)("Error");
        bool load_from_file(char * filepath);
        bool check_errors(bool start_game);
        void error(Error code);
        void decodage_ligne(std::string line);
        void print_players();
        void print_balls();
        void print_obstacles();

        bool check_player_collision(double marge);
        bool check_ball_collision(double marge);
        bool check_obstacle_collision(double marge);

        bool detect_if_outside(std::vector<Player> p);
        bool detect_if_outside(std::vector<Ball> b);
        bool detect_if_outside(std::vector<Obstacle> o);
};

#endif
