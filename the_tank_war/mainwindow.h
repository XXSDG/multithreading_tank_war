#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include "concurrentqueue.h"
#include "gameobject.h"
#include "mainloop.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
constexpr const int FPS = 60;
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *Event);
    void onTimeout();
    enum class flag:int
    {
        prepare,
        fight,
        finish
    };

private:
    Ui::MainWindow *ui;
    flag state_machine = flag::prepare;
    QPushButton *btn;
    QPushButton *btn_exit;
    QTimer *timer;
    bool flag_fight_finish = false;
    bool flag_loop_finish = false;
    moodycamel::ConcurrentQueue<int> key_communication;
    moodycamel::ConcurrentQueue<Gameobject> icon_communication;
    std::thread main_loop;
    //std::vector<std::thread> main_loop;
};
#endif // MAINWINDOW_H
