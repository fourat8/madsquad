#include "chambre.h"
//#include "ui_chambre.h"

chambre::chambre()
{
  num=0;
  type="";
  statut="";
};
chambre::chambre(int num,QString type,QString statut)
{
    this->num=num;
    this->type=type;
    this->statut=statut;
};
bool chambre::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(num);
    query.prepare("INSERT INTO CHAMBRE (NUM, TYPE, STATUT) "
                        "VALUES (:num, :type, :statut)");
    query.bindValue(":num", res);
    query.bindValue(":type", type);
    query.bindValue(":statut", statut);
    return    query.exec();
}
bool chambre::modifier(int reff,QString N,QString NB)
{
    QSqlQuery query;
    QString res= QString::number(reff);
    query.prepare("UPDATE CHAMBRE SET  TYPE= :N,STATUT= :NB where NUM = :num");
    query.bindValue(":num", res);
    query.bindValue(":N", N);
    query.bindValue(":NB",NB);
    return    query.exec();

}
QSqlQueryModel * chambre::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CHAMBRE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("statut"));
    return model;
}

bool chambre::supprimer(int reff)
{
QSqlQuery query;
QString res= QString::number(reff);
query.prepare("delete from CHAMBRE where NUM = :num ");
query.bindValue(":num", res);
return    query.exec();
}

