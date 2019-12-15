#include "ordonance.h"
#include "ui_ordonance.h"
#include "ordo.h"
#include <QMessageBox>
#include<QString>
#include <QFile>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include <QTextEdit>
#include <QDebug>
#include <QSqlError>
ordonance::ordonance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ordonance)
{
    ui->setupUi(this);
    ui->tabordo->setModel(tmpordo.afficher());
    QPixmap pix(":/img/img/doctor-gp-netherlands2.jpg");
    ui->label_7->setPixmap(pix);
    son=new QSound(":/son/son/1100.wav");

}

ordonance::~ordonance()
{
    delete ui;
}

void ordonance::on_pb_ajouter_clicked()
{
    int numordonnance= ui->numO->text().toInt();
    int nump= ui->numP->text().toInt();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QString nomdocteur= ui->doc->text();
    QString medicament= ui->med->toPlainText();

ordo  o(numordonnance,nump,nom,prenom,nomdocteur,medicament);
  bool test=o.ajouter();
  if(test)
{
      son->play();
      ui->tabordo->setModel(tmpordo.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une ordonnance"),QObject::tr("ordonnance ajoutée.\n""Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une ordonnance"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void ordonance::on_pb_supprimer_clicked()
{
    int numordonnance = ui->numO->text().toInt();
    bool test=tmpordo.supprimer(numordonnance);

    if(test)
    {      son->play();

        ui->tabordo->setModel(tmpordo.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("ordonnance supprimé.\n"), QMessageBox::Ok);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void ordonance::on_pb_modifier_clicked()
{
    int numordonnance= ui->numO->text().toInt();
    int nump= ui->numP->text().toInt();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QString nomdocteur= ui->doc->text();
    QString medicament= ui->med->toPlainText();


      ordo  o(numordonnance, nump,nom,prenom,nomdocteur,medicament);
      o.modifier(nom,prenom,nomdocteur,medicament);

       if(o.modifier(nom,prenom,nomdocteur,medicament))
       {        son->play();

           ui->tabordo->setModel(o.afficher());
           QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                               QObject::tr("info d'ordonnance modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else
           QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                               QObject::tr("info d'u docteur'ordonnance non modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

}

void ordonance::on_pdf_clicked()
{
    QString strStream;
       QTextStream out(&strStream);

       const int rowCount = ui->tabordo->model()->rowCount();
       const int columnCount = ui->tabordo->model()->columnCount();
       QString TT = QDate::currentDate().toString("yyyy/MM/dd");
       out <<"<html>\n"
             "<head>\n"
              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           << "<title>ERP - COMmANDE LIST<title>\n "
           << "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h1 style=\"text-align: center;\"><strong> ******ordonnance ****** "+TT+"</strong></h1>"
           "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
             "</br> </br>";
       // headers
       out << "<thead><tr bgcolor=#d6e5ff>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tabordo->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->tabordo->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->tabordo->isColumnHidden(column)) {
                   QString data =ui->tabordo->model()->data(ui->tabordo->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

       QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
       if (dialog->exec() == QDialog::Accepted) {
           document->print(&printer);
       }

       delete document;
}

void ordonance::on_pb_deconnexion_clicked()
{

}




void ordonance::on_pb_chercher_clicked()
{
    QSqlQuery query;
         QString numordonnance= ui->numO_2->text();
        numordonnance=numordonnance+"%";
        qDebug()<<numordonnance;
        query.prepare("SELECT * from ORDO where(NUM_ORD LIKE :numordonnance)");
        query.bindValue(":numordonnance",numordonnance);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tabordo->setModel(modal);
}
