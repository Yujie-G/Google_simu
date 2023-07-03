#ifndef GAME_H
#define GAME_H

#include<QMainWindow>
#include<QtWidgets>
#include<QLabel>
#include<QPixmap>
#include<QTimer>
#include<QPainter>
#include<QDebug>
#include<QtGlobal>
#include<QPropertyAnimation>
#include<QKeyEvent>


class Game:public QWidget
{
    Q_OBJECT
public:
    Game();
    QRect Dinosaur;
    QLabel *dinosaur;
    Game *g;
    QTimer *scoretimer;
    bool win = 0;
    QLabel *jump;
    QLabel *down;
    int isanimation = 0;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer4;
    QTimer *timer5;
    QTimer *timer6;
    QTimer *timer7;
    int num = 1;
    void mainscene();
    void judge(QRect, QRect);
    void pixmapshowd();
    void pixmapshown();
    void nrun(int, int);
    void pixmapshowp();
    void pixmapshowg();
    void pixmapshowc();
    void treerun(int, int);
    void pixmapshowt();
    void djump(QLabel *);
    void ddown(QLabel *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void score();

};



#endif // GAME_H
