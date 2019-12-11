#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "docteur.h"
#include <QMessageBox>
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabdocteur->setModel(tmpdocteur.afficher());
QPixmap pic(":/img/doctor-gp-netherlands.jpg");
ui->picture->setPixmap(pic);
ui->picture_2->setPixmap(pic);
 ui->picture_3->setPixmap(pic);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
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

void MainWindow::on_supprimer_clicked()
{
    int id = ui->lineEdit_id_2->text().toInt();
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




void MainWindow::on_pushButton_clicked()
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













void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
     ui->tabdocteur->setModel(tmpdocteur.afficher2(arg1));//refresh
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString id=ui->lineEdit->text();
    ui->tabdocteur->setModel(tmpdocteur.afficher2(id));//refresh
}
