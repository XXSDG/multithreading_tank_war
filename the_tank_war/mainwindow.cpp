#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainloop.h"
#include <QKeyEvent>
#include  <QPushButton>
#include <thread>
#include<QDir>
#include <QIcon>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;
    timer->setInterval(1000/FPS);
    connect(timer, &QTimer::timeout ,this, &MainWindow::onTimeout);
    btn = new QPushButton("开始游戏",this);
    btn->move(width()/2-btn->width()/2,height()/2);
    btn->setStyleSheet("QPushButton{font:20px;}");
    btn_exit = new QPushButton("退出游戏",this);
    btn_exit->setStyleSheet("QPushButton{font:20px;}");
    btn_exit->hide();
    QObject::connect(btn_exit,&QPushButton::clicked,[this](){
        flag_loop_finish = true;
        this->update();
        main_loop.join();
        this->close();

    });
    //btn->resize(200,200);
    QObject::connect(btn,&QPushButton::clicked,btn,&QPushButton::hide);
    main_loop = std::thread(Mainloop,&key_communication,&icon_communication,
                                              &flag_fight_finish,&flag_loop_finish);

}

MainWindow::~MainWindow()
{
//    main_loop.join();
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    key_communication.enqueue(event->key());
}

void MainWindow::paintEvent(QPaintEvent *Event)
{
    //qDebug() << "!!";
    static QString critical_table[(int)(Gameobject::Direction::right)+1][(int)(Gameobject::Team::boom3)+1] =
    {{":/resource/hero1U.gif",
      ":/resource/enemy2U.gif",
      ":/resource/bullet_up.png",
      ":/resource/bullet_up.png",
      ":/resource/wall1.png",
      "/Users/xiaoshuai/the_tank_war/resource/wall2.png",
      ":/resource/3.png",
      ":/resource/bomb_3.gif",
      ":/resource/bomb_2.gif",
      ":/resource/bomb_1.gif"},
     {":/resource/hero1D.gif",
      ":/resource/enemy2D.gif",
      ":/resource/bullet_down.png",
      ":/resource/bullet_down.png",
      ":/resource/wall1.png",
      "/Users/xiaoshuai/the_tank_war/resource/wall2.png",
      ":/resource/3.png",
      ":/resource/bomb_3.gif",
      ":/resource/bomb_2.gif",
      ":/resource/bomb_1.gif"},
     {":/resource/hero1L.gif",
      ":/resource/enemy2L.gif",
      ":/resource/bullet_left.png",
      ":/resource/bullet_left.png",
      ":/resource/wall1.png",
      "/Users/xiaoshuai/the_tank_war/resource/wall2.pngg",
      ":/resource/3.png",
      ":/resource/bomb_3.gif",
      ":/resource/bomb_2.gif",
      ":/resource/bomb_1.gif"},
     {":/resource/hero1R.gif",
      ":/resource/enemy2R.gif",
      ":/resource/bullet_right.png",
      ":/resource/bullet_right.png",
      ":/resource/wall1.png",
      "/Users/xiaoshuai/the_tank_war/resource/wall2.png",
      ":/resource/3.png",
      ":/resource/bomb_3.gif",
      ":/resource/bomb_2.gif",
      ":/resource/bomb_1.gif"}};
    QPainter painter(this);
    QPixmap pix;
    painter.translate(0,0);
    qDebug()<<QDir::currentPath();
    //pix.load("../../../../the_tank_war/resource/background.png");
    pix.load(":/resource/background.png");
    painter.drawPixmap(0,0,width(),height(),pix);
    if(state_machine == flag::prepare){
        btn->show();
        QPixmap pix_1;
        pix_1.load(":/resource/logo.png");
        painter.drawPixmap(width()/2 - pix_1.width()/2, height()/2 - pix_1.height(), pix_1.width(), pix_1.height(),pix_1);
        btn->move(width()/2-btn->width()/2,height()/2+pix_1.height());
        QObject::connect(btn,&QPushButton::clicked,[this](){
            state_machine = flag::fight;
            this->update();
            timer->start();

        });
    }
    if(state_machine == flag::fight){
        if(flag_fight_finish){

            state_machine = flag::finish;
            flag_fight_finish = false;
        }
        else{

            size_t length = icon_communication.size_approx();
            //qDebug() <<length<<endl;
            size_t i = 1;
            while (i <= length) {
                Gameobject temp;
                if(!icon_communication.try_dequeue(temp)){
                    break;
                }
                QString pix_location = critical_table[(int)temp.getDirection()][(int)temp.getTeam()];
                QPixmap pix_temp;
                pix_temp.load(pix_location);
                //qDebug() << "##"<<endl;
                painter.drawPixmap(temp.getPosition_x(),temp.getPosition_y(),temp.getWidth(),temp.getHeight(),pix_temp);
                i++;
            }
        }
    }
    if(state_machine == flag::finish){
        QPixmap pix_2;
        pix_2.load(":/resource/gameover.png");
        painter.drawPixmap(width()/2 - pix_2.width(), height()/2 - pix_2.height(), pix_2.width()*2, pix_2.height()*2, pix_2);
        btn->setText("再来一局");
        btn->move(width()/2-btn->width()/2,height()/2+pix_2.height()*2);
        btn->setStyleSheet("QPushButton{font:20px;}");
        btn_exit->move(btn->x(),btn->y()+btn->height()*2);
        btn->show();
        btn_exit->show();
//        QObject::connect(btn_exit,&QPushButton::clicked,[this](){
//            flag_loop_finish = true;
//            this->update();
//            if(main_loop.joinable()){
//                main_loop.join();
//                this->close();
//            }

//        });
        QObject::connect(btn,&QPushButton::clicked,[this](){
            state_machine = flag::prepare;
            btn_exit->hide();
            btn->setText("开始游戏");
            btn->setStyleSheet("QPushButton{font:20px;}");
            this->update();
            timer->stop();
//            main_loop.join();
//            main_loop = std::thread(Mainloop,&key_communication,&icon_communication,
//                                                      &flag_fight_finish);
        });
    }

}

void MainWindow::onTimeout()
{
    update();
    //qDebug() <<"##";
}

