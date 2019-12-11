#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class rdv
{
public:
    rdv();
    rdv(int,QString,QString,QString,QString,QString,QString);
    QString get_nom();
    QString get_prenom();
    QString get_objet();
    QString get_medecin();
    int get_cin();
    QString get_heure();
    QString get_datee();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);
    QSqlQueryModel * afficher_patient(QString);
    bool recherche_patient(QString);
    QSqlQueryModel * afficher_medecin(QString);
    bool recherche_medecin(QString);
    QSqlQueryModel * afficher_chambre(QString);
    bool recherche_chambre(QString); 
    bool supprimer(int);
    bool modifier(int,QString);
private:
    QString nom,prenom,objet,medecin,datee,heure;
    int cin;
};

#endif // RDV_H



