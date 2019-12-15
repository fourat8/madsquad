#include "mainwindow.h"
#include <QMessageBox>
#include "connexion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connection c;
    bool test=c.creatconnect();

   if(test)
     {w.show();
      QMessageBox::information(nullptr,QObject::tr("database is open"), QObject::tr("connection successful.\n"
                                                    "click cancel to exit."),QMessageBox::Cancel);
   }
  else
       QMessageBox::critical(nullptr,QObject::tr("database is not open"), QObject::tr("connection failed.\n"
                                                     "click cancel to exit."),QMessageBox::Cancel);
    return a.exec();
}
