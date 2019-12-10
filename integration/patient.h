#ifndef PATIENT_H
#define PATIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class patient
{
public:
    patient();
    patient(int,QString,QString,QString,QString,QString);
    QString get_nom();
    QString get_prenom();
    int get_nump();
    QString getdrdv();
    QString getmaladie();
    QString getobservation();
    void set_nump(int id);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * rechercher(int);

    bool supprimer(int idd);
    bool modifier();

private:
    QString nom,prenom,drdv,maladie,observation;
    int nump;
};

#endif // PATIENT_H

