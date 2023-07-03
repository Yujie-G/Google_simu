
#include <BrowserView.h>
#include "mainwindow.h"




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int nargs = argc + 1;
    char** args = new char*[nargs];
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }
    args[argc] = (char*)"--disable-web-security";

    BrowserView *window = new BrowserView();
    window->show();
    return app.exec();
}

