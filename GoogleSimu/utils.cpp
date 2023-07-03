#include <utils.h>
#include <BrowserView.h>
#include<fstream>

Tab::Tab(QWidget* p)
    :QPushButton(p)
{
    setFixedWidth(200);
    setStyleSheet("background-color: #DCDCDC;"
                  "border: none;"
                  "margin-right: 5px;"
                  );
    QAction *Close = new QAction("X",this);
    this->addAction(Close);
}

void Tab::beFocused()
{
    this->setStyleSheet("background-color:#87CEFA;"
                        "border-style: solid;"
                        "border-width: 2px;"
                        "border-color: #696969;"
                        "border-radius: 20px;");
}

void Tab::leaveFocused()
{
    this->setStyleSheet("background-color:#DCDCDC;"
                        "border: none;");
}
void Favorite::setFavour(){
    this->setIcon(QIcon(":/sourc/fav_solid.png"));
    this->menu = readFavFile();
    this->setMenu(menu);
}

void Favorite::setUnFavour(){
    this->setIcon(QIcon(":/sourc/fav.png"));
}

bool Favorite::isPDF(QString s) //"D://test_pdf.pdf"
{
    return QFileInfo(s).suffix()=="pdf";
}
QMenu* Favorite::readFavFile()
{
    QMenu *menu = new QMenu(this);

    QAction *actions[10];int cnt=0;
    std::ifstream file("fav_urls.txt");
    if (file.is_open()) {
        std::string urlString;
        while (std::getline(file, urlString)) {
            QString s = QString::fromStdString(urlString);
            actions[cnt] = new QAction(s,this);
            menu->addAction(actions[cnt]);
            //TODO input arg:url
            if(isPDF(s))
            {
                qDebug()<<"find a pdf..";
                actions[cnt]->setIcon(QIcon(":/sourc/pdf.png"));
                connect(actions[cnt],&QAction::triggered, this,[=](){
                    this->parent->showPdf(s);
                });
            }
            else
            {
                connect(actions[cnt],&QAction::triggered, this,[=](){
                    loadUrl(s);
                });
            }
            cnt++;
        }
        file.close();
    }
    return menu;
}


void Favorite::loadUrl(QString s)
{
    this->web->load(QUrl(s));
}

Setting::Setting(BrowserView *p){
    this->parent = p;
    this->setPopupMode(QToolButton::InstantPopup);
    this->setIcon(QIcon(":/sourc/more.png"));
    setStyleSheet("Setting::menu-indicator{"
             "image:none;}");
    this->menu = new QMenu(this);
    QAction *newTab = new QAction(QIcon(":/sourc/new-tab.png"),"new Tab",this);
    menu->addAction(newTab);

    QObject::connect(newTab,&QAction::triggered, this, [=](){
        //do something
        parent->addNewTab();
    });

    QAction *his = new QAction(QIcon(":/sourc/time-history.png"),"History",this);
    menu->addAction(his);
    his->setMenu(parent->history);

    QAction *help = new QAction("Help",this);
    menu->addAction(help);

    QAction *setting = new QAction("Setting",this);
    menu->addAction(setting);

    this->setMenu(menu);
}




