#ifndef GAMESET_H
#define GAMESET_H
class Gameobject{


public:
    enum class Direction:int{
        up,
        down,
        left,
        right
    };
    enum class Team:int
    {
        my_tank,
        enemy_tank,
        my_bullet,
        enemy_bullet,
        wall1_map,
        wall2_map,
        tree_map,
        boom1,
        boom2,
        boom3,
        lawless
    };
    Gameobject(){

    }
    Gameobject(int position_x, int position_y, Direction direction,int width, int height, Team team){
        this->position_x = position_x;
        this->position_y = position_y;
        this->direction = direction;
        this->width = width;
        this->height = height;
        this->team = team;
    }
    ~Gameobject(){

    }


    int getPosition_x() const;
    void setPosition_x(int value);
    int getPosition_y() const;
    void setPosition_y(int value);
    Direction getDirection() const;
    void setDirection(const Direction &value);
    int getWidth() const;
    void setWidth(int value);
    int getHeight() const;
    void setHeight(int value);
    Team getTeam() const;
    void setTeam(const Team &value);

private:
    int position_x;
    int position_y;
    Direction direction;
    int width;
    int height;
    Team team;
};

#endif // GAMESET_H

