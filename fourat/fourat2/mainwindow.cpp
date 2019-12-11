#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>

#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabpatient->setModel(tmppatient.afficher());
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
    int id = ui->nump->text().toInt();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    int numtraitement= ui->drdv->text().toInt();
    QString maladie= ui->maladie->text();
    QString obs= ui->obs->text();


  patient e(id,nom,prenom,numtraitement,maladie,obs);
  bool test=e.ajouter();
  if(test)
{son->play();
      ui->tabpatient->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("patient ajouté"),
                  QObject::tr("Dossier ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_id_2->text().toInt();
bool test=tmppatient.supprimer(id);
if(test)
{son->play();
    ui->tabpatient->setModel(tmppatient.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                QObject::tr("Etudiant supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_modif_clicked()
{
    int id = ui->m1->text().toInt();
    QString nom= ui->m2->text();
    QString prenom= ui->m3->text();
    int numtraitement= ui->m4->text().toInt();
    QString maladie= ui->m5->text();
    QString obs= ui->m6->text();


  patient e(0,nom,prenom,numtraitement,maladie,obs);
  e.set_nump(id);
  bool test=e.modifier();
  if(test)
{ui->tabpatient->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Dossier modifié"),
                  QObject::tr("Dossier modifié !!.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
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

     qry->prepare("SELECT * from patient where nump like '"+rech+"%'");
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

     qry->prepare("SELECT * from patient where nump like '"+rech+"%'");
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

void MainWindow::on_pdf_clicked()
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
                "<h1 style=\"text-align: center;\"><strong> *****LISTE DES Réservations ***** "+TT+"</strong></h1>"
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

void MainWindow::on_imp2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabr->model()->rowCount();
                const int columnCount = ui->tabr->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title>ERP - COMmANDE LIST<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> *****ordonnance ***** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabr->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabr->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabr->isColumnHidden(column)) {
                            QString data =ui->tabr->model()->data(ui->tabr->model()->index(row, column)).toString().simplified();
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
