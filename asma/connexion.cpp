#include "connexion.h"
#include "ui_connexion.h"
#include <QDebug>
connexion::connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexion)
{
    ui->setupUi(this);
}

connexion::~connexion()
{
    delete ui;
}
connection::connection()
{

}
bool connection::creatconnect()
{bool test=false;
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
