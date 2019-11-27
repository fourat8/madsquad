#include "docteur.h"

docteur::docteur()
{
    id=0;
    nom="";
    prenom="";

}
docteur::docteur(QString nom,QString prenom,int id)
{this->nom=nom;
    this->prenom=prenom;
    this->id=id;

}
QString docteur::get_nom(){return nom;}
QString docteur::get_prenom(){return prenom;}
int docteur::get_id(){return id;}

bool docteur::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO docteur ( NOM, PRENOM,ID) "
                    "VALUES ( :nom, :prenom, :id)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);


return    query.exec();
}


    QSqlQueryModel * docteur::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from docteur order by nom asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));

        return model;
    }

    bool docteur::supprimer(int idd)
    {
    QSqlQuery query;
    query.prepare("Delete from docteur where ID =:id ");
    query.bindValue(":id",idd);
    return    query.exec();
    }

    bool docteur:: modifier(QString,QString)
    {
        QSqlQuery query;

        query.prepare("UPDATE docteur SET nom=:n , prenom= :p where id=:i" );
        query.bindValue(":n",nom);
        query.bindValue(":p",prenom);
        query.bindValue(":i",id);

        return  query.exec();

    }

    QSqlQueryModel * docteur::afficher2(QString id)
   { QSqlQueryModel * model= new QSqlQueryModel();
        //QString res= QString::number(id);
        QString cherche="Select * from docteur where id like '"+id+"%'";
    if (id=="")
    {
        model->setQuery("select * from docteur ");

    }
    else
    {
        model->setQuery(cherche);

    }



    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));


        return model;


    }








