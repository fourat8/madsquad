#include "connexion.h"
#include <QSqlError>
#include <QDebug>
Connexion::Connexion(){
                      }
bool Connexion::ouvrirConnexion()
{ bool test=false;
    QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_projet2A");
    db.setUserName("asmaa");
    db.setPassword("123");
    if(db.open())
   { test=true;
     return test; }
else
    qDebug()<<db.lastError().text();
    return test;
}

