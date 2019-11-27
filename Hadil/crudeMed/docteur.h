#ifndef DOCTEUR_H
#define DOCTEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class docteur
{
private:
    QString nom,prenom;
    int id;
public:
    docteur();
    docteur(QString,QString,int);
    QString get_nom();
    QString get_prenom();
    int get_id();



    bool ajouter();
    QSqlQueryModel * afficher();
         QSqlQueryModel * afficher2(QString);
    bool supprimer(int);
    bool modifier(QString,QString);


};

#endif // DOCTEUR_H
