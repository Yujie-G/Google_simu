#include<Game.h>
#include<BrowserView.h>
const int MAX_LEN = 1500, MAX_WID=480;

Game::Game()
{
    this->setMinimumSize(1150,MAX_WID);
}

void Game::mainscene(){
    QLabel* scene=new QLabel();
    scene->setMaximumSize(MAX_LEN,MAX_WID);
    scene->setGeometry(0,0,MAX_LEN,MAX_WID);
    QPixmap a;
    a.load(":/sourc/scene.png");
//    QPixmap B=a.scaled(MAX_LEN,MAX_WID,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setPixmap(a);
    scene->setParent(this);
    //    QPushButton*exit=new QPushButton("Back to Menu");
    //    exit->setParent(this);
    //       exit->move(0,0);
    //       exit->setFixedSize(80,30);
    //       exit->show();
    //       connect(exit,&QPushButton::clicked,[=](){
    //           this->hide();
    //       });
}

int i=0;
void Game::pixmapshowd(){
    dinosaur=new QLabel();
    timer1=new QTimer();
    timer1->start(300);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap a;
        QString str=QString(":/sourc/d00%1.png").arg(i);
        a.load(str);
        QPixmap B=a.scaled(43,44,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        dinosaur->setPixmap(B);
        dinosaur->setGeometry(0,0,B.width(),B.height());
        dinosaur->setParent(this);
        dinosaur->move(100,245);
        Dinosaur.setRect(100,245,B.width(),B.height());
        dinosaur->show();
        i++;
        i=i%2;
    });
}

void Game::judge(QRect r1,QRect r2){
    if(r1.intersects(r2)){
        win=1;
        timer1->stop();
        timer2->stop();
        timer4->stop();
        timer5->stop();
        timer6->stop();
        timer7->stop();
        scoretimer->stop();
        QLabel *end=new QLabel();
        end->setParent(this);
        QPixmap a1;
        a1.load(":/sourc/gameover.png");
        end->setPixmap(a1);
        end->setGeometry(0,0,a1.width(),a1.height());
        end->move((this->width()-a1.width())*0.5,-200);
        end->show();
        QPropertyAnimation *animation1=new QPropertyAnimation(end,"geometry");
        animation1->setDuration(1000);
        animation1->setStartValue(QRect(end->x(),end->y(),end->width(),end->height()));
        animation1->setEndValue(QRect(end->x(),end->y(),end->width(),end->height()+650));
        animation1->start();
        QTimer::singleShot(1000,this,[=](){
            QPushButton *again=new QPushButton();
            again->setParent(this);

            QPixmap a;
            a.load(":/sourc/playagain.png");
            again->move(MAX_LEN*0.5-a.width()*0.5,200);
            again->setFixedSize(a.width(),a.height());
            again->setIcon(QIcon(":/sourc/playagain.png"));

            again->show();
            connect(again,&QPushButton::clicked,[=](){
                this->hide();
                delete(g);
                g=new Game();
                g->mainscene();
                g->pixmapshowg();
                g->pixmapshowd();
                g->pixmapshown();
                //w.pixmapshowp();
                g->pixmapshowt();
                g->pixmapshowc();
                g->score();
                g->show();
            });
            again->move(MAX_LEN*0.5-a.width()*0.5,200);
        });
    }

}


int k=0;
static int k2=0;
void Game::pixmapshowg(){
    QLabel*ground1=new QLabel();
    QLabel*ground2=new QLabel();
    QPixmap a,b;
    a.load(":/sourc/ground2.png");
    ground1->setPixmap(a);
    b.load(":/sourc/ground2.png");
    ground2->setPixmap(b);
    timer4=new QTimer();
    timer4->start(40);
    connect(timer4,&QTimer::timeout,[=](){
        ground1->setGeometry(k2-k*5,335-50,a.width(),a.height());
        ground1->setParent(this);
        ground1->show();
        ground2->setGeometry(k2+MAX_LEN-k*5,335-50,a.width(),a.height());
        ground2->setParent(this);
        ground2->show();
        if(k2-k*5<=-MAX_LEN){k2+=MAX_LEN;}
        k++;
    });
}
std::vector<int>l;
void  Game::treerun(int y,int count){
    QPixmap *a=new QPixmap();
    QLabel*tree=new QLabel();
    QString str=QString(":/sourc/tree%1.png").arg(y%4);
    a->load(str);
    timer5=new QTimer();
    tree->setPixmap(*a);
    tree->setParent(this);
    timer5->start(40);
    connect(timer5,&QTimer::timeout,[=](){
        if(win==0){
            if(y%4==2||y%4==3){
                tree->setGeometry(y-l[count]*5+MAX_LEN,292-50,a->width(),a->height());
                tree->show();
                QRect Tree(y-l[count]*5+MAX_LEN+a->width()*0.25,292-50,a->width()*0.5,a->height());
                this->judge(Tree,Dinosaur);
                l[count]++;}
            else{
                tree->setGeometry(y-l[count]*5+MAX_LEN,305-50,a->width(),a->height());
                tree->show();
                QRect Tree(y-l[count]*5+MAX_LEN+a->width()*0.25,305-50,a->width()*0.5,a->height());
                this->judge(Tree,Dinosaur);
                l[count]++;
            }
        }
    });
}
int count=0;
void Game:: pixmapshowt(){
    timer6=new QTimer();
    timer6->start(4000);
    connect(timer6,&QTimer::timeout,[=](){
        l.push_back(0);

        int y=rand()%100;
        this->treerun(y,count);
        count++;
    });
}
std::vector<int>m;
int count1=0;

