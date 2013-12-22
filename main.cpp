#include "mainwindow.h"

#include <iostream>
#include <stdio.h>
#include <QApplication>

//@author Buu Ngo and Jessica Milne 10/28/13

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();

    return a.exec();
}


