#ifndef CHAMBRE_H
#define CHAMBRE_H
#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QObject>
class chambre
{
private:
    int num;
    QString type;
    QString statut;

public:
    chambre();
    chambre(int,QString,QString);
    bool ajouter();
    int getnum() {return num;}
    QString gettype() {return type;}
    void settype(QString t) {type=t;}
    QString getstatut() {return statut;}
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString);



};

#endif // CHAMBRE_H