void  Game::nrun(int y,int count1){
    timer2=new QTimer();
    timer2->start(125);
    QLabel* dinosaurn1=new QLabel();
    QLabel* dinosaurn2=new QLabel();
    QPixmap a,b;
    QString str1=QString(":/sourc/n0.png");
    QString str2=QString(":/sourc/n1.png");
    a.load(str1);b.load(str2);
    dinosaurn1->setPixmap(a);
    dinosaurn2->setPixmap(b);
    connect(timer2,&QTimer::timeout,[=](){
        if(m[count1]%2==0){        dinosaurn1->setParent(this);
            dinosaurn1->setGeometry(y-m[count1]*20+MAX_LEN,220-50+y%3*20,a.width(),a.height());
            dinosaurn2->close();
            dinosaurn1->show();
            QRect N(y-m[count1]*20+MAX_LEN-20,220-50+y%3*20,a.width(),a.height());
            this->judge(N,Dinosaur);
            m[count1]++; }
        else{ dinosaurn2->setParent(this);
            dinosaurn2->setGeometry(y-m[count1]*20+MAX_LEN,220-50+y%3*20,a.width(),a.height());
            dinosaurn1->close();
            dinosaurn2->show();
            QRect N(y-m[count1]*20+MAX_LEN-20,220-50+y%3*20,a.width(),a.height());
            this->judge(N,Dinosaur);
            m[count1]++; }

    } );
}

