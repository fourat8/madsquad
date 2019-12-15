#include "ordo.h"



ordo::ordo()
{
    numordonnance=0;
    nom="";
    prenom="";
    nomdocteur="";
    medicament="";
    nump=0;

}
 ordo::ordo(int numordonnance, int nump,QString nom,QString prenom,QString nomdocteur,QString medicament)
{
    this->nom=nom;
    this->prenom=prenom;
    this->numordonnance=numordonnance;
    this->medicament=medicament;
    this->nomdocteur=nomdocteur;
    this->nump=nump;

}
QString ordo::get_nom(){return nom;}
QString ordo::get_prenom(){return prenom;}
int ordo::get_numordonnance(){return numordonnance;}
QString ordo::get_nomdocteur(){return nomdocteur;}
QString ordo::get_medicament(){return medicament;}
int ordo::get_nump(){return nump;}

bool ordo::ajouter()
{
QSqlQuery query;
QString res= QString::number(numordonnance);
QString res2= QString::number(nump);
query.prepare("INSERT INTO ORDO (NUM_ORD, NUMP, NOM , PRENOM , NOM_DOC , MEDICAMENT ) "
                    "VALUES ( :numordonnance , :nump ,  :nom, :prenom, :nomdocteur, :medicament )");


query.bindValue(":numordonnance", res);
query.bindValue(":nump", res2);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":nomdocteur", nomdocteur);
query.bindValue(":medicament", medicament);


return    query.exec();
}


    QSqlQueryModel * ordo::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ORDO order by NOM desc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_ORD"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUMP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM_DOC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MEDICAMENT"));


        return model;
    }






    bool ordo::supprimer(int numordoo)
    {
    QSqlQuery query;
    query.prepare("Delete from ORDO where NUM_ORD =:numordonnance ");
    query.bindValue(":numordonnance",numordoo);
    return    query.exec();
    }

    bool ordo:: modifier(QString,QString,QString,QString)
    {
        QSqlQuery query;

        query.prepare("UPDATE ORDO SET   NOM= :m, PRENOM= :p, NOM_DOC= :d ,  MEDICAMENT= :a where NUM_ORD=:o" );


         query.bindValue(":m", nom);
         query.bindValue(":p", prenom);
         query.bindValue(":d", nomdocteur);
         query.bindValue(":a", medicament);
         query.bindValue(":o", numordonnance);
        return  query.exec();

    }

    QSqlQueryModel * ordo::afficher2(QString numordonnance)
   { QSqlQueryModel * model= new QSqlQueryModel();
        //QString res= QString::number(numordonnance);
        QString cherche="Select * from ORDO where numordonnance like '"+numordonnance+"%'";
    if (numordonnance=="")
    {
        model->setQuery("select * from ORDO ");

    }
    else
    {
        model->setQuery(cherche);

    }


        model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_ORD"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUMP"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM_DOC"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("MEDICAMENT"));


        return model;


    }


