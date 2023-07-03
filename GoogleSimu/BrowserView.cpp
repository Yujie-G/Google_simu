#include <BrowserView.h>
#include <Game.h>
#include <fstream>




BrowserView::BrowserView()
    :HOME(QUrl("https://www.google.com")),curTab(nullptr)
{
    setWindowTitle("Google Simu");
    setWindowIcon(QIcon(":/sourc/Google_icon.png"));
    this->setMaximumSize(MAX_LEN,MAX_WID);
    view = new QWebEngineView(this);
    view->setMinimumSize(MAX_LEN*0.6,MAX_WID-100);
    view->load(HOME);//home pagedsdf
    history = new QMenu();

    //set Tabs
    tabs_column = new QHBoxLayout();
    tabs_column->setDirection(QBoxLayout::LeftToRight);
    tabs_column->setAlignment(Qt::AlignLeft);
    tabs_column->setSpacing(7);
    addNewTab();

    // set Search Bar
    SearchBar *sb = new SearchBar(this);
    QObject::connect(sb, &QLineEdit::returnPressed, [=]() {
        view->load(sb->parseInput(sb->text()));
    });
    QObject::connect (view, &QWebEngineView::loadFinished, this, [=] (bool ok) {
        if(!ok)
        {
            //show bad-connection
            view->hide();
            vLayout->removeWidget(view);
            hint=new QLabel();
            hint->setFixedSize(1150,300);
            hint->setPixmap(QPixmap(":/sourc/disconnect.png"));
            hint->setScaledContents( true );
            //          hint->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            vLayout->addWidget(hint,0,Qt::AlignTop);
            showGame();
            qDebug()<<"disconnect";
        }
        else //sucessfully load
        {
            //isFavourite?
            favorite->setUnFavour();

            curTab->setText(view->title());
            curTab->url = view->url();
            curTab->beFocused();
            QAction *q = new QAction(view->url().toString(),this);
            history->addAction(q);
        }
    });


    // set Buttons
    setStyleSheet("border:none");
    homeButton = new  QPushButton(this);
    QIcon home_icon;
    home_icon.addFile(":/sourc/home.png");
    homeButton->setIcon(home_icon);
    homeButton->setFlat(true);
    QObject::connect(homeButton, &QPushButton::clicked, view, [=]() {
        view->load(HOME);
        sb->clearText();
    });

    backButton = new QPushButton(this);
    QIcon back_icon;
    back_icon.addFile(":/sourc/back.png");
    backButton->setIcon(back_icon);
    backButton->setFlat(true);
    QObject::connect(backButton, &QPushButton::clicked, view, &QWebEngineView::back);

    forwardButton = new QPushButton(this);
    QIcon fw_icon;
    fw_icon.addFile(":/sourc/forward.png");
    forwardButton->setIcon(fw_icon);
    forwardButton->setFlat(true);
    QObject::connect(forwardButton, &QPushButton::clicked, view, &QWebEngineView::forward);

    reloadButton = new QPushButton(this);
    QIcon re_icon;
    re_icon.addFile(":/sourc/refersh.png");
    reloadButton->setIcon(re_icon);
    reloadButton->setFlat(true);
    QObject::connect(reloadButton, &QPushButton::clicked, view, &QWebEngineView::reload);

    progressBar = new QProgressBar(this);
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setMaximumHeight(10);
    QObject::connect(view, &QWebEngineView::loadProgress, progressBar, &QProgressBar::setValue);

    favorite = new Favorite(this);
    favorite->setWeb(view);
    QObject::connect(favorite, &QToolButton::clicked, favorite,[=](){
        addPage2Fav();
        favorite->setFavour();
    });

    setting = new Setting(this);



    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(backButton);
    hLayout->addWidget(forwardButton);
    hLayout->addWidget(reloadButton);
    hLayout->addWidget(homeButton);
    hLayout->addWidget(sb);
    hLayout->addWidget(favorite);
    hLayout->addWidget(setting);
    hLayout->setSpacing(20);
    hLayout->setMargin(0);


    vLayout = new QVBoxLayout(this);
    vLayout->addLayout(tabs_column);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(progressBar,0,Qt::AlignTop);
    vLayout->addWidget(view);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    //Debug: directly show game
    //    view->hide();
    //    vLayout->removeWidget(view);
    //    showGame();

}

void BrowserView::addPage2Fav(){
    std::ofstream file("fav_urls.txt", std::ios_base::app);
    if (file.is_open()) {
            file << view->url().toString().toStdString() << std::endl;
            file.close();
            qDebug()<<"url writed!";
    }
}
void BrowserView::showGame()
{
    //    if(view->isHidden())
    //        vLayout->removeWidget(view);
    startscene *ss = new startscene(this);
    ss->show();
    vLayout->addWidget(ss,0,Qt::AlignTop);
    ss->setFocusPolicy(Qt::ClickFocus);
}

void BrowserView::showPdf(QString add)
{
    pdfView = new QPdfWidget();
    pdfView->setMinimumHeight(900);
    view->hide();
    vLayout->removeWidget(view);
    vLayout->addWidget(pdfView);
    pdfView->loadFile(add);
}


void BrowserView::addNewTab()
{
    Tab *toThisPage = new Tab(this);
    toThisPage->url = HOME;
    QObject::connect(toThisPage,&QPushButton::clicked, view, [=]() {
        if(this->curTab)
            curTab->leaveFocused();
        view->load(toThisPage->url);
        this->curTab = toThisPage;
        this->curTab->beFocused();
    });

    tabs_column->addWidget(toThisPage);
    if(this->curTab!=nullptr) curTab->leaveFocused();
    view->load(toThisPage->url);
    this->curTab = toThisPage;
    this->curTab->beFocused();
}




