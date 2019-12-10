#include "secretaire.h"
#include "ui_secretaire.h"
#include "rdv.h"
#include <QMessageBox>
#include "login.h"
#include "patient.h"

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
    son=new QSound(":/img/son/button20.wav");
    ui->picture_ajoutrdv->setPixmap(pic);
    ui->picture_affichrdv->setPixmap(pic);
    ui->picture_modifrdv->setPixmap(pic);
    ui->picture_supprdv->setPixmap(pic);
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
    QString drdv= ui->drdv_2->text();
    QString maladie= ui->maladie_2->text();
    QString obs= ui->obs_2->text();


  patient e(id,nom,prenom,drdv,maladie,obs);
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
    QString drdv= ui->m4_2->text();
    QString maladie= ui->m5_2->text();
    QString obs= ui->m6_2->text();


  patient e(0,nom,prenom,drdv,maladie,obs);
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

void secretaire::on_rech2_2_textChanged(const QString &arg1)
{
    QString rech;
    rech=ui->rech2_2->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from ordonnance where numordonnance like '"+rech+"%'");
     qry->bindValue("rech",rech);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr2_2->setModel(model);
}
