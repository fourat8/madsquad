#include "mainwindow.h"
#include "ui_mainwindow.h"
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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabordo->setModel(tmpordo.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int numorodonnance= ui->num->text().toInt();
    QString nomdocteur= ui->doc->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
     QString medicament1= ui->med1->text();
     QString medicament2= ui->med2->text();
     QString medicament3= ui->med3->text();
     QString medicament4= ui->med4->text();
ordo  o(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4,numorodonnance);
  bool test=o.ajouter();
  if(test)
{ui->tabordo->setModel(tmpordo.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une ordonnance"),QObject::tr("ordonnance ajoutée.\n""Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une ordonnance"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_supprimer_clicked()
{
    int numordonnance = ui->num_2->text().toInt();
    bool test=tmpordo.supprimer(numordonnance);

    if(test)
    {ui->tabordo->setModel(tmpordo.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("ordonnance supprimé.\n"), QMessageBox::Ok);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
}




void MainWindow::on_pushButton_clicked()
{

    int numorodonnance= ui->num->text().toInt();
    QString nomdocteur= ui->doc->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
     QString medicament1= ui->med1->text();
     QString medicament2= ui->med2->text();
     QString medicament3= ui->med3->text();
     QString medicament4= ui->med4->text();

      ordo  o(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4,numorodonnance);
      o.modifier(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4);

       if(o.modifier(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4))
       {   ui->tabordo->setModel(o.afficher());
           QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                               QObject::tr("info d'ordonnance modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else
           QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                               QObject::tr("info d'u docteur'ordonnance non modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


}





void MainWindow::on_numm_textChanged(const QString &arg1)
{

        ui->tabordo->setModel(tmpordo.afficher2(arg1));//refresh
}

void MainWindow::on_numm_returnPressed()
{
    QString numordonnance=ui->numm->text();
    ui->tabordo->setModel(tmpordo.afficher2(numordonnance));//refresh
}

void MainWindow::on_pdf_clicked()
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
                "<h1 style=\"text-align: center;\"><strong> ******LISTE DES Réservations ****** "+TT+"</strong></h1>"
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

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
    }

