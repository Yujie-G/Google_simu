#ifndef UTILS_H
#define UTILS_H


#include <QWebEngineView>
#include <QtWidgets>
#include <QToolButton>
#include <QMenu>
#include <QAction>
class BrowserView;

class Tab :public QPushButton
{
public:
    Tab(QWidget*);
    QUrl url;
    void beFocused();
    void leaveFocused();
};

class SearchBar : public QLineEdit{
    Q_OBJECT
public:
    SearchBar(QWidget *window):QLineEdit(window)
    {
        this->setPlaceholderText("Search or enter URL here");
        setStyleSheet("padding:6px,6px,2px,2px;"
        "background-color: #DCDCDC;"
        "selection-color: #00BFFF;" );
        QIcon q = QIcon(":/sourc/search.png"); //QPixmap().scaledToWidth(20));

        this->addAction(q,QLineEdit::TrailingPosition);

    }

    void clearText()
    {
        this->setText("");
    }
    QUrl parseInput(QString input)
    {
        if(input.startsWith("https://") || input.startsWith("http://"))
        {
            return *new QUrl(input);
        }
        else //search
        {
            return *new QUrl("https://www.google.com/search?q="+input);
        }
    }
};


class Favorite : public QToolButton{
    Q_OBJECT
public:
    Favorite(BrowserView *parent)
//        :QToolButton(parent)
    {
        this->parent=parent;
        QIcon icon;
        icon.addFile(":/sourc/fav.png");
        this->setIcon(icon);
        this->setMinimumWidth(80);
        setPopupMode(QToolButton::MenuButtonPopup);
        menu=readFavFile();
        setMenu(menu);
    }
    void setWeb(QWebEngineView *v){
        this->web = v;
    }
private:
    BrowserView *parent;
    QWebEngineView *web;
    QMenu *menu;
    QMenu* readFavFile();
    bool isPDF(QString);
public slots:
    void setFavour();
    void setUnFavour();
    void loadUrl(QString);

};


class Setting :public QToolButton
{
    BrowserView *parent;
    QMenu *menu;
public:
    Setting(BrowserView *parent);

};


#endif // UTILS_H
