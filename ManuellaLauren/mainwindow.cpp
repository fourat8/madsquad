#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rdv.h"
#include <QMessageBox>
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
    son=new QSound(":/son/1100.wav");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
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
/*
void MainWindow::on_chambre_recherche_clicked()
{

}

*/

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
