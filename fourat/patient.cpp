#include "patient.h"
#include <QDebug>

patient::patient()
{
    nump=0;
    nom="";
    prenom="";
    drdv="";
    maladie="";
    observation="";

    }
patient::patient(int nump,QString nom,QString prenom,QString drdv,QString maladie,QString observation)
    {
      this->nump=nump;
      this->nom=nom;
      this->prenom=prenom;
    this->drdv=drdv;
    this->maladie=maladie;
    this->observation=observation;
    }
    QString patient::get_nom(){return  nom;}
    QString patient::get_prenom(){return prenom;}
    int patient::get_nump(){return  nump;}
    QString patient::getdrdv(){return  drdv;}
    QString patient::getmaladie(){return  maladie;}
    QString patient::getobservation(){return  observation;}
    void patient::set_nump(int id) {nump=id;}


    bool patient::ajouter()
    {
    QSqlQuery query;
    QString res= QString::number(nump);
    query.prepare("INSERT INTO patient (nump, nom, prenom, drdv, maladie, observation)"
                        "VALUES (:nump, :nom, :prenom, :drdv, :maladie, :observation)");
    query.bindValue(":nump", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":drdv", drdv);
    query.bindValue(":maladie", maladie);
    query.bindValue(":observation", observation);


    return    query.exec();
    }

    QSqlQueryModel * patient::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from PATIENT order by nump ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DRDV"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MALADIE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("OBSERVATION"));

        return model;
    }







    bool patient::supprimer(int nump)
    {
    QSqlQuery query;
    QString res= QString::number(nump);
    query.prepare("Delete from PATIENT where NUMP = :NUMP ");
    query.bindValue(":NUMP", res);
    return    query.exec();
    }

















    bool patient::modifier()
    {
        QSqlQuery query;
        QString res= QString::number(nump);
        query.prepare("update patient set nom=:nom,prenom=:prenom,drdv=:drdv,maladie=:maladie,observation=:observation where nump= :nump");
        query.bindValue(":nump", res);
        query.bindValue(":nom", this->nom);
        query.bindValue(":prenom", this->prenom);
        query.bindValue(":drdv", this->drdv);
        query.bindValue(":maladie", this->maladie);
        query.bindValue(":observation", this->observation);

return query.exec();

    }
