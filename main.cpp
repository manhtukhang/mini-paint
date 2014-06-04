/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 ******************************************************************************/


#include "mainwindow.h"
#include <QtPlugin>
#include <QApplication>

// Macro của Qt, dùng để nạp Plugin khi tạo đối tượng
Q_IMPORT_PLUGIN(BasicToolsPlugin)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
