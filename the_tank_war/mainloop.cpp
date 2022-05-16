#include "mainloop.h"
#include "gameobject.h"
#include <thread>
#include <chrono>
#include "mainwindow.h"
#include <QDebug>
#include <random>
#include "control_console.h"

void Mainloop(moodycamel::ConcurrentQueue<int> *key_communication, moodycamel::ConcurrentQueue<Gameobject> *icon_communication,
              bool *flag_fight_finsih, bool *flag_loop_finish)
{

    while (true) {
        if(*flag_loop_finish){
            //qDebug()<<"##";
            break;
        }
        initialized();
        int count_FPS = 1;
        while (true) {
            if(*flag_loop_finish){

                break;
            }
            //int length_map = map.size();
            if(enemy_tank.empty() || my_tank.getTeam() == Gameobject::Team::lawless){
                *flag_fight_finsih = true;
                break;
            }
            for(auto temp_map: map){
                icon_communication->enqueue(temp_map);
            }
            if(count_FPS%(FPS/6) == 0 && boom.getTeam() != Gameobject::Team::lawless){
                icon_communication->enqueue(boom);
            }
            control_operate(&count_FPS);
    //        std::thread control(control_operate, &count_FPS);
    //        control.join();
            for(auto temp_bullet: bullet_list){
                icon_communication->enqueue(temp_bullet);
            }
            for(auto &temp_enemy_tank: enemy_tank){
                icon_communication->enqueue(temp_enemy_tank);
            }

            if(my_tank.getTeam() != Gameobject::Team::lawless){
                my_tank_move(key_communication);
                icon_communication->enqueue(my_tank);
            }
            count_FPS++;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(300ms/FPS);
        }

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms/FPS);
    }

}

