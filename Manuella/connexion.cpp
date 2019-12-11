#include "connexion.h"
#include <QSqlError>

connexion::connexion()
{

}

bool connexion::ouvrirconnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
                 db.setDatabaseName("secretaire");//nom de la base du projet
                 db.setUserName("Manuella");//inserer nom de l'utilisateur
                 db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

     if (db.open())
     {
        test=true;
     }

      else throw QString ("Erreur dans les paramètres de la base."+db.lastError().text());

      return  test;
}

void connexion::fermerconnexion()
{
    db.close();
}


