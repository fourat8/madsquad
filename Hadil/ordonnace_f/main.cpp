#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        Connexion c;

      bool test=c.ouvrirConnexion();
      MainWindow w;
     if(test)
      {w.show();

          QMessageBox::information(nullptr, QObject::tr("database is not open"),
                      QObject::tr("connection avec succés"), QMessageBox::Ok );

      }
      else
          QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                      QObject::tr("connection failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Close);

        return a.exec();}
