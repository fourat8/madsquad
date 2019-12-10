#include <QTextDocument>
#include <QTextStream>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>

#include <QDate>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "traitement.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabpatient->setModel(tmptraitement.afficher());
QPixmap pix("C:/Users/Admin/Desktop/fourat/img/pic.jpg");
       ui->p1->setPixmap(pix);
       ui->p2->setPixmap(pix);
       ui->p3->setPixmap(pix);
       ui->p4->setPixmap(pix);
       ui->p5->setPixmap(pix);
       ui->p6->setPixmap(pix);
son=new QSound("C:/Users/Admin/Desktop/fourat/son/1100.wav");

}

MainWindow::~MainWindow()
{
   delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
   int numt = ui->nump->text().toInt();
   QString nomt= ui->nom->text();
   QString datet= ui->prenom->text();



 traitement e(numt,nomt,datet);
 bool test=e.ajouter();
 if(test)
{son->play();
     ui->tabpatient->setModel(tmptraitement.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("traitement ajouté"),
                 QObject::tr("traitement ajouté.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}
 else
     QMessageBox::critical(nullptr, QObject::tr("traitement non ajouté"),
                 QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_id_2->text().toInt();
bool test=tmptraitement.supprimer(id);
if(test)
{son->play();
   ui->tabpatient->setModel(tmptraitement.afficher());//refresh
   QMessageBox::information(nullptr, QObject::tr("Supprimer un traitement"),
               QObject::tr("traitement supprimé.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);

}
else
   QMessageBox::critical(nullptr, QObject::tr("Supprimer un traitement"),
               QObject::tr("Erreur !.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_modif_clicked()
{
     int numt= ui->m1->text().toInt();
   QString nomt= ui->m2->text();
   QString datet= ui->m3->text();





 traitement e(0,nomt,datet);
 e.set_numt(numt);
 bool test=e.modifier();
 if(test)
{ui->tabpatient->setModel(tmptraitement.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("traitement modifié"),
                 QObject::tr("traitement modifié !!.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}
 else
     QMessageBox::critical(nullptr, QObject::tr("traitement non ajouté"),
                 QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}



/*void MainWindow::on_rechercher_clicked()
{
   QString rech;
   rech=ui->rech->text();
   QSqlQueryModel * model= new QSqlQueryModel();
   QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT * from patient where nump like '"+rech+"'");
    qry->bindValue("rech",rech);
    qry->exec();
    model->setQuery(*qry);
    ui->tabr->setModel(model);
}*/

void MainWindow::on_rech_returnPressed()
{
   QString rech;
   rech=ui->rech->text();

   QSqlQueryModel * model= new QSqlQueryModel();
   QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * from traitement where numt like '"+rech+"%'");
    qry->bindValue("rech",rech);
    qry->exec();
    model->setQuery(*qry);
    ui->tabr->setModel(model);
}


/*void MainWindow::on_rechercher_2_clicked()
{
   QString rech;
   rech=ui->rech2->text();

   QSqlQueryModel * model= new QSqlQueryModel();
   QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * from ordonnance where numordonnance like '"+rech+"%'");
    qry->bindValue("rech",rech);
    qry->exec();
    model->setQuery(*qry);
    ui->tabr2->setModel(model);
}*/

void MainWindow::on_rech_textChanged(const QString &arg1)
{ QString rech;
   rech=ui->rech->text();

   QSqlQueryModel * model= new QSqlQueryModel();
   QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * from traitement where numt like '"+rech+"%'");
    qry->bindValue("rech",rech);
    qry->exec();
    model->setQuery(*qry);
    ui->tabr->setModel(model);

}


void MainWindow::on_rech2_textChanged(const QString &arg1)
{
   QString rech;
   rech=ui->rech2->text();

   QSqlQueryModel * model= new QSqlQueryModel();
   QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * from ordonnance where numordonnance like '"+rech+"%'");
    qry->bindValue("rech",rech);
    qry->exec();
    model->setQuery(*qry);
    ui->tabr2->setModel(model);
}



void MainWindow::on_modif_2_clicked()
{
    QString rech;
    rech=ui->rech2->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;

     qry.prepare("SELECT * from tabmed where Refmedicament like '%"+rech+"%' like  nomproduit = '%"+rech+"%' like nbrmed = '%"+rech+"%'");
     qry.exec();
     model->setQuery(qry);

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Refmedicament"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomproduit"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrmed"));
     ui->tabord->setModel(model);

}

void MainWindow::on_pb_supprimer_2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabpatient->model()->rowCount();
                const int columnCount = ui->tabpatient->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title>ERP - COMmANDE LIST<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> *****traitement ***** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabpatient->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabpatient->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabpatient->isColumnHidden(column)) {
                            QString data =ui->tabpatient->model()->data(ui->tabpatient->model()->index(row, column)).toString().simplified();
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
