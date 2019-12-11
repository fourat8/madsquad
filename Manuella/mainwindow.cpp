#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rdv.h"
#include <QMessageBox>
#include "connexion.h"
#include <QDateEdit>
#include <QString>
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
    ui->tabrdv->setModel(tmprdv.afficher());
    QPixmap pic(":/img/secretariat2.jpg");
    ui->picture_ajoutrdv->setPixmap(pic);
    ui->picture_affichrdv->setPixmap(pic);
    ui->picture_modifrdv->setPixmap(pic);
    ui->picture_supprdv->setPixmap(pic);
    connexion conn;
    QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery(conn.db);
    qry->prepare("select nom from medecin");

    qry->exec();
    model->setQuery(*qry);
    ui->comboBox->setModel(model);

    son=new QSound(":/son/1100.wav");

    arduino = new QSerialPort;

    for(QSerialPortInfo info : QSerialPortInfo::availablePorts())
    {
        qDebug()<<"Name : "<<info.portName();
        qDebug()<<"vendor id : "<<info.vendorIdentifier();
        qDebug()<<"product id : "<<info.productIdentifier();

        Arduino_port_name = info.portName();
    }

    arduino->setPortName(Arduino_port_name);
    arduino->open(QSerialPort::ReadOnly);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

}


MainWindow::~MainWindow()
{
    delete ui;
    arduino->close();

}

void MainWindow::on_pb_ajouter_clicked()
{
    int cin = ui->cinline->text().toInt();
    QString nom= ui->nomline->text();
    QString prenom= ui->prenomline->text();
    QString datee = ui->dateEdit->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString objet= ui->lineEdit->text();
    QString medecin =ui->medline->text();



    rdv r(cin,nom,prenom,datee,heure,objet,medecin);
    bool test=r.ajouter();


    if(test)
    {   son->play();
        ui->tabrdv->setModel(tmprdv.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Ajouter un rendez-vous"),
            QObject::tr("Rendez-vous ajouté.\n"
                              "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);


    }
    else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un rendez-vous"),
                  QObject::tr("Erreur,le rendez-vous n'est pas ajouté!\n"
                              "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
  int cin = ui->lineEdit_id_2->text().toInt();
  bool test=tmprdv.supprimer(cin);

  if(test)
  {  son->play();
      ui->tabrdv->setModel(tmprdv.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("Supprimer un Rendez-vous"),
                QObject::tr("Rendez-vous supprimé.\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);
  }
  else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un Rendez-vous"),
                QObject::tr("Erreur,le rendez-vous n'est pas supprimé!\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

}

void MainWindow::on_pb_modifier_clicked()
{
  int cin = ui->cinlinemod->text().toInt();
  QString heure = ui->timeEdit_2->time().toString();
  bool test = tmprdv.modifier(cin,heure);


  if(test)
  {
      ui->tabrdv->setModel(tmprdv.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("Modifier un Rendez-vous"),
                QObject::tr("Rendez-vous modifié.\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);
  }
  else
    QMessageBox::critical(nullptr, QObject::tr("Modifier un Rendez-vous"),
                QObject::tr("Erreur,le rendez-vous n'est pas modifié!\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

}

void MainWindow::on_recherche_patient_clicked()
{
    QString cin = ui->patient_recherche->text();
    bool test=tmprdv.recherche_patient(cin);

   if(test)
    {    son->play();
        ui->tabrdv->setModel(tmprdv.afficher_patient(cin));//refresh
            QMessageBox::information(nullptr, QObject::tr("Recherche effectuée"),
            QObject::tr("Reussite.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
            QMessageBox::critical(nullptr, QObject::tr("Recherche non effectuée"),
                  QObject::tr("Echecs !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_rechercher_medecin_clicked()
{
    QString cin = ui->medecin_recherche->text();
    bool test=tmprdv.recherche_medecin(cin);

   if(test)
    {
       son->play();
        ui->tabrdv->setModel(tmprdv.afficher_medecin(cin));//refresh
            QMessageBox::information(nullptr, QObject::tr("Recherche effectuée"),
            QObject::tr("Reussite.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
            QMessageBox::critical(nullptr, QObject::tr("Recherche non effectuée"),
                  QObject::tr("Echecs !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_lineEdit_id_6_returnPressed()
{
    QString cin=ui->lineEdit_id_6->text();
    ui->tabrdv->setModel(tmprdv.afficher2(cin));//refresh
}

void MainWindow::on_lineEdit_id_6_textChanged(const QString &arg1)
{
    ui->tabrdv->setModel(tmprdv.afficher2(arg1));//refresh
}

void MainWindow::on_patient_recherche_returnPressed()
{
    QString cin = ui->patient_recherche->text();
    tmprdv.recherche_patient(cin);
   ui->tabrdv->setModel(tmprdv.afficher_patient(cin));//refresh
}



void MainWindow::on_medecin_recherche_returnPressed()
{
    QString cin = ui->medecin_recherche->text();
    tmprdv.recherche_medecin(cin);
   ui->tabrdv->setModel(tmprdv.afficher_medecin(cin));//refresh

}
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString nom=ui->comboBox->currentText();
    QSqlQuery qry;

    qry.prepare("select * from medecin where nom = '"+nom+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->medline->setText(qry.value(1).toString());

        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }


}


void MainWindow::on_pdf_clicked()
{
       QString strStream;
       QTextStream out(&strStream);

       const int rowCount = ui->tabrdv->model()->rowCount();
       const int columnCount = ui->tabrdv->model()->columnCount();
       QString TT = QDate::currentDate().toString("yyyy/MM/dd");
       out <<"<html>\n"
             "<head>\n"
              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           << "<title>ERP - COMmANDE LIST<title>\n "
           << "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h1 style=\"text-align: center;\"><strong> FICHE RENDEZ-VOUS "+TT+"</strong></h1>"
           "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
             "</br> </br>";
       // headers
       out << "<thead><tr bgcolor=#d6e5ff>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tabrdv->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->tabrdv->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->tabrdv->isColumnHidden(column)) {
                   QString data =ui->tabrdv->model()->data(ui->tabrdv->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pdf2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tabrdv->model()->rowCount();
    const int columnCount = ui->tabrdv->model()->columnCount();
    QString TT = QDate::currentDate().toString("dd/MM/yyyy");
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - COMmANDE LIST<title>\n "
        << "</head>\n"
           "<img src=:/img/logooo.png height=400px width=400px; position=fixed; right=10px; top=10px; />"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> FICHE RENDEZ-VOUS "+TT+"</strong></h1>"
        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tabrdv->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tabrdv->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tabrdv->isColumnHidden(column)) {
                QString data =ui->tabrdv->model()->data(ui->tabrdv->model()->index(row, column)).toString().simplified();
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
