#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QPdfWidget>
#include <QtWidgets>
#include <QWebEngineView>
#include <utils.h>


// main view
class BrowserView : public QWidget
{
private:
    const int MAX_LEN = 1500;
    const int MAX_WID = 1000;
    const QUrl HOME;

public:

    QHBoxLayout *tabs_column;
    Tab *curTab;
    QPushButton *homeButton;
    QPushButton *backButton;
    QPushButton *forwardButton;
    QPushButton *reloadButton;
    QProgressBar *progressBar;
    Favorite *favorite;
    Setting *setting;
    QLabel* hint;
    QMenu* history;
    QWebEngineView *view;
    QVBoxLayout *vLayout;
    QPdfWidget *pdfView;
    BrowserView();
    void showPdf(QString);
    void addNewTab();

private:
    void showGame();
    void addPage2Fav();
};

class startscene : public QWidget
{
    Q_OBJECT
private:
    const int MAX_LEN = 1150;
    const int MAX_WID = 400;
    BrowserView* parent;

public:
    int i2 = 0;
    startscene(BrowserView*);
    void keyPressEvent(QKeyEvent *event);

signals:

};
#endif // BROWSERVIEW_H
