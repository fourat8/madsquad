#include "secretaire.h"
#include "ui_secretaire.h"
#include "rdv.h"
#include <QMessageBox>
#include "login.h"
#include "patient.h"
#include "traitement.h"
#include "docteur2.h"
#include "ordo.h"
#include <QFile>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>


secretaire::secretaire(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secretaire)
{
    ui->setupUi(this);
    ui->tabrdv->setModel(tmprdv.afficher());
    ui->tabpatient_2->setModel(tmppatient.afficher());
    QPixmap pic(":/img/img/secretariat2.jpg");
    QPixmap pic2(":/img/img/pic.jpg");
    ui->p1_2->setPixmap(pic2);
    ui->p2_2->setPixmap(pic2);
    ui->p3_2->setPixmap(pic2);
    ui->p4_2->setPixmap(pic2);
    ui->p5_2->setPixmap(pic2);
    ui->p6_2->setPixmap(pic2);
    son=new QSound(":/son/son/button20.wav");
    ui->picture_ajoutrdv->setPixmap(pic);
    ui->picture_affichrdv->setPixmap(pic);
    ui->picture_modifrdv->setPixmap(pic);
    ui->picture_supprdv->setPixmap(pic);
    ui->tabdocteur->setModel(tmpdocteur.afficher());
    ui->tabpatient->setModel(tmptraitement.afficher());
    ui->tabpatient_2->setModel(tmppatient.afficher());
    ui->tabr->setModel(tmptraitement.afficher());

}

secretaire::~secretaire()
{
    delete ui;
}

