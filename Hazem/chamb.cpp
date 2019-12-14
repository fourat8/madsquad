#include "chamb.h"
#include "ui_chamb.h"
#include "chambre.h"
#include <QMessageBox>
#include "QDebug"
#include "QSqlError"
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>

Chamb::Chamb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chamb)
{
    ui->setupUi(this);
    ui->tabchambre->setModel(tmp.afficher());
    QPixmap pix(":/img/chambre.jpg");
    ui->label_6->setPixmap(pix);
}

Chamb::~Chamb()
{
    delete ui;
}


void Chamb::on_pb_ajouter_clicked()
{
    int num = ui->lineEdit_num->text().toInt();
    QString type= ui->lineEdit_type->text();
    QString statut= ui->lineEdit_statut->text();
  chambre c(num,type,statut);
  bool test=c.ajouter();
  if(test)
{ui->tabchambre->setModel(tmp.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une chambre"),
                  QObject::tr("Chambre ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

           ui->lineEdit_num->clear();
           ui->lineEdit_type->clear();
           ui->lineEdit_statut->clear();

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un chambre"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void Chamb::on_pb_supprimer_clicked()
{
int num = ui->lineEdit_num->text().toInt();
bool test=tmp.supprimer(num);
if(test)
{ui->tabchambre->setModel(tmp.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer une chambre"),
                QObject::tr("Chambre supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_num->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_statut->clear();

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer une chambre"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}




void Chamb::on_pb_modifier_clicked()

{

    int num = ui->lineEdit_num->text().toInt();
    QString type= ui->lineEdit_type->text();
    QString statut= ui->lineEdit_statut->text();
    bool test=tmp.modifier(num,type,statut);
       if(test)
       {   ui->tabchambre->setModel(tmp.afficher());
           QMessageBox::information(nullptr, QObject::tr("modifier une chambre"),
                               QObject::tr("info du chambre modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
           ui->lineEdit_num->clear();
           ui->lineEdit_type->clear();
           ui->lineEdit_statut->clear();

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("modifier une chambre"),
                               QObject::tr("info du chambre non modifié.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


}




void Chamb::on_pb_chercher_clicked()
{
    QSqlQuery query;
         QString num= ui->lineEdit_num_2->text();
        num=num+"%";
        qDebug()<<num;
        query.prepare("SELECT * from CHAMBRE where(NUM LIKE :num)");
        query.bindValue(":num",num);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tabchambre_2->setModel(modal);
        ui->lineEdit_num_2->clear();

}

void Chamb::on_pb_imprimer_clicked()
{
    QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tabchambre->model()->rowCount();
              const int columnCount = ui->tabchambre->model()->columnCount();
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
                  if (!ui->tabchambre->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tabchambre->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tabchambre->isColumnHidden(column)) {
                          QString data =ui->tabchambre->model()->data(ui->tabchambre->model()->index(row, column)).toString().simplified();
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

void Chamb::on_pb_chercherNum_clicked()
{
    QString  num= ui->lineEdit_num->text();
     qDebug()<< num << endl;
            QSqlQuery query;
            query.first();
            query.prepare("SELECT * from CHAMBRE where NUM= '"+num+"'");
            if(query.exec())

            {
                while(query.next())
                {

                    ui->lineEdit_num->setText(query.value(0).toString());//num
                    ui->lineEdit_type->setText(query.value(1).toString());//type
                    ui->lineEdit_statut->setText(query.value(2).toString());//statut


                }
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Chercher chambre!"),
                                      QObject::tr("Erreur!.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
}
