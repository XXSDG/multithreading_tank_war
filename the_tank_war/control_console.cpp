#include"control_console.h"
#include <QDebug>


std::list<Gameobject> bullet_list;
std::vector<Gameobject> map;
std::list<Gameobject> enemy_tank;
Gameobject my_tank;
std::default_random_engine engine;
Gameobject boom;

void initialized()
{
    for(int i = 0; i < wall1_num; i++){
        Gameobject wall1(initial_wall1_positon/2,initial_wall1_positon+interval*i/2,Gameobject::Direction::up,initial_wall1_width,
                        initial_wall1_height,Gameobject::Team::wall1_map);
        map.push_back(wall1);
    }
    for(int i = 0; i < wall2_num; i++){
        Gameobject wall2(initial_wall2_positon+interval*i,initial_wall2_positon/3*2,Gameobject::Direction::up,initial_wall2_width,
                        initial_wall2_height,Gameobject::Team::wall2_map);
        map.push_back(wall2);
    }
    for(int i = 0; i < enemy_tank_num; i++){
        Gameobject enemy_tanks(enemy_tank_position+interval*i,enemy_tank_position/5,enemy_tank_dirextion,enemy_tank_width,
                               enemy_tank_height,Gameobject::Team::enemy_tank);
        enemy_tank.push_back(enemy_tanks);
    }
    my_tank.setPosition_x(my_tank_position*3/2);
    my_tank.setPosition_y(my_tank_position);
    my_tank.setDirection(my_tank_direction);
    my_tank.setWidth(my_tank_width);
    my_tank.setHeight(my_tank_height);
    my_tank.setTeam(Gameobject::Team::my_tank);
    boom.setTeam(Gameobject::Team::lawless);
    //Gameobject temp_my_tank(my_tank_position,my_tank_position,my_tank_direction,my_tank_width,my_tank_height,Gameobject::Team::my_tank);
    //my_tank = &temp_my_tank;
    //qDebug() << my_tank->getPosition_x();
}



