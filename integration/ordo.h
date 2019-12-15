#ifndef DOCTEUR_H
#define DOCTEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
class ordo
{
private:
     int numordonnance , nump;
    QString nom,prenom,nomdocteur,medicament;

public:
   ordo();
   ordo(int, int,QString,QString,QString,QString);
      int get_numordonnance();
      int get_nump();
   QString get_nom();
    QString get_prenom();
    QString get_nomdocteur();
    QString get_medicament();

    bool ajouter();
    QSqlQueryModel * afficher();
      QSqlQueryModel * afficher2(QString);
    bool supprimer(int);
    bool modifier(QString,QString,QString,QString);


};

#endif // DOCTEUR_H

