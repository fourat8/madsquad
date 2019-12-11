#include "rdv.h"
#include <QDebug>

rdv::rdv()
{
    cin=0;
    nom="";
    prenom="";
    datee="";
    heure="";
    objet="";
    medecin="";
}

rdv::rdv(int cin,QString nom,QString prenom,QString datee,QString heure,QString objet,QString medecin)
{
  this->cin=cin;
  this->nom=nom;
  this->prenom=prenom;
  this->datee=datee;
  this->heure=heure;
  this->objet=objet;
  this->medecin=medecin;
}

QString rdv::get_nom()
{
    return  nom;
}
QString rdv::get_prenom(){
    return prenom;
}
QString rdv::get_objet(){
    return objet;
}

QString rdv::get_medecin(){
    return medecin;
}

int rdv::get_cin()
{
    return  cin;
}

QString rdv::get_datee()
{
    return  datee;
}

QString rdv::get_heure()
{
    return  heure;
}

bool rdv::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(cin);
    query.prepare("INSERT INTO rdv (CIN, NOM, PRENOM, HEURE, OBJET,MEDECIN, DATEE) "
                        "VALUES (:cin, :nom, :prenom, :heure, :objet,:medecin, :datee)");
    query.bindValue(":cin", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":heure", heure);
    query.bindValue(":objet", objet);
    query.bindValue(":medecin", medecin);
    query.bindValue(":datee", datee);



    return    query.exec();
}

QSqlQueryModel * rdv::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from rdv");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("OBJET"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MEDECIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE"));


        return model;
}

QSqlQueryModel * rdv::afficher_patient(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    if (idd=="")
    {
        model->setQuery("select * from rdv");

    }
    else {
        model->setQuery("select cin, nom, prenom, heure, medecin from rdv WHERE CIN = '"+idd+"'");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MEDECIN"));
    return model;
}


bool rdv::recherche_patient(QString idd)
{
    QSqlQuery query;
    //QString cinn= QString::number(idd);
    query.prepare("select nom, prenom, heure, medecin from rdv WHERE CIN = '"+idd+"'");
    //query.bindValue(":cin", cinn);

    return    query.exec();


}

QSqlQueryModel * rdv::afficher_medecin(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    if (idd=="")
    {
        model->setQuery("select * from rdv");

    }
    else {
        model->setQuery("select nom, prenom, heure from rdv WHERE MEDECIN = '"+idd+"'");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE"));
    return model;
}


bool rdv::recherche_medecin(QString idd)
{
    QSqlQuery query;
    //QString cinn= QString::number(idd);
    query.prepare("select nom, prenom, heure from rdv WHERE MEDECIN = '"+idd+"'");
    //query.bindValue(":cin", cinn);

    return    query.exec();


}

bool rdv::supprimer(int idd)
{
    QSqlQuery query;
    QString cinn= QString::number(idd);
    query.prepare("Delete from rdv where CIN = :cin ");
    query.bindValue(":cin", cinn);

    return    query.exec();
}

bool rdv::modifier(int idd,QString h)
{
    QSqlQuery query;
    QString cinn=QString::number(idd);
    QString heuree=h;
    query.prepare("UPDATE rdv SET HEURE = :heure where CIN = :cin");
    query.bindValue(":cin",cinn);
    query.bindValue(":heure",h);

    return query.exec();
}

QSqlQueryModel * rdv::afficher2(QString cin)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    QString cherche="Select * from rdv where cin like '"+cin+"%'";
    if (cin=="")
    {
     model->setQuery("select * from rdv order by cin");

    }
    else
    {
        model->setQuery(cherche);

    }
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("HEURE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("OBJET"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("MEDECIN"));
        return model;
  }

