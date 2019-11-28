#include "chambre.h"
#include "ui_mainwindow.h"
#include <QDebug>
Chambre::Chambre()
{
num=0;
type="";
statut="";
}
Chambre::Chambre(int numm,QString typee,QString statutt)
{
  this->num=numm;
  this->type=typee;
  this->statut=statutt;
}
QString Chambre::get_type(){return  type;}
QString Chambre::get_statut(){return statut;}
int Chambre::get_num(){return  num;}

bool Chambre::ajouter()
{
QSqlQuery query;
QString res= QString::number(num);
query.prepare("INSERT INTO chambre (NUM, TYPE, STATUT) "
                    "VALUES (:num, :type, :statut)");
query.bindValue(":num", res);
query.bindValue(":type", type);
query.bindValue(":statut", statut);

return    query.exec();
}

QSqlQueryModel * Chambre::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from chambre");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool Chambre::supprimer(int numm)
{
QSqlQuery query;
QString res= QString::number(numm);
query.prepare("Delete from chambre where NUM = :num ");
query.bindValue(":num", res);
return    query.exec();
}


bool Chambre:: modifier(QString type,QString statut, int num)
    {
        QSqlQuery query;

        query.prepare("UPDATE Chambre SET num=:num where type='"+type+"' or statut='"+statut+"'");
        query.bindValue(":type",type);
        query.bindValue(":statut",statut);


}
