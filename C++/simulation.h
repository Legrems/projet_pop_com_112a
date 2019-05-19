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
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <cmath>

class Simulation {
    private:
        std::vector<Player> Players;
        std::vector<Ball> Balls;
        std::vector<Obstacle> Obstacles;

        std::vector<Player> old_Players;
        std::vector<Ball> old_Balls;
        std::vector<Obstacle> old_Obstacles;
        
        std::vector<int> player_to_delete;
        std::vector<int> ball_to_delete;
        std::vector<int> obstacle_to_delete;

        int nb_cell;

        int old_nb_cell;
        
        bool gamesover_;
        bool blocked_;
		bool ready_to_run_;

        // float**** Floyd_Mat = new float***[nb_cell];
        
        double* Floyd_Mat;
        // std::vector<std::vector<std::vector<std::vector<float>>>> Floyd_Matrice;
        
        
    public:
    
        Simulation();
        ~Simulation();
		
        char * ERROR_MODE_KEYWORD = (char*)("Error");
        bool load_from_file(char * filepath);
        bool check_errors(bool start_game);
        void error(Error code);
        void decodage_ligne(std::string line, int nb_ligne);
        void print_players();
        void print_balls();
        void print_obstacles();

        bool check_player_collision(double marge);
        bool check_ball_collision(double marge);
        bool check_obstacle_collision(double marge);

        bool detect_if_outside(std::vector<Player> p);
        bool detect_if_outside(std::vector<Ball> b);
        bool detect_if_outside(std::vector<Obstacle> o);

        std::vector<Rectangle> get_rectangle_to_draw();
        std::vector<Rond> get_rond_to_draw();


        bool write_members_to_file(char * filepath);

        bool destroy_current_members();
        bool destroy_old_members();
        bool backup_members();
        bool restore_old_members();

        void run();
        
        void check_collide();
        bool kill();
        
        void move_player(int index, int target);
        void move_players();
        void shot_player();
		void move_ball();
        
        void lose_life(Player &p, int i);
        
        bool visible(Player p1, Player p2);
        
        bool gamesover();
        bool blocked();
        bool ready_to_run();

        bool has_obstacles_in(int k, int v);
        bool floyd();
        void init_Floyd_Mat();

        Point get_dir_vector(Point starting, Point ending);

        void show_floyd_matrice_for(int k, int v);
};

#endif