void Game:: pixmapshown(){
    timer7=new QTimer();
    timer7->start(14000);
    connect(timer7,&QTimer::timeout,[=](){
        m.push_back(0);

        int y=rand()%300;
        this->nrun(y,count1);
        count1++;
    });

}
void Game::djump(QLabel*jump){
    QPropertyAnimation*animation1=new QPropertyAnimation(jump,"geometry");
    animation1->setDuration(600);
    animation1->setStartValue(QRect(100,295-50,jump->width(),jump->height()));
    animation1->setEndValue(QRect(100,210-50,jump->width(),jump->height()));
    //    animation1->setEasingCurve(QEasingCurve::OutBounce);

    animation1->start();
    isanimation=1;
    Dinosaur.setRect(100,210-50,jump->width(),jump->height());
}
void Game::ddown(QLabel*jump){

    QPropertyAnimation*animation2=new QPropertyAnimation(jump,"geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(100,210-50,jump->width(),jump->height()));
    animation2->setEndValue(QRect(100,295-50,jump->width(),jump->height()));
    //    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
    isanimation=1;
}

void Game::keyPressEvent(QKeyEvent *event)  {
    if(win==1||isanimation==1){return;}
    QKeyEvent*key=(QKeyEvent *)event;
    jump=new QLabel();
    down=new QLabel();
    QPixmap a,b;
    a.load(":/sourc/d0.png");
    jump->setFixedSize(80,60);
    jump->setPixmap(a);
    jump->setParent(this);
    jump->setGeometry(0,0,a.width(),a.height());

    b.load(":/sourc/d1.png");
    down->setFixedSize(80,60);
    down->setPixmap(b);
    down->setParent(this);
    down->setGeometry(dinosaur->x(),dinosaur->y(),b.width(),b.height());
    if(key->key()==Qt::Key_Up){
        dinosaur->hide();
        timer1->stop();
        jump->show();
        this->djump(jump);
        QTimer::singleShot(600,this,[=](){ this->ddown(jump);});
        QTimer::singleShot(1200,this,[=](){ jump->hide();});
        QTimer::singleShot(1200,this,[=](){ isanimation=0;timer1->start();dinosaur->show();Dinosaur.setRect(100,95,43,44);});
    }
    else  if(key->key()==Qt:: Key_Down){
        dinosaur->hide();
        timer1->stop();
        down->show();
        //        this->ddown(down);
        if(event->isAutoRepeat()==false){

        }
    }

}

void Game::keyReleaseEvent(QKeyEvent *event)  {
    if(event->key()==Qt::Key_Down)
    {
        down->hide();
        isanimation=0;
        timer1->start();
        dinosaur->show();
        Dinosaur.setRect(100,95,43,44);
    }
}

void Game::pixmapshowc(){
    QLabel*cloud1=new QLabel();
    QLabel*cloud2=new QLabel();
    QLabel*cloud3=new QLabel();
    QLabel*cloud4=new QLabel();
    QLabel*cloud5=new QLabel();
    QLabel*cloud6=new QLabel();
    QLabel*sun=new QLabel();
    QPixmap a;
    a.load(":/sourc/cloud1.png");
    cloud1->setPixmap(a);
    cloud1->setParent(this);
    cloud1->setGeometry(100,50,a.width(),a.height());
    cloud1->show();
    cloud2->setPixmap(a);
    cloud2->setParent(this);
    cloud2->setGeometry(150,70,a.width(),a.height());
    cloud2->show();
    cloud3->setPixmap(a);
    cloud3->setParent(this);
    cloud3->setGeometry(350,20,a.width(),a.height());
    cloud3->show();
    cloud4->setPixmap(a);
    cloud4->setParent(this);
    cloud4->setGeometry(700,100,a.width(),a.height());
    cloud4->show();
    cloud5->setPixmap(a);
    cloud5->setParent(this);
    cloud5->setGeometry(600,40,a.width(),a.height());
    cloud5->show();
    cloud6->setPixmap(a);
    cloud6->setParent(this);
    cloud6->setGeometry(900,110,a.width(),a.height());
    cloud6->show();
    QPixmap b;
    b.load(":/sourc/sun.png");
    sun->setPixmap(b);
    sun->setParent(this);
    sun->setGeometry(1000,30,b.width(),b.height());
    sun->show();

}

void Game::score(){
    scoretimer=new QTimer();
    scoretimer->start(1000);
    QLabel*score=new QLabel();
    score->setParent(this);
    score->setGeometry(1050,10,100,100);
    score->setText("your score:0");
    connect(scoretimer,&QTimer::timeout,[=](){
        QString str=QString("Score:%1").arg(Game::num);
        score->setText(str);
        Game::num++;
        score->show();
    });
}


startscene::startscene(BrowserView *parent = nullptr)
{
    this->parent = parent;
    QLabel *scene = new QLabel();
//    scene->setGeometry(0, 0, MAX_LEN, MAX_WID);
    scene->setPixmap(QPixmap(":/sourc/scene.png"));
    scene->setScaledContents( true );
    scene->setParent(this);
    //        t = new teachwidget();
    this->setFixedSize(MAX_LEN, MAX_WID);
    //    setWindowIcon(QIcon(":/sourc/d0.png"));
    //    QPushButton *exit = new QPushButton("Quit");
    //    exit->setParent(this);
    //    exit->move(0, 0);
    //    exit->setFixedSize(80, 60);
    //    exit->show();
    //    connect(exit, &QPushButton::clicked, [=]()
    //            { this->close(); });
    //    start = new QPushButton("Start");
    //    QFont font;
    //    font.setPointSize(30);
    //    start->setFont(font);
    //    start->setParent(this);
    //    start->move(MAX_LEN * 0.5 - 100, 200 - 50);
    //    start->setFixedSize(200, 100);
    //        teach = new QPushButton("Help");
    //        teach->setParent(this);
    //        teach->move(MAX_LEN - 80, 400 - 50);
    //        teach->setFixedSize(80, 50);
    QLabel *hint = new QLabel("Tap blank to start..");
    hint->setParent(this);
    hint->move(500,150);
    QLabel *dinosaur = new QLabel();
    QTimer *timer1 = new QTimer();
    timer1->start(300);
    connect(timer1, &QTimer::timeout, [=]()
    {
        QPixmap a;
        QString str=QString(":/sourc/d00%1.png").arg(i2);
        a.load(str);
        QPixmap B=a.scaled(43*3,44*3,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        dinosaur->setPixmap(B);
        dinosaur->setGeometry(0,0,B.width(),B.height());
        dinosaur->setParent(this);
        dinosaur->move(100,100);
        dinosaur->show();
        i2++;
        i2=i2%2; });
    //        connect(this->teach, &QPushButton::clicked, [=]()
    //                {
    //                    t->show();
    //                });
    //    connect(this->start, &QPushButton::clicked, [=]()
    //            {
    //            QTimer::singleShot(600,this,[=](){
    //            this->hide();
    //            Game *g = new Game();
    //            g->mainscene();
    //            g->pixmapshowg();
    //            g->pixmapshowd();
    //            g->pixmapshown();
    //          //w.pixmapshowp();
    //            g->pixmapshowt();
    //            g->pixmapshowc();
    //            g->score();
    //            parent->vLayout->removeWidget(this);
    //            parent->vLayout->addWidget(g);
    //            g->setFocus();
    //            });
    //    });
}

void startscene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
    {
        QTimer::singleShot(600,this,[=](){
            this->hide();
            parent->vLayout->removeWidget(this);
            parent->hint->hide();
            parent->vLayout->removeWidget(parent->hint);
            Game *g = new Game();
            g->mainscene();
            g->pixmapshowg();
            g->pixmapshowd();
            g->pixmapshown();
            //w.pixmapshowp();
            g->pixmapshowt();
            g->pixmapshowc();
            g->score();
            parent->vLayout->addWidget(g);
            g->setFocus();
            parent->vLayout->setSpacing(0);
        });
    }
}
