#ifndef CHAMBRE_H
#define CHAMBRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Chambre
{public:
    Chambre();
    Chambre(int,QString,QString);
    QString get_type();
    QString get_statut();
    int get_num();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool chercher(int);
    bool modifier(QString,QString, int);
private:
    QString type,statut;
    int num;

};

#endif // CHAMBRE_H
