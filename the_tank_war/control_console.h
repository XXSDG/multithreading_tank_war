#ifndef CONTROL_CONSOLE_H
#define CONTROL_CONSOLE_H
#include "gameobject.h"
#include <vector>
#include "mainwindow.h"
#include <chrono>
#include <random>
#include <list>
#include <thread>

constexpr const int map_width_start = 0;
constexpr const int map_width_end = 1200;
constexpr const int map_height_start = 0;
constexpr const int map_height_end = 750;
constexpr const int tank_speed = 10;
constexpr const int bullet_speed = 15;
constexpr const int wall2_num = 4;
constexpr const int initial_wall2_positon = 150;
constexpr const int initial_wall2_width = 40;
constexpr const int initial_wall2_height = 300;
constexpr const int wall1_num = 2;
constexpr const int initial_wall1_positon = 500;
constexpr const int initial_wall1_width = 800;
constexpr const int initial_wall1_height = 30;
constexpr const int interval = 300;
constexpr const int enemy_tank_num = 3;
constexpr const int enemy_tank_position = 300;
constexpr const int enemy_tank_width = 50;
constexpr const int enemy_tank_height = 50;
constexpr const Gameobject::Direction enemy_tank_dirextion = Gameobject::Direction::down;
constexpr const int my_tank_position = 600;
constexpr const int my_tank_width = 50;
constexpr const int my_tank_height = 50;
constexpr const Gameobject::Direction my_tank_direction = Gameobject::Direction::up;
constexpr const int bullet_width = 15;
constexpr const int bullet_height = 15;
extern std::list<Gameobject> bullet_list;
extern std::vector<Gameobject> map;
extern std::list<Gameobject> enemy_tank;
extern Gameobject my_tank;
extern std::default_random_engine engine;
extern Gameobject boom;


void initialized();
void show_boom();
void control_operate(int *count);
void create_bullet_list(Gameobject objeoct);
void bullet_move();
bool limit_crash(Gameobject object,int direction);
void my_tank_move(moodycamel::ConcurrentQueue<int> *key_communication);
void enemy_tank_move(Gameobject *enemy_tank,bool flag);








#endif // CONTROL_CONSOLE_H