void secretaire::on_pb_ajouter_clicked()
{
    int cin = ui->cinline->text().toInt();
    QString nom= ui->nomline->text();
    QString prenom= ui->prenomline->text();
    int datee = ui->dateEdit->text().toInt();
    int heure = ui->lineEdit_4->text().toInt();
    QString objet= ui->lineEdit->text();
    QString medecin =ui->telline->text();


    rdv r(cin,nom,prenom,datee,heure,objet,medecin);
    bool test=r.ajouter();

    if(test)
    {
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

void secretaire::on_pb_supprimer_clicked()
{
  int cin = ui->lineEdit_id_2->text().toInt();
  bool test=tmprdv.supprimer(cin);

  if(test)
  {
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

void secretaire::on_pb_modifier_clicked()
{
  int cin = ui->cinlinemod->text().toInt();
  int heure = ui->lineEdit_2->text().toInt();
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

void secretaire::on_recherche_patient_clicked()
{
    QString cin = ui->patient_recherche->text();
    bool test=tmprdv.recherche_patient(cin);

   if(test)
    {
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



void secretaire::on_patient_recherche_returnPressed()
{
    QString cin = ui->patient_recherche->text();
    tmprdv.recherche_patient(cin);
   ui->tabrdv->setModel(tmprdv.afficher_patient(cin));//refresh
}

void secretaire::on_pushButton_clicked()
{
    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
     msgBox.setText("Voulez-vous vraiment vous déconnecter ?");
     msgBox.exec();

     if (msgBox.clickedButton() == connectButton)
     {
         msgBox.close();
         close();
         login c;
         c.exec();

     }
     else if (msgBox.clickedButton() == abortButton) {
         msgBox.close();
     }
}

void secretaire::on_pb_ajouter_3_clicked()
{
    int id = ui->nump_2->text().toInt();
    QString nom= ui->nom_2->text();
    QString prenom= ui->prenom_2->text();
    int numtraitement= ui->drdv_2->text().toInt();
    QString maladie= ui->maladie_2->text();
    QString obs= ui->obs_2->text();


  patient e(id,nom,prenom,numtraitement,maladie,obs);
  bool test=e.ajouter();
  if(test)
{son->play();
      ui->tabpatient_2->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("patient ajouté"),
                  QObject::tr("Dossier ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void secretaire::on_pb_supprimer_3_clicked()
{
    int id = ui->lineEdit_id_4->text().toInt();
    bool test=tmppatient.supprimer(id);
    if(test)
    {son->play();
        ui->tabpatient_2->setModel(tmppatient.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Etudiant supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void secretaire::on_modif_2_clicked()
{
    int id = ui->m1_2->text().toInt();
    QString nom= ui->m2_2->text();
    QString prenom= ui->m3_2->text();
    int numtraitement= ui->m4_2->text().toInt();
    QString maladie= ui->m5_2->text();
    QString obs= ui->m6_2->text();


  patient e(0,nom,prenom,numtraitement,maladie,obs);
  e.set_nump(id);
  bool test=e.modifier();
  if(test)
{ui->tabpatient_2->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Dossier modifié"),
                  QObject::tr("Dossier modifié !!.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void secretaire::on_rech_2_returnPressed()
{
    QString rech;
    rech=ui->rech_2->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from patient where nump like '"+rech+"%'");
     qry->bindValue("rech",rech);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr_2->setModel(model);
}

void secretaire::on_rech_2_textChanged(const QString &arg1)
{

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();

         qry->prepare("SELECT * from patient where nump like '"+arg1+"%'");
         qry->bindValue("rech",arg1);
         qry->exec();
         model->setQuery(*qry);
         ui->tabr_2->setModel(model);
}

void secretaire::on_rech2_2_textChanged(const QString &arg1)
{


    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from ordonnance where numordonnance like '"+arg1+"%'");
     qry->bindValue("rech",arg1);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr2_2->setModel(model);
}

void secretaire::on_pb_ajouter_4_clicked()
{
    int numt = ui->nump->text().toInt();
    QString nomt= ui->nom_3->text();
    QString datet= ui->prenom_3->text();



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

void secretaire::on_pb_supprimer_4_clicked()
{
    int id = ui->lineEdit_id_3->text().toInt();
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

void secretaire::on_modif_clicked()
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

void secretaire::on_rech_textChanged(const QString &arg1)
{

       QSqlQueryModel * model= new QSqlQueryModel();
       QSqlQuery* qry=new QSqlQuery();

        qry->prepare("SELECT * from traitement where numt like '"+arg1+"%'");
        qry->bindValue("rech",arg1);
        qry->exec();
        model->setQuery(*qry);
        ui->tabr->setModel(model);


}

void secretaire::on_rech2_textChanged(const QString &arg1)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from ordo where numordonnance like '"+arg1+"%'");
     qry->bindValue("rech",arg1);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr2->setModel(model);
}

void secretaire::on_modif_3_clicked()
{
    QString rech;
    rech=ui->ord->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;

     qry.prepare("SELECT * from tabmed where Refmedicament =  '"+rech+"' or  nomproduit = '"+rech+"' or nbrmed = '"+rech+"'");

     qry.exec();
     model->setQuery(qry);

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Refmedicament"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomproduit"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrmed"));
     ui->tabord->setModel(model);
}

void secretaire::on_pb_supprimer_2_clicked()
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
                        "<h1 style=\"text-align: center;\"><strong> ***** Traitements ***** "+TT+"</strong></h1>"
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

void secretaire::on_pb_ajouter_2_clicked()
{
    int id= ui->lineEdit_id->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    docteur e(nom,prenom,id);
  bool test=e.ajouter();
  if(test)
{ui->tabdocteur->setModel(tmpdocteur.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un medecin"),QObject::tr("medecin ajouté.\n""Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un émedecin"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void secretaire::on_pushButton_2_clicked()
{

    int id= ui->lineEdit_id->text().toInt();
 QString nom=ui->lineEdit_nom->text();
 QString prenom=ui->lineEdit_prenom->text();


docteur e(nom,prenom,id);
e.modifier(nom,prenom);

if(e.modifier(nom,prenom))
{   ui->tabdocteur->setModel(e.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier un docteur"),
                       QObject::tr("info du docteurmodifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}
else
   QMessageBox::information(nullptr, QObject::tr("modifier un docteur"),
                       QObject::tr("info du docteur non modifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}



void secretaire::on_supprimer_clicked()
{
    int id = ui->lineEdit_id_5->text().toInt();
    bool test=tmpdocteur.supprimer(id);

    if(test)
    {ui->tabdocteur->setModel(tmpdocteur.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un docteur"),
                    QObject::tr("docteur supprimé.\n"), QMessageBox::Ok);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("Supprimer un docteur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void secretaire::on_lineEdit_3_textChanged(const QString &arg1)
{
    ui->tabdocteur->setModel(tmpdocteur.afficher2(arg1));
}

void secretaire::on_pb_supprimer_5_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabpatient_2->model()->rowCount();
                const int columnCount = ui->tabpatient_2->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title>ERP - COMmANDE LIST<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ***** Patients ***** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabpatient_2->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabpatient_2->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabpatient_2->isColumnHidden(column)) {
                            QString data =ui->tabpatient_2->model()->data(ui->tabpatient_2->model()->index(row, column)).toString().simplified();
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
