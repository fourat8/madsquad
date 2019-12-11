#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexion c;
    bool test=c.ouvrirconnexion();
    MainWindow w;
    if(test)
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("BASE DE DONNEE OUVERTE"),
                    QObject::tr("CONNEXION REUSSIE.\n"
                                "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("BASE DE DONNEE FERMEE"),
                    QObject::tr("ECHEC DE LA CONNEXION.\n"
                                "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

    }
    return a.exec();
}
