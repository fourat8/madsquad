#include "compte.h"
#include "QDebug"
#include "login.h"

compte::compte()
{

}

compte::compte(QString nom,QString prenom,QString nomcom,QString mdp, QString daate, QString statut)
{
    this->nom=nom;
    this->prenom=prenom;
    this->nomcom=nomcom;
    this->mdp=mdp;
    this->daate=daate;
    this->statut=statut;
}

bool compte::ajouter_compte()
{
QSqlQuery query;
query.prepare("INSERT INTO compte (nom, prenom, nomcom, mdp, daate,statut) VALUES (:nom, :prenom, :nomcom, :mdp, :daate, :statut)");
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":nomcom", nomcom);
query.bindValue(":mdp", mdp);
query.bindValue(":daate", daate);
query.bindValue(":statut", statut);

return    query.exec();
}

bool compte::verifier_compte(QString nomcom, QString mdp)
{
    QSqlQuery query;
    QString mdpbd,nomcombd;

    if (mdp=="" || nomcom=="")
    {
        return  false;
    }

    qDebug()<<query.exec("SELECT mdp,nomcom FROM compte WHERE"
                  " nomcom= '"+nomcom+"' AND"
                  " mdp= '"+mdp+"'");
    while (query.next()) {
        qDebug()<<"salut";
       mdpbd = query.value("mdp").toString();
       nomcombd= query.value("nomcom").toString();
        }
    if (mdpbd==mdp && nomcom==nomcombd)
    {

        return true;
    }

    else
    {
        return  false;
    }

}
int compte::verifier_statut(QString nomcom, QString mdp)
{
    QSqlQuery query;
    QString statut;
    query.exec("SELECT statut FROM compte WHERE"
               " nomcom= '"+nomcom+"' AND"
               " mdp= '"+mdp+"'");
    while (query.next())
    {
        statut=query.value("statut").toString();
    }
    if (statut=="medecin")
        return 1;
    else if (statut=="secretaire")
        return 2;
    else if (statut=="chef de depot")
        return 3;
    else if (statut=="pharmacien")
        return 4;
    else return 0;
}

QSqlQueryModel * compte::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from compte order by nom");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}

QSqlQueryModel * compte::afficher2(QString ref)
{QSqlQueryModel * model= new QSqlQueryModel();
    //QString res= QString::number(ref);
if (ref=="")
{
    model->setQuery("select * from compte order by nom");

}
else
{
    QString cherche="Select * from compte where nomcom = '"+ref+"' or mdp = '"+ref+"' or nom = '"+ref+"' or statut = '"+ref+"' or daate = '"+ref+"'";

}
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool compte::supprimer(QString nom)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from compte where nom = '"+nom+"' or prenom ='"+nom+"' or nomcom='"+nom+"' or mdp ='"+nom+"' or statut ='"+nom+"'" );
query.bindValue(":nom", nom);
return    query.exec();
}