bool limit_crash(Gameobject object,int direction){
    if(object.getTeam() == Gameobject::Team::enemy_tank){
        if(direction == Qt::Key_Up){
            for(auto temp_map:map){
                if((object.getPosition_y()-tank_speed <= temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth()&&object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() <= map_height_start)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Down){
            for(auto temp_map:map){
                if((object.getPosition_y()+object.getHeight()+tank_speed >= temp_map.getPosition_y() && object.getPosition_y() < temp_map.getPosition_y() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() >= map_height_end)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Left){
            for(auto temp_map:map){
                if((object.getPosition_x()-tank_speed <= temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() <= map_width_start)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Right){
            for(auto temp_map:map){
                if((object.getPosition_x()+object.getWidth()+tank_speed >= temp_map.getPosition_x() && object.getPosition_x() < temp_map.getPosition_x() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() >= map_width_end)){
                    return false;
                }
            }
        }
    }
    else if(object.getTeam() == Gameobject::Team::my_tank){
        if(direction == Qt::Key_Up){
            for(auto temp_map:map){
                if((object.getPosition_y() == temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth()&&object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() <= map_height_start)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Down){
            for(auto temp_map:map){
                if((object.getPosition_y()+object.getHeight() == temp_map.getPosition_y() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() >= map_height_end)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Left){
            for(auto temp_map:map){
                if((object.getPosition_x() == temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() <= map_width_start)){
                    return false;
                }
            }
        }
        else if(direction == Qt::Key_Right){
            for(auto temp_map:map){
                if((object.getPosition_x()+object.getWidth() == temp_map.getPosition_x() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() >= map_width_end)){
                    return false;
                }
            }
        }
    }
    else if(object.getTeam() == Gameobject::Team::my_bullet){
        if(direction == (int)Gameobject::Direction::up){
            for(auto temp_map:map){
                if((object.getPosition_y()-bullet_speed <= temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth()&&object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() <= map_height_start)){
                    return false;
                }
            }
            for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                if((object.getPosition_y()-bullet_speed <= temp_enemy_tank->getPosition_y()+temp_enemy_tank->getHeight() && object.getPosition_y()+object.getHeight() > temp_enemy_tank->getPosition_y()+temp_enemy_tank->getHeight() && object.getPosition_x() < temp_enemy_tank->getPosition_x()+temp_enemy_tank->getWidth()&&object.getPosition_x()+object.getWidth() > temp_enemy_tank->getPosition_x())){
                    boom.setPosition_x(temp_enemy_tank->getPosition_x());
                    boom.setPosition_y(temp_enemy_tank->getPosition_y());
                    boom.setDirection(temp_enemy_tank->getDirection());
                    boom.setWidth(temp_enemy_tank->getWidth());
                    boom.setHeight(temp_enemy_tank->getHeight());
                    boom.setTeam(Gameobject::Team::boom1);
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                    return false;
                }
            }
        }
        else if(direction == (int)Gameobject::Direction::down){
            for(auto temp_map:map){
                if((object.getPosition_y()+object.getHeight() >= temp_map.getPosition_y() && object.getPosition_y() < temp_map.getPosition_y() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() >= map_height_end)){
                    return false;
                }
            }
            for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                if((object.getPosition_y()+object.getHeight()+bullet_speed >= temp_enemy_tank->getPosition_y() && object.getPosition_y() < temp_enemy_tank->getPosition_y() && object.getPosition_x() < temp_enemy_tank->getPosition_x()+temp_enemy_tank->getWidth() && object.getPosition_x()+object.getWidth() > temp_enemy_tank->getPosition_x())){
                    boom.setPosition_x(temp_enemy_tank->getPosition_x());
                    boom.setPosition_y(temp_enemy_tank->getPosition_y());
                    boom.setDirection(temp_enemy_tank->getDirection());
                    boom.setWidth(temp_enemy_tank->getWidth());
                    boom.setHeight(temp_enemy_tank->getHeight());
                    boom.setTeam(Gameobject::Team::boom1);
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                    return false;
                }
            }
        }
        else if(direction == (int)Gameobject::Direction::left){
            for(auto temp_map:map){
                if((object.getPosition_x()-bullet_speed <= temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() <= map_width_start)){
                    return false;
                }
            }
            for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                if((object.getPosition_x()-bullet_speed <= temp_enemy_tank->getPosition_x()+temp_enemy_tank->getWidth() && object.getPosition_x()+object.getWidth() > temp_enemy_tank->getPosition_x()+temp_enemy_tank->getWidth() && object.getPosition_y() < temp_enemy_tank->getPosition_y()+temp_enemy_tank->getHeight() && object.getPosition_y()+object.getHeight() > temp_enemy_tank->getPosition_y())){
                    boom.setPosition_x(temp_enemy_tank->getPosition_x());
                    boom.setPosition_y(temp_enemy_tank->getPosition_y());
                    boom.setDirection(temp_enemy_tank->getDirection());
                    boom.setWidth(temp_enemy_tank->getWidth());
                    boom.setHeight(temp_enemy_tank->getHeight());
                    boom.setTeam(Gameobject::Team::boom1);
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                    return false;
                }
            }
        }
        else if(direction == (int)Gameobject::Direction::right){
            for(auto temp_map:map){
                if((object.getPosition_x()+object.getWidth()+bullet_speed >= temp_map.getPosition_x() && object.getPosition_x() < temp_map.getPosition_x() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() >= map_width_end)){
                    return false;
                }
            }
            for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                if((object.getPosition_x()+object.getWidth()+bullet_speed >= temp_enemy_tank->getPosition_x() && object.getPosition_x() < temp_enemy_tank->getPosition_x() && object.getPosition_y() < temp_enemy_tank->getPosition_y()+temp_enemy_tank->getHeight() && object.getPosition_y()+object.getHeight() > temp_enemy_tank->getPosition_y())){
                    boom.setPosition_x(temp_enemy_tank->getPosition_x());
                    boom.setPosition_y(temp_enemy_tank->getPosition_y());
                    boom.setDirection(temp_enemy_tank->getDirection());
                    boom.setWidth(temp_enemy_tank->getWidth());
                    boom.setHeight(temp_enemy_tank->getHeight());
                    boom.setTeam(Gameobject::Team::boom1);
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                    return false;
                }
            }
        }
    }
    else if(object.getTeam() == Gameobject::Team::enemy_bullet){
        if(direction == (int)Gameobject::Direction::up){
            for(auto temp_map:map){
                if((object.getPosition_y()-bullet_speed <= temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth()&&object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() <= map_height_start)){
                    return false;
                }
            }
            if((object.getPosition_y()-bullet_speed <= my_tank.getPosition_y()+my_tank.getHeight() && object.getPosition_y()+object.getHeight() > my_tank.getPosition_y()+my_tank.getHeight() && object.getPosition_x() < my_tank.getPosition_x()+my_tank.getWidth()&&object.getPosition_x()+object.getWidth() > my_tank.getPosition_x())){
                my_tank.setTeam(Gameobject::Team::lawless);
                boom.setPosition_x(my_tank.getPosition_x());
                boom.setPosition_y(my_tank.getPosition_y());
                boom.setDirection(my_tank.getDirection());
                boom.setWidth(my_tank.getWidth());
                boom.setHeight(my_tank.getHeight());
                boom.setTeam(Gameobject::Team::boom1);
                for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                }
                return false;
            }
        }
        else if(direction == (int)Gameobject::Direction::down){
            for(auto temp_map:map){
                if((object.getPosition_y()+object.getHeight() >= temp_map.getPosition_y() && object.getPosition_y() < temp_map.getPosition_y() && object.getPosition_x() < temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()) || (object.getPosition_y() >= map_height_end)){
                    return false;
                }
            }
            if((object.getPosition_y()+object.getHeight()+bullet_speed >= my_tank.getPosition_y() && object.getPosition_y() < my_tank.getPosition_y() && object.getPosition_x() < my_tank.getPosition_x()+my_tank.getWidth() && object.getPosition_x()+object.getWidth() > my_tank.getPosition_x())){
                my_tank.setTeam(Gameobject::Team::lawless);
                boom.setPosition_x(my_tank.getPosition_x());
                boom.setPosition_y(my_tank.getPosition_y());
                boom.setDirection(my_tank.getDirection());
                boom.setWidth(my_tank.getWidth());
                boom.setHeight(my_tank.getHeight());
                boom.setTeam(Gameobject::Team::boom1);
                for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                }
                return false;
            }
        }
        else if(direction == (int)Gameobject::Direction::left){
            for(auto temp_map:map){
                if((object.getPosition_x()-bullet_speed <= temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_x()+object.getWidth() > temp_map.getPosition_x()+temp_map.getWidth() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() <= map_width_start)){
                    return false;
                }
            }
            if((object.getPosition_x()-bullet_speed <= my_tank.getPosition_x()+my_tank.getWidth() && object.getPosition_x()+object.getWidth() > my_tank.getPosition_x()+my_tank.getWidth() && object.getPosition_y() < my_tank.getPosition_y()+my_tank.getHeight() && object.getPosition_y()+object.getHeight() > my_tank.getPosition_y())){
                my_tank.setTeam(Gameobject::Team::lawless);
                boom.setPosition_x(my_tank.getPosition_x());
                boom.setPosition_y(my_tank.getPosition_y());
                boom.setDirection(my_tank.getDirection());
                boom.setWidth(my_tank.getWidth());
                boom.setHeight(my_tank.getHeight());
                boom.setTeam(Gameobject::Team::boom1);
                for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                }
                return false;
            }
        }
        else if(direction == (int)Gameobject::Direction::right){
            for(auto temp_map:map){
                if((object.getPosition_x()+object.getWidth()+bullet_speed >= temp_map.getPosition_x() && object.getPosition_x() < temp_map.getPosition_x() && object.getPosition_y() < temp_map.getPosition_y()+temp_map.getHeight() && object.getPosition_y()+object.getHeight() > temp_map.getPosition_y()) || (object.getPosition_x() >= map_width_end)){
                    return false;
                }
            }
            if((object.getPosition_x()+object.getWidth()+bullet_speed >= my_tank.getPosition_x() && object.getPosition_x() < my_tank.getPosition_x() && object.getPosition_y() < my_tank.getPosition_y()+my_tank.getHeight() && object.getPosition_y()+object.getHeight() > my_tank.getPosition_y())){
                my_tank.setTeam(Gameobject::Team::lawless);
                boom.setPosition_x(my_tank.getPosition_x());
                boom.setPosition_y(my_tank.getPosition_y());
                boom.setDirection(my_tank.getDirection());
                boom.setWidth(my_tank.getWidth());
                boom.setHeight(my_tank.getHeight());
                boom.setTeam(Gameobject::Team::boom1);
                for(auto temp_enemy_tank = enemy_tank.begin(); temp_enemy_tank != enemy_tank.end(); temp_enemy_tank++){
                    temp_enemy_tank = enemy_tank.erase(temp_enemy_tank);
                }
                return false;
            }
        }
    }
    return true;
}
void show_boom(){
//    if(boom.getTeam() == Gameobject::Team::boom1){
//        boom.setTeam(Gameobject::Team::boom2);
//    }
//    else if(boom.getTeam() == Gameobject::Team::boom2){
//        boom.setTeam(Gameobject::Team::boom3);
//    }
//    else if(boom.getTeam() == Gameobject::Team::boom3){
//        boom.setTeam(Gameobject::Team::lawless);
//    }
    boom.setTeam((Gameobject::Team)((int)boom.getTeam()+1));
}

void create_bullet_list(Gameobject objeoct)
{
      if(objeoct.getTeam() == Gameobject::Team::my_tank){
          if(objeoct.getDirection() == Gameobject::Direction::up){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth()/2-bullet_width/2,objeoct.getPosition_y()-bullet_height,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::my_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::down){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth()/2-bullet_width/2,objeoct.getPosition_y()+objeoct.getHeight(),objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::my_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::left){
              Gameobject bullet(objeoct.getPosition_x()-bullet_width,objeoct.getPosition_y()+objeoct.getHeight()/2-bullet_height/2,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::my_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::right){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth(),objeoct.getPosition_y()+objeoct.getHeight()/2-bullet_height/2,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::my_bullet);
              bullet_list.push_back(bullet);
          }
      }
      else{
          if(objeoct.getDirection() == Gameobject::Direction::up){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth()/2-bullet_width/2,objeoct.getPosition_y()-bullet_height,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::enemy_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::down){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth()/2-bullet_width/2,objeoct.getPosition_y()+objeoct.getHeight(),objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::enemy_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::left){
              Gameobject bullet(objeoct.getPosition_x()-bullet_width,objeoct.getPosition_y()+objeoct.getHeight()/2-bullet_height/2,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::enemy_bullet);
              bullet_list.push_back(bullet);
          }
          else if(objeoct.getDirection() == Gameobject::Direction::right){
              Gameobject bullet(objeoct.getPosition_x()+objeoct.getWidth(),objeoct.getPosition_y()+objeoct.getHeight()/2-bullet_height/2,objeoct.getDirection(),bullet_width,bullet_height,Gameobject::Team::enemy_bullet);
              bullet_list.push_back(bullet);
          }
      }
}


void bullet_move()
{
    for(auto temp_bullet = bullet_list.begin(); temp_bullet != bullet_list.end(); temp_bullet++){
        if(!limit_crash(*temp_bullet,(int)temp_bullet->getDirection())){
            temp_bullet = bullet_list.erase(temp_bullet);
        }
        else{
            if(temp_bullet->getDirection() == Gameobject::Direction::up){
                temp_bullet->setPosition_y(temp_bullet->getPosition_y()-bullet_speed);
            }
            else if(temp_bullet->getDirection() == Gameobject::Direction::down){
                temp_bullet->setPosition_y(temp_bullet->getPosition_y()+bullet_speed);
            }
            else if(temp_bullet->getDirection() == Gameobject::Direction::left){
                temp_bullet->setPosition_x(temp_bullet->getPosition_x()-bullet_speed);
            }
            else if(temp_bullet->getDirection() == Gameobject::Direction::right){
                temp_bullet->setPosition_x(temp_bullet->getPosition_x()+bullet_speed);
            }
        }
    }
}


void my_tank_move(moodycamel::ConcurrentQueue<int> *key_communication){
    int temp;
    if(key_communication->try_dequeue(temp)){
        if(temp == Qt::Key_Up && limit_crash(my_tank,temp) ){
            my_tank.setPosition_y(my_tank.getPosition_y() - tank_speed);
            my_tank.setDirection(Gameobject::Direction::up);
        }
        else if(temp == Qt::Key_Down && limit_crash(my_tank,temp)){
            my_tank.setPosition_y(my_tank.getPosition_y() + tank_speed);
            my_tank.setDirection(Gameobject::Direction::down);
        }
        else if(temp == Qt::Key_Left && limit_crash(my_tank,temp)){
            my_tank.setPosition_x(my_tank.getPosition_x() - tank_speed);
            my_tank.setDirection(Gameobject::Direction::left);
        }
        else if(temp == Qt::Key_Right && limit_crash(my_tank,temp)){
            my_tank.setPosition_x(my_tank.getPosition_x() + tank_speed);
            my_tank.setDirection(Gameobject::Direction::right);
        }
        else if(temp == Qt::Key_Space){
            create_bullet_list(my_tank);
        }
    }
}



void enemy_tank_move(Gameobject *enemy_tank,bool flag){
    std::uniform_int_distribution<unsigned> limit(Qt::Key_Left,Qt::Key_Down);
    if(flag){
        while (true) {
            int direction = limit(engine);
            //qDebug()<<direction;
            if(limit_crash(*enemy_tank,direction)){

                if(direction == Qt::Key_Up){
                    enemy_tank->setDirection(Gameobject::Direction::up);
                    enemy_tank->setPosition_y(enemy_tank->getPosition_y() - tank_speed);
                }
                else if(direction == Qt::Key_Down){
                    enemy_tank->setDirection(Gameobject::Direction::down);
                    enemy_tank->setPosition_y(enemy_tank->getPosition_y() + tank_speed);
                }
                else if(direction == Qt::Key_Left){
                    enemy_tank->setDirection(Gameobject::Direction::left);
                    enemy_tank->setPosition_x(enemy_tank->getPosition_x() - tank_speed);
                }
                else if(direction == Qt::Key_Right){
                    enemy_tank->setDirection(Gameobject::Direction::right);
                    enemy_tank->setPosition_x(enemy_tank->getPosition_x() + tank_speed);
                }
                create_bullet_list(*enemy_tank);
                break;
            }
        }
    }
    else{
        if(limit_crash(*enemy_tank,(int)enemy_tank->getDirection())){
            if(enemy_tank->getDirection() == Gameobject::Direction::up){
                enemy_tank->setPosition_y(enemy_tank->getPosition_y() - tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::down){
                enemy_tank->setPosition_y(enemy_tank->getPosition_y() + tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::left){
                enemy_tank->setPosition_x(enemy_tank->getPosition_x() - tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::right){
                enemy_tank->setPosition_x(enemy_tank->getPosition_x() + tank_speed);
            }
        }
        else {
            if(enemy_tank->getDirection() == Gameobject::Direction::up){
                enemy_tank->setDirection(Gameobject::Direction::down);
                enemy_tank->setPosition_y(enemy_tank->getPosition_y() + tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::down){
                enemy_tank->setDirection(Gameobject::Direction::up);
                enemy_tank->setPosition_y(enemy_tank->getPosition_y() - tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::left){
                enemy_tank->setDirection(Gameobject::Direction::right);
                enemy_tank->setPosition_x(enemy_tank->getPosition_x() + tank_speed);
            }
            else if(enemy_tank->getDirection() == Gameobject::Direction::right){
                enemy_tank->setDirection(Gameobject::Direction::left);
                enemy_tank->setPosition_x(enemy_tank->getPosition_x() - tank_speed);
            }
        }
    }

}


void control_operate(int *count)
{
    if(*count%(FPS/3) == 0){
        bullet_move();
    }
    if(*count%(FPS/6) == 0 && boom.getTeam() != Gameobject::Team::lawless){
        show_boom();
    }
    std::vector<std::thread> thread_list;
    for(auto &temp_enemy_tank: enemy_tank){
        if(*count%(FPS/3) == 0){
            if(*count%FPS == 0){
                //enemy_tank_move(&temp_enemy_tank,true);
                thread_list.emplace_back(enemy_tank_move,&temp_enemy_tank,true);
            }
            else{
                //enemy_tank_move(&temp_enemy_tank,false);
                thread_list.emplace_back(enemy_tank_move,&temp_enemy_tank,false);
            }
        }
    }
    for(std::thread &temp_thread_list: thread_list){
        temp_thread_list.join();
    }

}
