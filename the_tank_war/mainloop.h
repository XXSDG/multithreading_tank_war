#ifndef MAINLOOP_H
#define MAINLOOP_H
#include "mainwindow.h"
#include "gameobject.h"
#include "concurrentqueue.h"
#include <vector>

void Mainloop(moodycamel::ConcurrentQueue<int> *key_communication,
              moodycamel::ConcurrentQueue<Gameobject> *icon_communication,
              bool *flag_fight_finsih,bool *temp);
#endif // MAINLOOP_H
